#include "smallsh.h"

static char inpbuf[MAXBUF];
static char tokbuf[2*MAXBUF];
static char *ptr = inpbuf;
static char *tok = tokbuf;
static int flag_redirection=0;
static char*filename [MAXBUF];
static char command[MAXBUF];

static char special [] = {' ' ,'\t', '&', ';','\n','\0'};

int inarg(char c){
	char *wrk;

	for (wrk=special; *wrk; wrk++) {
		if (c==*wrk)
			return 0;
	}
	return 1;
}

int userin(char *p)
{
	int c, count;
	ptr = inpbuf;
	tok=tokbuf;
	
	flag_redirection=0;
	int i=0;
	int j=0;
	char temp [MAXBUF];
	char * tempPtr = temp;
	char * homePtr = strstr(p,"/home/s12211639");
	if (homePtr)
	{
		strncpy(homePtr, "              ~",15);
	}

	 for (i=0; p[i]!=0; i++)
        {
                if (p[i] !=' ')
                {
                        tempPtr[j]=p[i];
		       	j++;
                }
        }
	 for (int k=0; k<j; k++)
	 {
		 printf("%c",tempPtr[k]);
	 }
	 printf("$ ");

	count =0;
	while (1) {
		if ((c=getchar())==EOF)
			return EOF;
		if (count < MAXBUF)
			inpbuf[count++] = c;
		if (c=='\n'&&count <MAXBUF) {
			inpbuf[count]= '\0';
			return count;
		}
		if (c=='\n'||count >=MAXBUF) {
			printf("smallsh: input line too long\n");
			count =0;
			printf("%s",p);
		}
	}
}

int gettok(char ** outptr){
	int type;
	*outptr = tok;
	while(*ptr == ' '|| *ptr == '\t')
		ptr++;
	*tok++ = *ptr;
	switch(*ptr ++) {
		case '\n':
			type=EOL;
			break;
		case '&' :
			type = AMPERSAND;
			break;
		case ';' :
			type= SEMICOLON;
			break;
		default:
			type=ARG;
			while(inarg(*ptr))
				*tok++ = *ptr ++;
	}
	*tok++ ='\0';
	return type;
}

void procline() {
	char *arg[MAXARG+1];
	int toktype , type;
	int narg=0;
	struct passwd *pwd;
	char cwd[MAXBUF];
	char curdir[MAXBUF];
	for (;;) {
		flag_redirection=0;
		switch (toktype = gettok(&arg[narg]))
		{
			case ARG: 
				if (narg<MAXARG)
					narg++;
				break;
			case EOL:
			case SEMICOLON:
			case AMPERSAND:
				if (toktype == AMPERSAND) type = BACKGROUND;
				else			type = FOREGROUND;
				if (narg!=0 ) {
					arg[narg]=NULL;
					if (strcmp(*arg,"exit")==0)
					{
						exit(0);
					}
					
					if (strcmp(*arg,"cd")==0)
					{
						if (narg>2)
						{
							printf("too many argument\n");
							perror("error");
						}
						else if (narg <2)
						{
							pwd = getpwuid(getuid());
						//	printf("%s\n", pwd->pw_dir);
							if (!chdir(pwd->pw_dir))
							{
								return;
							}
							else
							{
								perror("error");
							}
						}
						else if (narg==2)
						{
							if (strcmp(arg[1],"~")==0)
							{
								pwd = getpwuid(getuid());
								if (!chdir(pwd->pw_dir))
									return;
								else
									perror("error");
							}
							 if (!chdir(arg[1]))
							{
								return;
							}
							else
							{
								getcwd(curdir,MAXBUF);	
								pwd = getpwuid(getuid());
								if (!chdir(pwd->pw_dir))
								{
								//	printf("home change");
								char *wavePtr = strstr(arg[1],"~");
								if (wavePtr)
								{
									strncpy(wavePtr," ",1);
								}
								for (int i=0; arg[1][i]!=0; i++)
								{
									arg[1][i]=arg[1][i+1];
								}
								char *barPtr = strstr(arg[1],"/");
								if (barPtr)
								{
									strncpy(barPtr," ",1);
								}
								
								for (int i=0; arg[1][i]!=0; i++)
								{
									arg[1][i]=arg[1][i+1];
								}
									if (!chdir(arg[1]))
									{
								//		printf("home+wnat change");
										return;
									}
									else{
										perror(arg[1]);
										chdir(curdir);
									}
								}
								else
								{ perror(arg[1]);
								}
							}
						}
					}
					else
					{
					runcommand(arg, type);
					}
				}
				if (toktype ==EOL ) return ;
				narg = 0;
				break;
		}
	}
}
int runcommand(char ** cline, int where)
{
	pid_t pid;
	int status;
	int fd;
	int i=0;
       	
	char dirname [MAXBUF];

	while(*(cline+i)!=NULL)
	{
		//printf("value i change %d\n", i);
		if (strcmp(*(cline+i),">")==0)
		{
			flag_redirection=1;
		//	printf("flag on\n");
			break;
		}
		i++;
	}
	//printf("value: i %d\n",i);
	switch(pid=fork())
	{
		case -1: 
			perror ("smallsh");
			return -1;
		case 0:
			//printf("flag_redirection %d\n",flag_redirection);
			if (flag_redirection) {
				if ((fd=open(*(cline+i+1),O_RDWR|O_CREAT|O_TRUNC,0644))==-1){
					perror("error");
					exit(-1);
				}
				dup2(fd,STDOUT_FILENO);
				close(fd);
				*(cline+i)=NULL;
			}
			execvp(*cline, cline);
			perror(*cline);
			exit(1);
			
		}
	if (where == BACKGROUND){
		printf("[Process id] %d\n", pid);
		return 0;
	}
	if (waitpid(pid, &status, 0) == -1 )
		return -1;
	else
		return status;

}

