

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666

char fname[256];

int main()
{
	int readfd, writefd;
	ssize_t n;
	char buff[512];
	
	printf("\nTrying to connect to server...\n");
	writefd = open(FIFO1, O_WRONLY, 0);	
	readfd = open(FIFO2, O_RDONLY, 0);
	printf("\nConnected");
	
	printf("\nEnter the filename to request:\t");
	scanf("%s", fname);
	write(writefd, fname, 255);
	printf("\nWaiting for server to reply\n");
	
	while((n=read(readfd, buff, 512))>0)
	write(1,buff,n);
	
	close(readfd);
	close(writefd);
}
