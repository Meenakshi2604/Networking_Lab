#include<sys/socket.h>
#include<unistd.h>
#include<netinet/ip.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<math.h>

void main()
{
	float number, new_num;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd>0)
	{
		struct sockaddr_in address;
		address.sin_family=AF_INET;
		address.sin_addr.s_addr= INADDR_ANY;
		address.sin_port=htons(9840);
		int bindValue=bind(sockfd,(struct sockaddr*)&address,sizeof(address));
		if(bindValue<0)
		{
			printf("Bind failed\n");
			exit(1);
		}
		else
		{
			listen(sockfd,3);
			int addr = sizeof(&address);
			int new_socket=accept(sockfd,(struct sockaddr*)&address,(socklen_t*)&addr);
			if(new_socket<0)
			{
				printf("Could not accept the request");
				exit(1);
			}
			recv(new_socket, &number, sizeof(float), 0);
			printf("Number is: %f \n", number);
			new_num = pow(number, 1.5);
			
			int new_socket1=accept(sockfd,(struct sockaddr*)&address,(socklen_t*)&addr);
			if(new_socket1<0)
			{
				printf("Could not accept the request");
				exit(1);
			}
			send(new_socket1, &new_num, sizeof(float),0);
			printf("Message Sent \n");
		}
	}
	else
	{
		printf("Error in socket creation\n");
		exit(1);
	}
}
