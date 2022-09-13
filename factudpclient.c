#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
void main()
{
struct sockaddr_in server_address;
int socket_descriptor,fact;
int message;
socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
server_address.sin_family=AF_INET;
server_address.sin_port=3000;
server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(socket_descriptor,(struct sockaddr *)&server_address,sizeof(server_address));
while (1)
{
printf("client : ");
scanf("%d",&message);
sendto(socket_descriptor,&message,sizeof(message),0,(struct sockaddr *)&server_address,sizeof(server_address));
recvfrom(socket_descriptor,&fact,sizeof(int),0,NULL,NULL);
printf("Factorial of the number is: %d \n",fact);

}

}
