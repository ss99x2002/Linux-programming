#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
sigjmp_buf position;
void int_handler (int a) {
	printf("\nSIGINT caught\n");
	siglongjmp(position,1);
}

int main() {
	struct sigaction act;

	sigfillset(&act.sa_mask); //signal handler 수행 중 block 할 signal 들 모음
	act.sa_handler = int_handler;
	sigaction (SIGINT, &act, NULL); 
	printf("int handler() for SIGINT is registered\n");
	if (sigsetjmp(position,1)!=0 ) printf("Restart sleeps. . . \n");
	for (int i=0; i<4; i++ ) {
		printf("sleep call #%d\n",i);
		sleep(3);
	}
	return 0;
}
