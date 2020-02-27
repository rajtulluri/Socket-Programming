#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int sockfd;
	int sendb,recvb;
	int res,ele,ch,n,b[60];
	int r[60], o[30], e[30];
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

	while (1) {

		printf("Enter length of array\n");
		fflush(stdout);
		scanf("%d",&n );
		b[0] = n+3;
		printf("Enter array\n");
		fflush(stdout);
		for(int i=3;i<n+3;i++){
			scanf("%d",&b[i]);
		}
		fflush(stdout);
		printf("Enter choice\n");
		printf("1.Search 2.Sort 3.Odd/Even 4.Exit\n" );
		fflush(stdout);
		scanf("%d",&ch );
		b[1] = ch;
		switch (ch) {
			case 1:
				printf("Enter element to search\n");
				scanf("%d",&ele );
				b[2] = ele;
				sendb = send(sockfd,&b,sizeof(b),0);
				recvb = recv(sockfd,&res,sizeof(int),0);
				printf("Search result - %d\n",res );
			 	break;
			case 2:
				printf("1.Ascending 2.Descending\n");
				scanf("%d",&ele);
				b[2] = ele;
				sendb = send(sockfd,&b,sizeof(b),0);
				recvb = recv(sockfd,&r,sizeof(r),0);
				printf("The sorted array - \n" );
				for(int i=3;i<n+3;i++){
					printf("%d\n",r[i]);
				}
				break;
			case 3:
				sendb = send(sockfd,&b,sizeof(b),0);
				recvb = recv(sockfd,&o,sizeof(o),0);
				printf("The even array - \n" );
				for(int i=1;i<o[0];i++){
					printf("%d\n",o[i] );
				}
				recvb = recv(sockfd,&e,sizeof(e),0);
				printf("The odd array - \n" );
				for(int i=1;i<e[0]-1;i++){
					printf("%d\n",e[i] );
				}
				break;
			case 4:
				close(sockfd);
				exit(0);
				break;
		}
	}

	close(sockfd);
}
