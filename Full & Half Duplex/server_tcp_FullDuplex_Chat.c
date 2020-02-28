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
	char s_buff[50],r_buff[50];
	char arr[50][50];
	struct sockaddr_in server,client;
	pid_t pid;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))==-1){
		printf("Socket not bound\n");
		close(sockfd);
		exit(0);
	}else{
		printf("Socket bound\n");
	}

	len = sizeof(client);
	listen(sockfd,1);
	afd = connect(sockfd,(struct sockaddr*)&client,len);
	if(afd == -1){
		printf("Client not connected\n");
	}else{
		printf("Client connected\n");
	}

	if((pid= fork())==0){
		while(1){
			printf("\t");
			scanf("%s",&s_buff);
			sendb = send(afd,&s_buff,sizeof(s_buff),0);
		}
	}else{
		while(1){
			recvb = recv(afd,&r_buff,sizeof(r_buff),0);
			printf("\t\t\t\t\t%s\n", &r_buff);
		}
	}

	close(sockfd);
}