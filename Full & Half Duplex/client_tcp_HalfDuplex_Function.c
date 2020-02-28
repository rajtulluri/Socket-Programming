#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int sockfd,afd;
	socklen_t len;
	int sendb, recvb, ch,l,k;
	char buff[50];
	char wrd[10],repwrd[10];
	char res[20];
	char arr[50][50];
	struct sockaddr_in server,client;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	len = sizeof(server);

	printf("Enter message -\n");
	fflush(stdout);
	scanf("%s",&buff);
	sendb = sendto(sockfd,&buff,sizeof(buff),0,&server,len);
	close(sockfd);
}