#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//bibliotecas para socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORTA 2000
#define LEN 4096
struct sockaddr_in local;
struct sockaddr_in remoto;

int main (int argc, char **argv){
	
	int sock;
	int client;
	int slen;
	int len = sizeof(remoto);
	char buffer[4096];
	
	
	
	sock = socket(AF_INET, SOCK_STREAM,0);
	
	if (sock == -1)
	{
		perror("socket");
		exit(1);
		}else
			printf("socket criado \n");
		
	local.sin_family = AF_INET;
	local.sin_port = htons(PORTA);
	//local.sin_addr.s_addr = inet_addr("ip");
	memset(local.sin_zero, 0x0, 8);
	
	if(bind(sock,(struct sockaddr*)&local, sizeof(local) ) == -1)
	{
		perror("bind ");
		exit(1);
		}
		
		
		
	listen(sock,1);
	
	
	
	
	if((client = accept(sock, (struct sockaddr*)&remoto, &len)) == -1)
		{
			perror("accept");
			exit(1);
			}
	
	strcpy(buffer,"Bem vindo\n\0");
	
	if(send(client,buffer, strlen(buffer), 0))
	{
		printf("Aguardando resposta\n");
		while(1){
			memset(buffer, 0x0, len);
			if((slen = recv(client,buffer,LEN,0))>0){
				buffer[slen] = '\0';
				printf("mensagem recebida %s\n",buffer);
				Sclose(client);
				break;
				}
			}
		}
	
	printf("conexão encerrada");
	
	close(sock);
	


		close();
	return 0;
	}
