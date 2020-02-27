#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int num_search(int* a,int ele,int n){
	for(int i=3;i<n;i++){
		if(a[i] == ele){
			return i-3;
		}
	}
	return 0;
}

void sort(int* a,int n,int ch){
	int temp;
	if(ch == 1){
		for(int i=3;i<n;i++){
			for(int j=3;j<n-1;j++){
				if(a[j] >= a[j+1]){
					temp = a[j];
					a[j] = a[j+1];
					a[j+1] = temp;
				}
			}
		}
	}else{
		for(int i=3;i<n;i++){
			for(int j=3;j<n-1;j++){
				if(a[j] <= a[j+1]){
					temp = a[j];
					a[j] = a[j+1];
					a[j+1] = temp;
				}
			}
		}
	}
}

int odd_even_split(int* a, int n, int* o, int* e){
	int j=1,k=1;
	for(int i=3;i<n;i++){
		if(a[i] % 2 == 0){
			o[j] = a[i];
			j++;
		}else{
			e[k] = a[i];
			k++;
		}
	}
	return j;
}

int main()
{
	int sockfd,afd;
	socklen_t len;
	int sendb, recvb, l;
	int b[60];
	int res[60],odd[30],eve[30];
	int s_res,end;
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
	while (1) {
		recvb = recv(afd,&b,sizeof(b),0);
		switch (b[1]) {
			case 1:
				s_res = num_search(b,b[2],b[0]);
				sendb = send(afd,&s_res,sizeof(int),0);
				break;
			case 2:
				sort(b,b[0],b[2]);
				sendb = send(afd,&b,sizeof(b),0);
				break;
			case 3:
				end = odd_even_split(b,b[0],odd,eve);
				odd[0] = end;
				eve[0] = b[0] - end;
				sendb = send(afd,&odd,sizeof(odd),0);
				sendb = send(afd,&eve,sizeof(eve),0);
				break;
			case 4:
				close(sockfd);
				exit(0);
				break;
		}
	}
	close(sockfd);
}
