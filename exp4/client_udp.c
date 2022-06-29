#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	float *buff, reply[3];
	int n;
	
	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(client_fd < 0) {
		printf("Socket creation failed!\n");
		exit(1);
	} else {
		printf("Client socket created.\n");
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8000);
	
	printf("Enter size: ");
	scanf("%d", &n);
	
	buff = (float*) malloc(n * sizeof(float));
	
	printf("Enter numbers: ");
	for(int i = 0; i < n; i++)
		scanf("%f", &buff[i]);
	
	int len = sizeof(serv_addr);
	
	if(sendto(client_fd, &n, sizeof(int), 0, (struct sockaddr*) &serv_addr, len) < 0) {
		printf("Send failed!\n");
		exit(1);
	} else {
		if(sendto(client_fd, buff, n * sizeof(float), 0, (struct sockaddr*) &serv_addr, len) < 0) {
			printf("Send failed!\n");
			exit(1);
		} else {
			printf("Data sent:");
			for(int i = 0; i < n; i++) {
				printf(" %.1f", buff[i]);
			}
			printf("\nWaiting for reply.\n");
		}
	}
	
	if(recvfrom(client_fd, reply, 3 * sizeof(float), 0, (struct sockaddr*) &serv_addr, &len) < 0) {
		printf("Receive failed!\n");
		exit(1);
	} else {
		printf("Result received:\n");
		printf("Min: %.1f\n", reply[0]);
		printf("Max: %.1f\n", reply[1]);
		printf("Avg: %.1f\n", reply[2]);
	}
	
	close(client_fd);
}
