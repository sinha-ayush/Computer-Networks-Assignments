#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define channelPort 1976

int main(void){

    printf("Client Started \n\n");
    int senderSocket = socket(AF_INET, SOCK_STREAM , 0);
    if(senderSocket<0) perror("SOCKET WAS NOT CREATED :: \n");
    
    struct sockaddr_in channel;
    memset(&channel, '\0', sizeof(struct sockaddr_in));
    channel.sin_addr.s_addr = inet_addr("127.0.0.1");
    channel.sin_port = htons(channelPort);
    channel.sin_family = AF_INET;
    
    int connectionSocket = connect(senderSocket, (struct sockaddr *)&channel, sizeof(channel));
    if(connectionSocket<0) perror("CHANNEL NOT CONNECTED \n");    
    
    char response[200];
    printf("ENTER DATA :\n"); 
    char *request; scanf("%s",request);

    send(senderSocket , request , 5 , 0 );
    printf("FRAME SENT %s\n",request);

    if(recv(senderSocket , response , 5 , 0) < 0)
    perror("NOT RECEIVED");
    else printf("%s RECEIVED\n\n",response);
 
    return 0;
}