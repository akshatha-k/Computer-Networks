#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int len, result, sockfd, n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];
	sockfd = socket(AF_INET, SOCK_STREAM,0);

	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(8000);
	len=sizeof(address);
	result= connect(sockfd,(struct sockaddr*)&address,len);
	if(result==-1)
	{
		perror("\n CLIENT ERROR");
		exit(1);
	}
	printf("\n Enter String\t");
	gets(ch);
	ch[strlen(ch)]='\0';
	write(sockfd,ch,strlen(ch));
	printf("String sent back from server is ... ");
	while(n)
	{
		n=read(sockfd, buf, sizeof(buf));
		puts(buf);
	}
}