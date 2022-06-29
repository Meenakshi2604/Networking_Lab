#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0 );
	float number;
	printf("Enter a number: ");
	scanf("%f", &number);
	if(sockfd>0)
	{
		struct sockaddr_in address;
		address.sin_family=AF_INET;
		address.sin_addr.s_addr= INADDR_ANY;
		address.sin_port=htons(9840);

		if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
			perror("Connection failed. Error");
			exit(1);
		}

		puts("Connected\n");
		send(sockfd,&number,sizeof(float),0);
	}
	else
	{
		printf("Error in socket creation\n");
		exit(1);
	}
}
