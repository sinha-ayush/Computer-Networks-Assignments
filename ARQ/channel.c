#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define receiverPort 2015
#define channelPort 1975

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

    
    while (1){

    char response[6];
    printf("Channel Started \n");
    if(recv(newSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");
    else printf("DATA RECEIVED  :: %s\n",response);
    // int k = strlen(response);
    // int r = rand() % k;
    // printf("INDUCING BIT ERROR AT POSITION %d\n",r+1);
    // response[r] = (response[r]=='1')?'0':'1';     
    // printf("NEW RESPONSE %s\n",response);

    // printf("ADDING %d SECONDS DELAY\n",r);
    // sleep(r);
    
    if(send(receiverSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");

    if(recv(receiverSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");

    if(send(newSocket , response , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");
    printf("%s\n",response);

    printf("\n");
    }


    return 0;
}