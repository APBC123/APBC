#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    struct sockaddr_in sa;
    int res;
    int SocketFD=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(SocketFD==-1){
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }
    memset(&sa,0,sizeof sa);
    sa.sin_family=AF_INET;
    //sa.sin_addr.s_addr=htonl(INADDR_ANY);
    sa.sin_port=htons(1815);
    res=inet_pton (AF_INET,"127.0.0.1",&sa.sin_addr);
    if(connect(SocketFD,(struct sockaddr*)&sa,sizeof sa)==-1){
        perror("connect failed");
        close(SocketFD);
        exit(EXIT_FAILURE);

    }
    char buffer[512];
    int TotalSize=0;
    for(;;){
        int ReadSize=0;
        ReadSize=read(SocketFD,buffer+TotalSize,sizeof(buffer)-TotalSize);
        
        if(ReadSize==0){
            break;
        }
        else if(ReadSize==-1){
            perror("read failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        TotalSize+=ReadSize;
    }
        buffer[TotalSize]=0;
        printf("get from server: %s\n",buffer);
        (void)shutdown(SocketFD,SHUT_RDWR);
        close(SocketFD);
        return EXIT_SUCCESS;


    }
    
