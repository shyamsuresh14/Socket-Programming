#include<sys/types.h>
//#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{ 	
	struct sockaddr_in servaddr, cliaddr;
	int portnumber = 1213;
	char accids[3][10] = {"1234\n", "5678\n", "9012\n"};
	char pins[3][10] = {"aaaa\n", "bbbb\n", "cccc\n"};
	
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
	
	printf("\n\n ATM:\n-----\n");
	
	int ind=-1, lin=-1, x = 1; 
	while(1){
		printf("\nIteration: %d", x++);
		char msg[100],accid[10],pin[10];
		if(ind == -1)
		{
			int s = send(new_sock, "Enter account id: ", 100, 0);
			//wait(NULL);
			int r = recv(new_sock, accid, 10, 0);  
			printf("\nSend: %d, Receive: %d, Received: %s", r, s, accid);	
			int i;
			for(i=0; i<3; i++)
			{
				if(strcmp(accid, accids[i]) == 0)
				{
					ind = i; 
					send(new_sock, "Enter pin: ", 100, 0);
					break;
				}	
			}
			if(ind == -1)	
			{
				send(new_sock, "Account not found!", 100, 0);	
			}
		}
	}	
	/*
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
	*/	
	close(sockfd);
	return 0;
}

