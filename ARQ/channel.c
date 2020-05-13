#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define receiverPort 2016
#define channelPort 1976

int main(void){
    printf("Channel Started \n");
    int senderSocket = socket(AF_INET, SOCK_STREAM , 0);
    if(senderSocket<0) printf("SOCKET WAS NOT CREATED");

    struct sockaddr_in channel;
    memset(&channel, '\0', sizeof(struct sockaddr_in));
    channel.sin_addr.s_addr = INADDR_ANY;
    channel.sin_port = htons(channelPort);
    channel.sin_family = AF_INET; 

    int receiverSocket = socket(AF_INET, SOCK_STREAM , 0);
    if(receiverSocket<0) 
    printf("SOCKET WAS NOT CREATED");

    struct sockaddr_in receiver;
    receiver.sin_addr.s_addr = inet_addr("127.0.0.1");
    receiver.sin_port = htons(receiverPort);
    receiver.sin_family = AF_INET; 
    
    if(bind(senderSocket, (struct sockaddr *)&channel, sizeof(channel))<0) 
    perror("BINDING FAILED :: ");
    listen(senderSocket , 5);
    int c = sizeof(struct sockaddr);
    int newSocket = accept(senderSocket, (struct sockaddr *)&channel, (socklen_t *)&c);
    if(newSocket<0) 
    perror("ACCEPTING FAILED :: ");

    int connectionSocket = connect(receiverSocket, (struct sockaddr *)&receiver, sizeof(receiver));
    if(connectionSocket<0) 
    printf("CHANNEL NOT CONNECTED");    

    char response[5];

    if(recv(newSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");
    else printf("DATA RECEIVED  :: %s\n",response);
    
    if(send(receiverSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");

    if(recv(receiverSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");

    if(send(newSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");
    printf("%s\n",response);

    return 0;
}