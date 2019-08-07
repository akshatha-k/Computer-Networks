#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>


int CreateClientSocket()
{
	return socket(AF_INET, SOCK_STREAM, 0);
}

void ConnecttoServer(int sockid, struct sockaddr_in address)
{
	int result;
	int len=sizeof(address);
	result= connect(sockid,(struct sockaddr*)&address,len);
	if(result==-1)
	{
		perror("\n CLIENT ERROR");
		exit(1);
	}
}

void PerformClientTask(int sockid)
{
	int n=1;
	char ch[256],buf[256];
	printf("\n Enter String\t");
	gets(ch);
	ch[strlen(ch)]='\0';
	write(sockid,ch,strlen(ch));
	printf("String sent back from server is ... ");
	while(n)
	{
		n=read(sockid, buf, sizeof(buf));
		puts(buf);
	}

}

void TerminateSocket(int sockid)
{
	int status= close(sockid);
	if (status == -1)
	{
		perror("\n Error");
		exit(1);
	}
}


int main()
{
	int sockfd;
	struct sockaddr_in address;
	sockfd = CreateClientSocket();

	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(8000);
	
	ConnecttoServer(sockfd, address);
	PerformClientTask(sockfd);
	TerminateSocket(sockfd);
}