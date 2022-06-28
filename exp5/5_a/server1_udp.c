#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

char* reverse(char* str) {
	char* temp = strdup(str);
	int n = strlen(temp);
	
	for(int i = 0; i < n / 2; i++) {
		char t = temp[i];
		temp[i] = temp[n - i - 1];
		temp[n - i - 1] = t;
	}
	
	return temp;
}

void main() {
	int server_fd;
	struct sockaddr_in address, cli_addr1;
	int opt, addrlen = sizeof(address);
	char* str;
		
	printf("UDP Server\n");
	if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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
	int len = sizeof(cli_addr1);
		
	cli_addr1.sin_port = htons(8001);
		
	str = (char*) malloc(20 * sizeof(char));
	
	if(recvfrom(server_fd, str, 20 * sizeof(char), 0, (struct sockaddr*) &address, &len) < 0) {
		printf("Receive failed!\n");
		exit(1);
	} else {
		printf("Received string from client 1: %s\n", str);
	}
		
	str = reverse(str);
		
	if(sendto(server_fd, str, 20 * sizeof(char), 0, (struct sockaddr*) &cli_addr1, len) < 0) {
		printf("Send failed!\n");
		exit(1);
	} else {
		printf("Reversed string sent to client 2.\n");
	}
	
	close(server_fd);
}
