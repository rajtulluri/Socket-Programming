#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int search(FILE *f,char b[]){
	char word[10];
	int ctr=0;
	while(fgets(word,sizeof(word),f)){
		if(strstr(word,b)){
			ctr++;
		}
	}
	return ctr;
}

int main()
{
	int sockfd,afd;
	socklen_t *len;
	int sendb, recvb, ch,l,k;
	char buff[50];
	char wrd[10],repwrd[10];
	char res[20];
	char arr[50][50];
	char b[] = "Output.txt";
	struct sockaddr_in server,client;
	FILE *fptr;
	FILE *fptr2;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
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
	len = sizeof(client);

	while(1){
		printf("Here\n");
		recvb = recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
		if(recvb){
			printf("%s\n", &buff);
		}else{
			printf("Fail\n");
		}
		fptr = fopen(buff,"r");
		if(fptr == NULL){
			char response[] = "No such file";
			sendb = sendto(sockfd,&response,sizeof(response),0,(struct sockaddr*)&client,len);
			close(fptr);
			close(sockfd);
			exit(0);
		}else{
			char response[] = "File opened";
			sendb = sendto(sockfd,&response,sizeof(response),0,(struct sockaddr*)&client,len);
		}
		recvb = recvfrom(sockfd,&ch,sizeof(ch),0,(struct sockaddr*)&client,len);
		switch(ch){
			case 1:
				recvb = recvfrom(sockfd,&wrd,sizeof(wrd),0,(struct sockaddr*)&client,len);
				l = search(fptr,wrd);
				if(l){
					sprintf(res,"%d",l);
				}else{
					sprintf(res,"%s","No String found");
				}
				sendb = sendto(sockfd,&res,sizeof(res),0,(struct sockaddr*)&client,len);
				break;
			case 2:
				fptr2 = fopen(b,"w");
				recvb = recvfrom(sockfd,&wrd,sizeof(wrd),0,(struct sockaddr*)&client,len);
				recvb = recvfrom(sockfd,&repwrd,sizeof(repwrd),0,(struct sockaddr*)&client,len);
				char word[20];
				while(fgets(word,sizeof(word),fptr)){
					if(strstr(&word,&wrd)){
						fprintf(fptr2, "%s",&repwrd);
						fflush(fptr2);
					}else{
						fprintf(fptr2, "%s",&word);
						fflush(fptr2);
					}
				}
				close(fptr2);
				break;
			case 3:
				fptr2 = fopen(b,"w");
				k=0;
				while(fgets(wrd,sizeof(wrd),fptr)){
					strcpy(arr[k],wrd);
					k++;
				}
				for(int i=0;i<=k;i++){
					for(int j=i+1;j<=k;j++){
						if(strcmp(arr[i],arr[j]) > 0){
							strcpy(repwrd,arr[i]);
							strcpy(arr[i],arr[j]);
							strcpy(arr[j],repwrd);
						}
					}
				}
				for(int i=0;i<=k;i++){
					fprintf(fptr2, "%s\n",arr[i] );
					fflush(fptr2);	
				}
				close(fptr2);
				break;
			case 4:
				close(fptr2);
				close(fptr);
				close(sockfd);
				exit(0);
				break;
		}
	}
	close(fptr2);
	close(fptr);
	close(sockfd);
}
