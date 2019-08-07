#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORTNO 8000

int CreateClientSocket()
{
	return socket(AF_INET, SOCK_STREAM,0);
}

void PerformServerTask(int sockid, struct sockaddr_in seraddr)
{
	int newsockfd, portno,clilen,n=1;
	struct sockaddr_in cliaddr;
	int i, value;

	bind(sockid,(struct sockaddr*)&seraddr,sizeof(seraddr));
	listen(sockid,5);
	while(1)
	{
		char buf[256];
		printf("server waiting \n");
		clilen=sizeof(clilen);
		newsockfd=accept(sockid,(struct sockaddr *)&cliaddr,&clilen);
		n=read(newsockfd,buf,sizeof(buf));
		printf("\n Message from client %s \n",buf);
		n=write(newsockfd,buf,sizeof(buf));
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
	struct sockaddr_in seraddr;
	sockfd= CreateClientSocket();

	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=INADDR_ANY;
	seraddr.sin_port=htons(PORTNO);

	PerformServerTask(sockfd, seraddr);
	TerminateSocket(sockfd);
}