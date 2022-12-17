#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define BUFSIZE 64

int main(int argc, char *argv[]) {
	char buf [BUFSIZE]; int fd;
	if (argc<3) {
		printf("Usage: %s <FIFO NAME> <MESSAGE> ",argv[0]); return 1;
	}
	if ((fd=open(argv[1],O_WRONLY | O_NONBLOCK))<0) {
		perror("open"); return 2;
	}

	for (int i=2; i<argc; i++) {
		if (strlen(argv[i]) > BUFSIZE) {
			printf("message too long %s\n", argv[i]);
		}
		if (write(fd,argv[i], strlen(argv[i]))==-1) {
			perror("sender write"); return 3;
		}
	}
	return 0;
}
