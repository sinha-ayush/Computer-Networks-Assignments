#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define channelPort 1975
int main(void){

    printf("Client Started \n\n");
    int senderSocket = socket(AF_INET, SOCK_STREAM , 0);
    // if(senderSocket<0) perror("SOCKET WAS NOT CREATED :: \n");
    
    struct sockaddr_in channel;
    memset(&channel, '\0', sizeof(struct sockaddr_in));
    channel.sin_addr.s_addr = inet_addr("127.0.0.1");
    channel.sin_port = htons(channelPort);
    channel.sin_family = AF_INET;
    
    int connectionSocket = connect(senderSocket, (struct sockaddr *)&channel, sizeof(channel));
    char response[200];

    if(connectionSocket<0) perror("CHANNEL NOT CONNECTED \n");    
    
    printf("ENTER DATA :\n"); 
    char *request; scanf("%s",&request);

    while(1){
    SEND : send(senderSocket , request , 5 , 0 );
    printf("FRAME SENT %s\n\n",request);
    
    //5 seconds timer 
    int counter =0, received = 0; 
    while(counter<5){
        printf("%d seconds left\n",counter);
        if(recv(senderSocket , response , 5 , MSG_DONTWAIT) >= 0){
            received = 1;
            break;
        }
        sleep(1);
        counter++;
    }

    if(received) printf("%s", response);
    else {
    printf("RETRANSMITTING\n\n"); 
    goto SEND;
    }
    
    }
    return 0;
}