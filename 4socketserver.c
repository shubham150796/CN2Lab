#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
int cs,fd,ns,n;
int bufsize=1024;
char *buffer=malloc(bufsize);
char fname[255];
struct sockaddr_in address;
address.sin_family=AF_INET;
address.sin_addr.s_addr=INADDR_ANY;
address.sin_port=htons(15000);
cs=socket(AF_INET,SOCK_STREAM,0);
bind(cs,(struct sockaddr*)&address,sizeof(address));
listen(cs,3);
ns=accept(cs,(struct sockaddr*)NULL,NULL);
recv(ns,fname,255,0);
fd=open(fname,O_RDONLY);
n=read(fd,buffer,bufsize);
send(ns,buffer,n,0);
close(ns);
return close(cs);
}



