#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int palindrome_check(char a[]){
	int s=0,e=0;	
	e = strlen(a) -1;
	while( e > s){
		if(a[s++] != a[e--]){
			return 0;
		}
	}
	return 1;
}

int count_vowel(char a[],char b){
	int ctr=0;
	for(int i=0;i<strlen(a);i++){
		if(a[i] == b){
			ctr++;
		}
	}
	return ctr;
}

int main()
{
	int sockfd,afd;
	socklen_t len;
	int sendb, recvb, l;
	char buff[50];
	int res[20];
	struct sockaddr_in server,client;

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

	while(1){
		recvb = recv(afd,&buff,sizeof(buff),0);
		l = palindrome_check(buff);
		res[0] = l;
		res[1] = strlen(buff);
		res[2] = count_vowel(buff,'a');
		res[3] = count_vowel(buff,'e');
		res[4] = count_vowel(buff,'i');
		res[5] = count_vowel(buff,'o');
		res[6] = count_vowel(buff,'u');
		//a=2,e=3,i=4,o=5,u=6
		sendb = send(afd,&res,sizeof(res),0);
	}

	close(sockfd);
}