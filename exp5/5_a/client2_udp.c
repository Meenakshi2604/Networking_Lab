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
	char* str;
	int len = sizeof(serv_addr);
	printf("UDP Client\n");

	if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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
	cli_addr.sin_port = htons(8001);
	
	str = (char*) malloc(20 * sizeof(char));

	if(bind(client_fd, (struct sockaddr*) &cli_addr, sizeof(cli_addr)) < 0) {
		printf("Socket binding failed!\n");
		exit(1);
	} else {
		printf("Socket binded.\n");
	}
		
	if(recvfrom(client_fd, str, 20 * sizeof(char), 0, (struct sockaddr*) &serv_addr, &len) < 0) {
		printf("Receive failed!\n");
		exit(1);
	} else {
		printf("Reversed string received: %s\n", str);
	}
	
	close(client_fd);
}
