#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int sockid;
	struct sockaddr_in server;
	int out[3];
	int number[10] = { 5, 4, 3, 8, 9, 1, 2, 0, 6 ,7};

	// Create socket
	sockid = socket(AF_INET, SOCK_STREAM, 0);
	if (sockid == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	// Connect to remote server
	if (connect(sockid, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");

	if (send(sockid, &number, 10 * sizeof(int), 0) < 0) {
		puts("Send failed");
		return 1;
	}

	// Receive a reply from the server
	if (recv(sockid, &out, 3* sizeof(int), 0) < 0) {
		puts("recv failed");
		return 0;
	}

	printf("Server reply :\n");
	printf("MIN %d\n",out[0]);
	printf("MAX %d\n",out[1]);
	printf("AVG %d\n",out[2]);
	// close the socket
	close(sockid);
	return 0;
}
