#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
/*
 * Cliente UDP
 */
int main(argc, argv)
int argc;
char **argv;
{

   int s, server_address_size;
   unsigned short port;
   struct sockaddr_in server;
   char comando[200];
   char aux[2000];

   /* 
    * O primeiro argumento (argv[1]) � o endere�o IP do servidor.
    * O segundo argumento (argv[2]) � a porta do servidor.
    */
   if(argc != 3)
   {
      printf("Use: %s enderecoIP porta\n",argv[0]);
      exit(1);
   }
  port = htons(atoi(argv[2]));

   /*
    * Cria um socket UDP (dgram).
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /* Define o endere�o IP e a porta do servidor */
   server.sin_family      = AF_INET;            /* Tipo do endere�o         */
   server.sin_port        = port;               /* Porta do servidor        */
   server.sin_addr.s_addr = inet_addr(argv[1]); /* Endere�o IP do servidor  */

char a[200]="exit";
   
do{
for(int i=0;i<200;i++)
{
comando[i]='\0';
}
printf("\n>");
	scanf("%s", comando);
   /* Envia a mensagem no buffer para o servidor */
   if (sendto(s, comando, (strlen(comando)+1), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
   {
       perror("sendto()");
       exit(2);
   }

if(recvfrom(s, aux, sizeof(aux)+1, 0, (struct sockaddr *) &server,
            &server_address_size) <0)
   {
       perror("recvfrom()");
       exit(1);
   }
printf("%s", aux);
}while(strcmp(a, comando)!=0);

   /* Fecha o socket */
   close(s);
}
