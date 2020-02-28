#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int find_anagram(char a[],char b[]){
	int n1[26],n2[26]={0};
	int i=0;
	while(a[i] != '\0'){
		n1[a[i] - 'a']++;
		i++;
	}
	i=0;
	while(b[i] != '\0'){
		n2[b[i]-'a']++;
		i++;
	}
	for(i=0;i<26;i++){
		if(n1[i] != n2[i])
			return 0;
	}
	return 1;
}

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
	time_t now;
	time(&now);

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
	listen(sockfd,5);

	for(;;){
		len = sizeof(client);
		afd = accept(sockfd,(struct sockaddr*)&client,&len);
		if(afd==-1){
			printf("Client not connected\n" );
			exit(0);
		}

		l = inet_ntop(AF_INET,&client,ipv4,sizeof(ipv4));
		printf("Accepted client - %s : %d : %s",&ipv4,ntohs(client.sin_port),ctime(&now));

		recvb = recv(afd,&buff1,sizeof(buff),0);
		printf("%s\n", buff1);
		recvb = recv(afd,&buff2,sizeof(buff),0);
		printf("%s\n", buff2);

		if(find_anagram(buff1,buff2)){
			strcpy(buff,"Anagram");
			sendb = send(afd,buff,sizeof(buff),0);
		}else{
			strcpy(buff,"Not Anagram");
			sendb = send(afd,buff,sizeof(buff),0);
		}

	}
	close(sockfd);
}