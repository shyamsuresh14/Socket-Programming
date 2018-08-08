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

	close(sockfd);
	return 0;
}

