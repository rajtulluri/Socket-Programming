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
	int sendb, recvb,l,flag = 0;
	char buff1[50],buff2[50],buff[50];
	struct sockaddr_in server,client;
	FILE *fptr;
	pid_t cpid;
	char ipv4[50];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Socket creation error\n" );
		exit(0);
	}
	printf("Socket created\n" );
	server.sin_family = AF_INET;
	server.sin_port = htons(3380);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server)) == -1){
		printf("Socket not bound\n");
		exit(0);
	}
	printf("Socket bound\n" );
	listen(sockfd,5);

	for(;;){
		len = sizeof(client);
		afd = accept(sockfd,(struct sockaddr*)&client,&len);
		if(afd==-1){
			printf("Client not connected\n" );
			exit(0);
		}
		if(flag == 2){
			printf("Too many clients shutting down\n");
			close(afd);
			close(sockfd);
			exit(0);
		}
		printf("Client connected\n");
		l = inet_ntop(AF_INET,&client,ipv4,sizeof(ipv4));
		printf("Accepted client - %s : %d\n",&ipv4,ntohs(client.sin_port));
		flag++;
		printf("%d\n", flag);
		cpid = fork();
		if(cpid == 0){
			if(flag == 1){
				recvb = recv(afd,&buff1,sizeof(buff),0);
				printf("%s\n", &buff1);	
			}
			if(flag == 2){
				recvb = recv(afd,&buff2,sizeof(buff),0);
				printf("%s\n", &buff2);	
			}
			fptr = fopen("tmp.txt","r");
			fgets(buff,8,fptr);

			if(flag == 2){
				printf("%s ",buff );
				if(strcmp(buff1,"Institute of")==0){
					printf("%s %s", buff1,buff2);
				}
				else{
					printf("%s %s", buff2,buff1);
				}
			}
			
			close(afd);

		}
	}

	close(sockfd);
}
