#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int square(int num) {	
	return num*num;
}

void main() {
	int server_fd, client_fd1, client_fd2;
	struct sockaddr_in address, cli_addr1, cli_addr2;
	int addrlen = sizeof(address);
	int num;
		
	printf("TCP Server\n");
	
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
		
	if((client_fd1 = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
		printf("Connection failed!\n");
		exit(1);
	} else {
		printf("Connected to client 1.\n");
	}
		
	if((client_fd2 = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
		printf("Connection failed!\n");
		exit(1);
	} else {
		printf("Connected to client 2.\n");
	}
		
		
	if(recv(client_fd1, &num, sizeof(int), 0) < 0) {
		printf("Receive failed!\n");
		exit(1);
	} else {
		printf("Received string from client 1: %d\n", num);
	}
		
	num = square(num);
	
	if(send(client_fd2, &num, sizeof(num), 0) < 0) {
		printf("Send failed!\n");
		exit(1);
	} else {
		printf("Squared number sent to client 2.\n");
	}
	close(server_fd);
	close(client_fd1);
	close(client_fd2);
}
