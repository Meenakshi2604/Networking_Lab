#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void find(int[], int,int[]);

// Driver code
int main(int argc, char* argv[])
{
	int socketid, clientid, c, read_size;
	struct sockaddr_in server, client;
	int message[10], i;
	int out1[3];

	// Create socket
	socketid = socket(AF_INET, SOCK_STREAM, 0);
	if (socketid == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);

	// Bind the socket
	if (bind(socketid, (struct sockaddr*)&server, sizeof(server)) < 0) {

		// print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	// listen to the socket
	listen(socketid, 3);

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	// accept connection from an incoming client
	clientid = accept(socketid, (struct sockaddr*)&client, (socklen_t*)&c);

	if (clientid < 0) {
		perror("accept failed");
		return 1;
	}

	puts("Connection accepted");

	// Receive a message from client
	while ((read_size = recv(clientid, &message, 10 * sizeof(int), 0)) > 0) {

		find(message, 10,out1);

		write(clientid, &out1, 3 * sizeof(int));
	}

	if (read_size == 0) {
		puts("Client disconnected");
	}
	else if (read_size == -1) {
		perror("recv failed");
	}

	return 0;
}


void find(int list[], int n,int out2[])
{
	int c, d, t;
	int max=list[0];
	int min=list[0];
	float avg=list[0];
	for(int i=1;i<10;i++)
	{
	if(list[i]>max)
		max=list[i];
	if(list[i]<min)
		min=list[i];
	avg+=list[i];
	}
	out2[0]=min;
	out2[1]=max;
	out2[2]=(int)(avg/10);
}
