#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 64

int main() {
	int ptc_fd[2]; //parent to child pipe
	int ctp_fd[2]; //child to parent pipe 
	char buf[BUFSIZE];

	if (pipe(ptc_fd) == -1) {
		perror("parent to child pipe");
		return 0;
	}

	if (pipe(ctp_fd) == -1) {
		perror("child to parent pipe");
		return 0;
	}

	switch(fork()) {
		case -1:
			perror("fork");
			return 0;
		case 0:
			close(ctp_fd[0]);
			close(ptc_fd[1]);
			write (ctp_fd[1],"Hello I'm child.",BUFSIZE);
			read(ptc_fd[0],buf,BUFSIZE);
			printf("Message from parent: %s\n", buf);
			return 0;
		default:
			close(ctp_fd[1]);
			close(ptc_fd[0]);
			read(ctp_fd[0],buf,BUFSIZE);
			printf("Message from child: %s\n", buf);
			sleep(5);
			write(ptc_fd[1],"Hello I'm your parent.", BUFSIZE);
			wait(NULL);
			return 0;
	}
}
