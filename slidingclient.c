#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
int main()
{
int sfd,lfd,len,choice;
char str[20],strl[20],err[20];
struct sockaddr_in saddr,caddr;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
perror("Fderror");
bzero(&saddr,sizeof(saddr));
saddr.sin_family=AF_INET;
saddr.sin_addr.s_addr=htonl(INADDR_ANY);
saddr.sin_port=htons(5465);
connect(sfd,(struct sockaddr*)&saddr,sizeof(saddr));
for(;;)
{
read(sfd,str,20);
if(!strcmp(str,"Exit"))
{
printf("Exiting\n");
break;
}
printf("\n\n Recieved %s\n Do you want to report error",str);
scanf("%d",&choice);
if(!choice)
write(sfd,"-1",sizeof("=1"));
else
{
printf("Enter the sequence of frame where error has occured\n");
scanf("%s",err);
write(sfd,err,sizeof(err));
read(sfd,str,20);
printf("\n Recieved the retransmitted frames %s\n",str);
}
}
}
