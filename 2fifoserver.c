#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666

char fname[256];

int main()
{	
	int readfd, writefd, fd;
	char buff[512];
	ssize_t n;
	if(mkfifo(FIFO1, PERMS) < 0)
		printf("\nCan't create FIFO file");
	if(mkfifo(FIFO2, PERMS) < 0)
		printf("\nCan't create FIFO file");

	printf("\nWaiting for connection request...\n");
	readfd = open(FIFO1, O_RDONLY, 0);
	writefd = open(FIFO2, O_WRONLY, 0);
	printf("\nConnection established");
	
	read(readfd, fname, 255);
	printf("\nClient has requested %s\n", fname);
	
	if((fd = open(fname, O_RDWR)) < 0)
	{
		strcpy(buff, "\nFile does not exist!\n");
		write(writefd, buff, 512);
	}
	else
	{
		while( (n=read(fd, buff, 512))>0)
			write(writefd, buff,n);
	}
	
	close(readfd);
	close(writefd);
	unlink(FIFO1);
	unlink(FIFO2);
}

