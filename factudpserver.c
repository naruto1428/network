#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
void main()
{
struct sockaddr_in client_address,server_address;
int socket_descriptor,n,fact=1;
int message,i;
socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
server_address.sin_family=AF_INET;
server_address.sin_port=3000;
server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(socket_descriptor,(struct sockaddr *)&server_address,sizeof(server_address));
n=sizeof(client_address);
while (1)
{
recvfrom(socket_descriptor,&message,sizeof(message),0,(struct sockaddr *)&client_address,&n);
printf("The Number is: %d\n",message);
for(i=1;i<=message;i++)
{
  fact=fact*i;   
}
printf("client : %d\n",fact);
sendto(socket_descriptor,&fact,sizeof(int),0,(struct sockaddr *)&client_address,n);
fact=1;
}
}
