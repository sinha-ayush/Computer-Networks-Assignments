#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define receiverPort 2015

int main(void){
    printf("Receiver Started \n");
    int senderSocket = socket(AF_INET, SOCK_STREAM , 0);
    if(senderSocket<0) printf("SOCKET WAS NOT CREATED");

    struct sockaddr_in receiver;
    memset(&receiver, '\0', sizeof(struct sockaddr_in));
    receiver.sin_addr.s_addr = INADDR_ANY;
    receiver.sin_port = htons(receiverPort);
    receiver.sin_family = AF_INET; 

    
    if(bind(senderSocket, (struct sockaddr *)&receiver, sizeof(receiver))<0) 
    perror("BINDING FAILED :: ");
    listen(senderSocket , 5);
    int c = sizeof(struct sockaddr);
    int newSocket = accept(senderSocket, (struct sockaddr *)&receiver, (socklen_t *)&c);
    if(newSocket<0) 
    perror("ACCEPTING FAILED :: ");

    char response[200];
    
    while (1){
    
    recv(newSocket , response , 5 , 0 );
    printf("%s\n",response);
    
    char *newresponse = "ACK";
    if(send(newSocket , newresponse , 5 , 0 )<0)
    perror("THE ISSUE IS :: ");

    printf("\n");   
    }
    return 0;
}