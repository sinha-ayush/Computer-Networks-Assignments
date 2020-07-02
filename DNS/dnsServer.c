#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8082
#define MAXLINE 1024 
 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char string[MAXLINE]; 
    struct sockaddr_in servaddr, cliaddr;
    char domainName[5][MAXLINE] = {"www.anindya.com","www.google.com","www.yahoo.com","www.facebook.com","www.amazon.com"}; 
    char ipAddr[5][MAXLINE] = {"0.0.0.0","1.1.1.1","2.2.2.2","3.3.3.3","4.4.4.4"}; 
     
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
    len = sizeof(cliaddr);
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len);  
    for(int i=0;i<5;i++){
     if(strncmp(buffer,domainName[i],7)==0) {strcpy(string,ipAddr[i]);break;}
     else strcpy(string,"NOT FOUND");
    }

    sendto(sockfd, (const char *)string, strlen(string),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len);  
      
    return 0; 
} 
