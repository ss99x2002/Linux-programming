#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void int_handler(int a)
{
	printf("\nSIGINT caught\n");
}

int main() {

	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_handler = int_handler;
	sigaction(SIGINT, &act, NULL);

	sigset_t newset;
	sigemptyset(&newset);
	sigaddset(&newset, SIGINT);

	for (int i=0; i<4; i++) {
		sigprocmask(SIG_BLOCK,&newset,NULL);
		printf("sleep call #%d\n", i);
		sleep(3);
		sigprocmask(SIG_UNBLOCK,&newset,NULL);
	}
	return 0;
}
