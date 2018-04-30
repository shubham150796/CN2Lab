#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<fcntl.h>

#define MSGSZ 10000

typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
} message_buf;

int main()
{
	int msqid1, msqid2, f1, filesize, n;
	key_t key1, key2;
	message_buf buf;
	size_t buflen;
	
	key1 = 1234;
	key2 = 5678;
	
	if((msqid1 = msgget(key1, 0666)) < 0)
	{
		printf("\nServer: Can't open input message queue\n");	
		return 0;
	}
	else
		printf("\nServer: Input message queue opened\nWaiting for client request...");
	
	if(msgrcv(msqid1, &buf, MSGSZ, 1, 0) < 0)
	{
		printf("\nServer: Can't receive message");
		return 0;
	}

	if((msqid2 = msgget(key2, 0666)) < 0)
	{
		printf("\nServer: Can't open output message queue\n");
		return 0;
	}
	else
		printf("\nServer: Output message queue opened");
		
	buf.mtype = 2;
	if((f1 = open(buf.mtext, O_RDONLY)) != -1)
	{
		printf("\nServer: %s found\nTransferring Content", buf.mtext);
		filesize = lseek(f1, 0, 2);
		printf("\nServer: File size is %d", filesize);
		lseek(f1, 0, 0);
		n = read(f1, buf.mtext, filesize);
		buflen = strlen(buf.mtext) + 1;
		if(msgsnd(msqid2, &buf, buflen, IPC_NOWAIT) < 0)
		{
			printf("\nServer: Error on sending");
			return 0;
		}
		else
			printf("\nServer: File sent successfully\n");
	}
	
	return 0;
}
