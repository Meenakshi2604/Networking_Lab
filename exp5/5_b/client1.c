#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	int num;
	
	printf("TCP Client\n");
	if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation failed!\n");
		exit(1);
	} else {
		printf("Client socket created.\n");
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8000);
	
	if(connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Connection failed!\n");
		exit(1);
	} else {
		printf("Connection established.\n");
	}
	
	
	printf("Enter a number ");
	scanf("%d", &num);
	if(send(client_fd, &num, sizeof(int), 0) < 0) {
		printf("Send failed!\n");
		exit(1);
	} else {
		printf("Number sent: %d\n", num);
	}
	
	close(client_fd);
}
