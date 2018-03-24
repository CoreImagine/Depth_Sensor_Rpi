#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[])

{
    //socket的建立
    char inputBuffer[256] = {};
    char recv_key[256] = {"s"};
    uint16_t message[100001];
    int index;
    printf("start!");
    for(index=0;index<100000;index++)
    {
    	message[index]=index;
    }
    message[100000]=0xFFFF;
    //message[11]=0xFF;
    printf("gen done!");


    //char message[] = {"Hi,this is server.\n"};
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    listen(sockfd,5);

   // while(1){
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        //send(forClientSockfd,test_char,1,0);
        recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("Get:%s\n",inputBuffer);
	if(strcmp(inputBuffer,recv_key)==0){
	printf("true");
        send(forClientSockfd,message,sizeof(message),0);
	}
   // }
   close(sockfd);
    return 0;
}
