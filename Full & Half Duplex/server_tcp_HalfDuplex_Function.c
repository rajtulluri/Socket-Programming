#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int i, int n,char arr[][50])
{
    int j;
    if (i == n){
        sprintf(arr[i],"%s\n", a);
    	printf("%s\n", a);
    }
    else {
        for (j = i; j <= n; j++)
        {
            swap((a + i), (a + j));
            permute(a, i + 1, n,arr);
            swap((a + i), (a + j));
        }
    }
}

int main()
{
	int sockfd,afd;
	socklen_t len;
	int sendb, recvb;
	char buff[50];
	char arr[50][50];
	struct sockaddr_in server,client;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
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

	len = sizeof(server);
	recvb = recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	printf("%s\n", &buff);
	permute(buff,0,strlen(buff)-1,arr);

}