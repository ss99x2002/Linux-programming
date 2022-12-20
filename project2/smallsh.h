#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <setjmp.h>

#define EOL		1
#define ARG		2
#define AMPERSAND	3
#define SEMICOLON	4	
#define REDIRECTION 	5
#define PIPE		6

#define MAXARG		512
#define MAXBUF		512

#define FOREGROUND	0
#define BACKGROUND	1	

#define END 2
sigjmp_buf position;
int userin(char *p);
void procline();
int gettok(char ** outptr);
int inarg(char c);
int runcommand(char **cline, int where);
