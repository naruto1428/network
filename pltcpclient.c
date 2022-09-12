#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
struct sockaddr_in server_address;
int socket_descriptor,flag;
char message_1[10]="",message_2[10]="";
socket_descriptor=socket(AF_INET,SOCK_STREAM,0);
server_address.sin_family=AF_INET;
server_address.sin_port=2000;
server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(socket_descriptor,(struct sockaddr *)&server_address,sizeof(server_address));
while(1)
{
printf("\nClient:");
scanf("%s",message_2);
send(socket_descriptor,message_2,sizeof(message_2),0);
recv(socket_descriptor,&flag,sizeof(int),0);
if(flag==1)
{
printf("\nserver :The String is Palindrome\n");
}
else
{printf("\nServer:The String is not Palindrome\n");
}
}
close(socket_descriptor);
}
