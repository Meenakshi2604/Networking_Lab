#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


float findMin(float *buff, int n) {
	int min = 0;
	for(int i = 0; i < n; i++) {
		if (buff[min] > buff[i])
			min = i;
	}
	return buff[min];
}

float findMax(float *buff, int n) {
	int max = 0;
	for(int i = 0; i < n; i++) {
		if (buff[max] < buff[i])
			max = i;
	}
	return buff[max];
}

float findAvg(float *buff, int n) {
	float avg = 0;
	for(int i = 0; i < n; i++) {
		avg += buff[i];
	}
	avg /= n;
	return avg;
}

void main() {
	int server_fd, client_fd;
	struct sockaddr_in address;
	int n, addrlen = sizeof(address);
	float *buff, output[3];

	
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation failed!\n");
		exit(1);
	} else {
		printf("Server socket created.\n");
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8000);
	
	if(bind(server_fd, (struct sockaddr*) &address, addrlen) < 0) {
		printf("Socket binding failed!\n");
		exit(1);
	} else {
		printf("Socket binded.\n");
	}
	
	if(listen(server_fd, 5) < 0) {
		printf("Listening failed!\n");
		exit(1);
	} else {
		printf("Server listening.\n");
	}
	
	if((client_fd = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
		printf("Connection failed!\n");
		exit(1);
	} else {
		printf("Connected to client.\n");
	}
	
	if(recv(client_fd, &n, sizeof(int), 0) < 0) {
		printf("Receive failed!\n");
		exit(1);
	} else {
		buff = (float*) malloc(n * sizeof(float));
		
		if(recv(client_fd, buff, n * sizeof(float), 0) < 0) {
			printf("Receive failed!\n");
			exit(1);
		} else {
			printf("Received data:");
			for(int i = 0; i < n; i++) {
				printf(" %.1f", buff[i]);
			}
			printf("\n");
		}
	}
	
	printf("Calculating min, max and avg.\n");
	output[0] = findMin(buff, n);
	output[1] = findMax(buff, n);
	output[2] = findAvg(buff, n);
	
	if(send(client_fd, output, 3 * sizeof(float), 0) < 0) {
		printf("Send failed!\n");
		exit(1);
	} else {
		printf("Result sent to client.\n");
	}
	
	close(server_fd);
	close(client_fd);
}
