#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    char hello[]="hello world";
    struct sockaddr_in sa;
    int SocketFD=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(SocketFD==-1){
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }
    memset(&sa,0,sizeof sa);
    sa.sin_family=AF_INET;
    sa.sin_addr.s_addr=htonl(INADDR_ANY);
    sa.sin_port=htons(1815);
    if(bind(SocketFD,(struct sockaddr*)&sa,sizeof sa)==-1){
        perror("bind failed");
        close(SocketFD);
        exit(EXIT_FAILURE);

    }
    if(listen(SocketFD,20)==-1){
        perror("listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);

    }
    for(;;){
        int ConnectFD=accept(SocketFD,NULL,NULL);
        if(ConnectFD<0){
            perror("accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);

        }
        int WriteSize=0;
        size_t TotalSize=0;
        while(TotalSize<sizeof(hello)){
            WriteSize=write(ConnectFD,hello+TotalSize,sizeof(hello)-TotalSize);
            if(WriteSize==-1){
                perror("write failed");
                close(ConnectFD);
                close(SocketFD);
                exit(EXIT_FAILURE);
            }
            TotalSize+=WriteSize;
            }
            if(shutdown(ConnectFD,SHUT_RDWR)==-1){
                perror("shutdown failed");
                close(ConnectFD);
                close(SocketFD);
                exit(EXIT_FAILURE);
            }
            close(ConnectFD);
        }
        close(SocketFD);
        return EXIT_SUCCESS;
    }
    
