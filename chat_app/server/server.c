#include<sys/types.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{ 	
	struct sockaddr_in servaddr, cliaddr;
	int portnumber = 1213;
	//creating a socket 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket Id : %d \n", sockfd);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(portnumber);
	
	int b = bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	if(b < 0)
	{
		printf("\nBinding failed\n");
		return 0;
	}
	
	printf("\nBinding successful\n");
	
	listen(sockfd, 3);
	
	int addrlen = sizeof(servaddr);
	

	int new_sock = accept(sockfd, (struct sockaddr*) &servaddr, (socklen_t*)&addrlen);
	
	if(new_sock >= 0)
	printf("Connection established!");
	
	printf("\n\nChat:\n-----");

	while(1){

		char s_msg[1000], r_msg[1000];
		
		printf("\nServer: ");
		fgets(s_msg, 1000, stdin);
		send(new_sock, s_msg, 1000, 0);
		if(strcmp(s_msg, "bye\n") == 0)
		{
			printf("\nEnd of chat");
			printf("\n-----x-----\n");
			break;
		}
		
		recv(new_sock, r_msg, 1000, 0);
		printf("\nClient: %s",r_msg);
		
		if(strcmp(r_msg, "bye\n") == 0)
		{
			printf("\nEnd of chat");
			printf("\n-----x-----\n");
			break;
		}			
	}	
	close(sockfd);
	return 0;
}

