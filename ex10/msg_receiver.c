#include "msg_header.h"

static int msgid;

void sigint_handler(int a)
{
	struct msqid_ds msq_status;
	if(msgctl(msgid,IPC_RMID,&msq_status) == -1) {
		perror("msg remove");
	}
}

int main() {
	key_t key;
	struct msg_entry msg;
	int msglen;
	struct sigaction act;
	sigfillset(&act.sa_mask);
	act.sa_handler = sigint_handler;
	sigaction(SIGINT, &act,NULL);

	key = ftok("msg_header.h", 1);
	msgid = msgget(key, IPC_CREAT | QPERM);
	if (msgid==-1) {
		perror("msgget");
		return 1;
	}
	while((msglen = msgrcv(msgid,&msg,MAXLEN,-10,IPC_NOWAIT))>0){
		printf("Received Msg = %s\n",msg.mtext);
	}
	return 0;
}


