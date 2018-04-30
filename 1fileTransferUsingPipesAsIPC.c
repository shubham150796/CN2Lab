#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char buffer[1000];

void client(int readfd, int writefd)
{
	printf("\nGive the file path:\t");
	fflush(stdout);
	scanf("%s",&buffer);
	printf("\nServer Online\nProcessing Request...\n");
	write(writefd, buffer, sizeof(buffer));
	while(read(readfd, buffer, sizeof(buffer)))
		printf("%s", buffer);
}

void server(int readfd, int writefd)
{
	FILE *fd;
	char line[1000];
	read(readfd, buffer, sizeof(buffer));
	if(strchr(buffer, '\n'))
		*strchr(buffer, '\n') = 0;
	
	fd = fopen(buffer, "r");
	if(fd == NULL)
	{
		strcpy(buffer, "Can't open file");
		write(writefd, buffer, sizeof(buffer));
		exit(1);
	}
	else
	{
		while(fgets(line, sizeof(line), fd))
			write(writefd, line, sizeof(line));
		printf("\nServer Transfer Completed\n");
	}
}

void main()
{
	int pid;
	int pipe1[2], pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	pid = fork();
	
	if(pid > 0)
	{
		close(pipe2[1]);	
		close(pipe1[0]);
		client(pipe2[0], pipe1[1]);
	}
	else
	{
		close(pipe2[0]);
		close(pipe1[1]);
		server(pipe1[0], pipe2[1]);
	}
}

