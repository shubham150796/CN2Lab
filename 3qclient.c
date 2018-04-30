#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>

#define MSGSZ 10000

typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
} message_buf;

int main()
{
	int msqid1, msqid2;	
	int msflag = IPC_CREAT|0666;
	key_t key1, key2;
	message_buf buf;
	size_t buflen;
	
	key1 = 1234;
	key2 = 5678;
	
	if((msqid1 = msgget(key1, msflag)) < 0)
	{
		printf("\nClient: Can't open output message queue");
		return 0;
	}
	else
		printf("\nClient: Output message queue opened");
	
	if((msqid2 = msgget(key2, msflag)) < 0)
	{
		printf("\nClient: Can't open input message queue");
		return 0;
	}
	else
		printf("\nClient: Input message queue opened");
	
	buf.mtype = 1;
	printf("\nEnter the filename:\t");
	scanf("%s", buf.mtext);
	buflen = strlen(buf.mtext) + 1;
	
	if(msgsnd(msqid1, &buf, buflen, IPC_NOWAIT) < 0)
	{
		printf("\nClient: Error on sending filename");
		return 0;
	}
	else
		printf("\nClient: Filename sent. Waiting for reply...");
	
	if(msgrcv(msqid2, &buf, MSGSZ, 2, 0) < 0)
	{
		printf("\nClient: Error on receiving reply");
		return 0;
	}
	else
	{
		printf("\nClient: Reply from server:\n");
		fputs(buf.mtext, stdout);	
		printf("\n\n");
	}
	return 0;
}

