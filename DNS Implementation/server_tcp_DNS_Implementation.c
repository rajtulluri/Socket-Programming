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
	int sendb, recvb;
	char buff[50];
	struct sockaddr_in server,client;
	FILE *fptr;
	char word[50];
	char *token;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Socket creation error\n" );
		exit(0);
	}
	printf("Socket created\n" );
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server)) == -1){
		printf("Socket not bound\n");
		exit(0);
	}
	printf("Socket bound\n" );
	listen(sockfd,1);
	len = sizeof(client);
	afd = accept(sockfd,(struct sockaddr*)&client,&len);
	if(afd==-1){
		printf("Client not connected\n" );
		exit(0);
	}
	printf("Client connected\n");

	recvb = recv(afd,&buff,sizeof(buff),0);

	fptr = fopen("database.txt","r");
	int flag = 0;
	while(fgets(word,sizeof(word),fptr)){
		token = strtok(word,"-");
		if(strstr(token,buff)){
			flag = 1;
			token = strtok(NULL,"-");
			strcpy(buff,token);
		}
	}
	if(flag == 0){
		strcpy(buff,"No such domain in database");
	}
	sendb = send(afd,&buff,sizeof(buff),0);
	close(sockfd);
}