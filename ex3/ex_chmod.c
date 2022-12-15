#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void print_usage(char* prog_name) {
	printf("Default usage: %s -f <file name> -m <mode>\n",prog_name);
	printf("-- Change the permission of the <file name> to <mode>\n");
	printf("-- additional options:\n");
	printf("	-v: output a diagnostic for every file processed\n");
	printf("	-h: output a usage of ex_chmod\n");
}

int main(int argc, char * argv[]) {
	int opt;
	int flag_v =0, flag_h =0;
	while ((opt = getopt(argc, argv, "vh" )) != -1 ) {
		switch(opt) {
			case 'v':
				flag_v=1; break;
			case 'h':
				flag_h=1; break;
			default:
				printf("default");
				print_usage(argv[0]);
				return -1;
		}
	}
	if (optind==1)
	{
		printf("Missing operand\nTry 'ex_chomd -h' for more information\n");
		return -1;
	}
	if (flag_h){
		print_usage(argv[0]);
		return 0; }
	if (flag_v) {
		mode_t newmode;

		if (access(argv[2],F_OK)!=0) {
			perror("file is not existed");
			return -1; }

		sscanf (argv[1], "%o", &newmode);
		if (chmod(argv[2], newmode) == -1) {
			perror("mode change failed");
			return -3;
		}
		printf("mode of %s is changed to %d",argv[2],newmode);
		return 0;}
}

