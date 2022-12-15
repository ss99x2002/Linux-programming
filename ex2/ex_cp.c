#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define PERMS 0644
#define BUFSIZE 4096

int copyfile (const char*, const char *);

int main(int argc, char *argv[]){
	char *infile = argv[1];
	char *outfile = argv[2];

	int retcode = copyfile(infile,outfile);

	if(retcode == 0) printf("copy succeed!\n");	
	else	perror ("copy failed");
	return 0;
}

int copyfile (const char * name1, const char * name2 ){
	int infile, outfile;
	ssize_t nread;
	char buffer[BUFSIZE];

	if ((infile = open(name1, O_RDONLY))==-1)
		return -1;
	if ((outfile = open(name2, O_WRONLY | O_CREAT | O_EXCL,PERMS))==-1){
		if (errno == EEXIST) {
			printf("%s copy file already exists. overwirte? (y/n)",name2);
			char s = getc(stdin);
			if (s == 'y')
			{
				if ((outfile = open(name2, O_WRONLY | O_TRUNC, PERMS)) == -1){
					close(infile);
					return -2;
			}
			else {
				close(infile);
				return -2;
			}
		}
		else
		{
			close(infile);
			return -2;
		}	
	
	}
	}
	while ((nread = read(infile, buffer,BUFSIZE))>0){
		if (write(outfile,buffer,nread)<nread){
			close(infile);
			close(outfile);
			return -3;
		}
	}
	close(infile);
	close(outfile);
	if (nread == -1) return -4;
	else return 0;
}
