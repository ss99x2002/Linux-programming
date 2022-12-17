#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

	int opt;
	int flag_g=0;
	int pid;
	int signal_num;

	while ((opt = getopt(argc,argv,"g"))!=-1) {
		switch(opt) {
			case 'g':
				flag_g= 1;
				break;
			default:
				printf("Unavailable option\n");
				return 1;
		}
	}

	if ((argc-optind)!=2) {
		return -1; //argument가 2개 입력되었는가?
	}

	signal_num = atoi(argv[optind]);
	
	if (flag_g) {
		pid = -atoi(argv[optind+1]);
	}
	else pid = atoi(argv[optind+1]);
	kill (pid,signal_num);
	return 0;
}
