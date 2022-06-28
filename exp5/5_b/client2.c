#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	int num;
	int len = sizeof(serv_addr);
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
	
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = INADDR_ANY;
	cli_addr.sin_port = htons(8000);
	
	if(connect(client_fd, (struct sockaddr*) &serv_addr, len) < 0) {
		printf("Connection failed!\n");
		exit(1);
	} else {
		printf("Connection established.\n");
	}
	
	if(recv(client_fd, &num, sizeof(int), 0) < 0) {
		printf("Receive failed!\n");
		exit(1);
	} else {
		printf("Squared number is: %d\n", num);
	}
	close(client_fd);
}
