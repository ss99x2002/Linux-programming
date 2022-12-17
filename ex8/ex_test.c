#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void child_handler(int a) {

	printf("child dead");
	waitpid(0,NULL,0); //child가 죽을때 거두겠다는 뜻인듯. wait 하겠다는 뜻.
}


int main() {

	struct sigaction act;
	
	act.sa_handler = child_handler;
	sigaction (SIGCHLD,&act, NULL);
	sigfillset(&act.sa_mask);

	fork();
	fork();

	for(;;);
	return 0;
}
