#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	char* str;
	int opt;
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
	
	str = (char*) malloc(20 * sizeof(char));
	
	printf("Enter string: ");
	scanf("%s", str);
	if(sendto(client_fd, str, 20 * sizeof(char), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Send failed!\n");
			exit(1);
	} else {
		printf("String sent: %s\n", str);
	}

	close(client_fd);
}
