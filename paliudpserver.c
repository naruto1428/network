#include<arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
void main() {
struct sockaddr_in client_address,server_address;
int socket_descriptor,n,flag,left,right;
char message[10];
socket_descriptor= socket(AF_INET,SOCK_DGRAM,0);
server_address.sin_family = AF_INET;
server_address.sin_port = 3000;
server_address.sin_addr.s_addr= inet_addr("127.0.0.1");
bind(socket_descriptor,(struct sockaddr *)&server_address,sizeof(server_address));
n=sizeof(client_address);
while(1)
{recvfrom(socket_descriptor,&message,sizeof(message),0,(struct sockaddr *)&client_address,&n);
printf("\nThe String recieved is:%s\n",message);
int n=strlen(message);
for(int i=0;i<n  ;i++)
{
if(message[i] !=message[n-i-1])
{
flag = 1;
break;
}
}
sendto(socket_descriptor,&flag,sizeof(int),0,(struct sockaddr *)&client_address,n);
}
}
