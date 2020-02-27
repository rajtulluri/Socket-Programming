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
	int sockfd;
	int sendb,recvb,ch;
	char buff[50];
	char res[20];
	char wrd[10],repwrd[10];
	struct sockaddr_in server;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Socket not bound\n");
		exit(0);
	}
	printf("Socket bound\n" );
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server)) == -1){
		printf("Connected to server failed\n");
		exit(0);
	}
	printf("Connected\n");

	while(1){
		printf("Enter a file name - \n");
		fflush(stdout);
		scanf("%s",buff);
		sendb = send(sockfd,buff,sizeof(buff),0);
		recvb = recv(sockfd,&res,sizeof(res),0);
		printf("%s\n",&res );
		fflush(stdin);
		printf("Enter choice\n");
		printf("1.Search 2.Replace 3.Reorder 4.Exit\n");
		fflush(stdout);
		scanf("%d",&ch);
		sendb = send(sockfd,&ch,sizeof(ch),0);

		switch(ch){
			case 1:
				printf("Enter word to search -\n");
				fflush(stdout);
				scanf("%s",&wrd);
				sendb = send(sockfd,&wrd,sizeof(wrd),0);
				recvb = recv(sockfd,&res,sizeof(res),0);
				printf("%s\n",&res );
				break;
			case 2:
				printf("Enter word to replace\n");
				fflush(stdout);
				scanf("%s",&wrd);
				sendb = send(sockfd,&wrd,sizeof(wrd),0);
				printf("Enter replacement word\n");
				fflush(stdout);
				scanf("%s",&repwrd);
				sendb = send(sockfd,&repwrd,sizeof(repwrd),0);
				break;
			case 4:
				close(sockfd);
				exit(0);
				break;
		}
	}
	close(sockfd);
}