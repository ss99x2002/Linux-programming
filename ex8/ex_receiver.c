#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define BUFSIZE 64
int main(int argc, char * argv[]) {
	char buf[BUFSIZE];
	int fd; int nread;
	if (argc !=2) {
		printf("Usage: %s <FIFO NAME>", argv[0]);
		return 1;
	}

	if (mkfifo(argv[1],0666) == -1) {
		if (errno!=EEXIST) {
			perror("mkfifo"); return 2;
		}
	}
	if ((fd=open(argv[1],O_RDWR)) <0 ) {
		perror("open"); return 3;
	}

	while((nread = read(fd,buf,BUFSIZE))>0 ) {
		printf("Msg received: ");
		write(1,buf,nread); return 0; //stdout에 받아온 값 출력하는 거임. 
	}
}
