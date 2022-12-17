#include "msg_header.h"

int main() {
	int msgid;
	struct msg_entry msg;
	struct msqid_ds msq_status;
	if((msgid = msgget(IPC_PRIVATE, IPC_CREAT | QPERM))==-1) {
		perror("msgget");
		return 1;
	}
	switch(fork()) {
		case -1:
			perror("fork");
			return 1;
		case 0:
			msg.mtype=1;
			strcpy(msg.mtext, "message type 1 from child \n");
			if (msgsnd(msgid, (void*)&msg, MAXLEN,IPC_NOWAIT)==-1){
				perror("msgsnd");
				return 1;
			}
			return 0;
	}

	switch(fork()) {
		case -1:
			perror("fork");
			return 1;
		case 0:
			sleep(10);
			if (msgrcv(msgid, (void*)&msg, MAXLEN, 0, 0) == -1) {
				perror("msgrcv");
				return 1;
			}
			printf("Received Msg = %s\n", msg.mtext);
			if(msgctl(msgid, IPC_RMID,&msq_status) == -1) 
			{
				perror("msg removd");
				return 1;
			}
			return 0;
		default:
			return 0;
	}
}
