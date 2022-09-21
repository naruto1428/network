#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<netinet/in.h>
void main()
{
struct sockaddr_in server_address;
int socket_descriptor,flag;
char message[10]="";
socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
server_address.sin_family=AF_INET;
server_address.sin_port=3000;
server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(socket_descriptor, (struct sockaddr *)&server_address,sizeof(server_address));
while(1)
{
printf("\n client:");
scanf("%s",message);
sendto(socket_descriptor,message,sizeof(message),0,(struct sockaddr *)&server_address,sizeof(server_address));
if(flag==1)
{
printf("\nserver :The String is Palindrome\n");
}
else
{printf("\nServer:The String is not Palindrome\n");
}
}recvfrom(socket_descriptor,&flag,sizeof(int),0,NULL,NULL);
}
