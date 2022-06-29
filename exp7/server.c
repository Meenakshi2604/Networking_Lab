#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>

struct recvData{
	int n;
	int i;
	int* client_fd;
};

void* serverRecv(void* data){
	char str[20];
	struct recvData data1 = *((struct recvData*)data);
	
	while(1){
		int k = recv(data1.client_fd[data1.i], str, 20*sizeof(char), 0);
		
		if(k<0){
			print("Receive failed \n");
			exit(1);
		}else if(k == 0){
			print("Client %d exited", data.i+1);
			exit(1);
		}else{
			printf("Received message from client %d: %s\n", d.i + 1, str);
		}
		
		for(int j=0; j<data1.n;j++){
			if(j != data1.i){
				if(send(data1.client_fd[j], str, (strlen(str) + 1) * sizeof(char), 0) < 0) {
					printf("Send failed!\n");
					exit(1);
				} else {
					printf("Message sent to client %d.\n", j + 1);
				}
			}
		}
	}	
}

void main(){
	int server_fd, n;
	struct sockaddr_in address, cli_addr1, cli_addr2;
	int addrlen = sizeof(address);
	
	printf("Chat Server\n");
	
	printf("Enter no. of clients: ");
	scanf("%d", &n);
	
	int client_fd[n];
	
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation failed!\n");
		exit(1);
	} else {
		printf("Server socket created.\n");
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	if(bind(server_fd, (struct sockaddr*) &address, addrlen) < 0) {
		printf("Socket binding failed!\n");
		exit(1);
	} else {
		printf("Socket binded.\n");
	}
	
	if(listen(server_fd, n) < 0) {
		printf("Listening failed!\n");
		exit(1);
	} else {
		printf("Server listening.\n");
	}
	
	for(int i = 0; i < n; i++) {
		if((client_fd[i] = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
			printf("Connection failed!\n");
			exit(1);
		} else {
			printf("Connected to client %d.\n", i+1);
		}
	}
	
	pthread_t tid[n];
	
	recvData data[n];
	
	for(int i = 0; i < n; i++) {
		data[i].i = i;
		data[i].n = n;
		data[i].client_fd = client_fd;
		
		pthread_create(&tid[i], NULL, serverRecv, &data[i]);
	}
	
	for (int i = 0; i < n; i++) {	
		pthread_join(tid[i], NULL);
	}
	
	for(int i = 0; i < n; i++) {
		close(client_fd[i]);
	}
	
	close(server_fd);
}
