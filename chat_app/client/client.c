#include<netinet/in.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	struct sockaddr_in servaddr,cliaddr;
	int port;
	printf("ENter port: ");
	scanf("%d", &port);
	int csd=socket(AF_INET,SOCK_STREAM,0);
	if(csd>0)
	{
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		servaddr.sin_port=htons(port);
		int x=connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr));
		printf("Successful connection!\n");
	}
	else
	{
		printf("UNSUCCESFUL");
		return 0;
	}
	
	printf("\nChat:\n-----");

	while(1){
		
		char r_msg[1000];
		
		recv(csd, r_msg, 1000, 0);
		printf("\nServer: %s",r_msg);
		
		if(strcmp(r_msg, "bye\n") == 0)
		{
			printf("\nEnd of chat");
			printf("\n-----x-----\n");
			break;
		}	
		
		char s_msg[1000];
		printf("\nClient: ");		
		fgets(s_msg, 1000, stdin);
		send(csd, s_msg, 1000, 0); 
		if(strcmp(s_msg, "bye\n") == 0)
		{
			printf("\nEnd of chat");
			printf("\n-----x-----\n");
			break;
		}	
	}
	
	close(csd);
	return 0;			
}
