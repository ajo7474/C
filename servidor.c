#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
int    meu_socket;
int    sock_cliente;
struct sockaddr_in addr;

meu_socket = socket(AF_INET,SOCK_STREAM,0);

if(meu_socket == -1)
  {
  printf("Erro ao criar o socket!\n");
  return 1;
  }

addr.sin_family      = AF_INET;
addr.sin_port        = htons(1234);
addr.sin_addr.s_addr = INADDR_ANY;

memset(&addr.sin_zero,0,sizeof(addr.sin_zero));

if(bind(meu_socket,(struct sockaddr*)&addr,sizeof(addr)) == -1)
  {
  printf("Erro na funcao bind()\n");
  return 1;
  }

if(listen(meu_socket,1) == -1)
  {
  printf("Erro na funcao listen()\n");
  return 1;
  }

printf("Aguardando conexoes...\n");

sock_cliente = accept(meu_socket,0,0);

if(sock_cliente == -1)
  {
  printf("Erro na funcao accept()\n");
  return 1;
  }
int recebidos, enviados;
char mensagem[256];
char resposta[256];

do
  {
  
  /* O processo inverso é feito aqui. Como o servidor espera uma mensagem inicialmente, o cliente deverí fornecê-la */

  printf("Cliente: ");
  fgets(mensagem,256,stdin);
  mensagem[strlen(mensagem)-1] = '\0';
  enviados = send(meu_socket,mensagem,strlen(mensagem),0);

 /* Após enviar a mensagem, espera-se a resposta do servidor */

  recebidos = recv(meu_socket,resposta,256,0);
  resposta[recebidos] = '\0';
  printf("Servidor: %s\n",resposta);
  

  }while(recebidos != -1 && enviados != -1);


close(sock_cliente);         
close(meu_socket);       
return 0;
}
