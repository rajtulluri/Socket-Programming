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
	char s_buff[50],r_buff[50];
	struct sockaddr_in server,client;
	pid_t pid;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	len = sizeof(server);
	if(connect(sockfd,(struct sockaddr*)&server,len) == -1){
		printf("Connected to server failed\n");
		exit(0);
	}
	printf("Connected\n");

	if((pid=fork())==0){
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