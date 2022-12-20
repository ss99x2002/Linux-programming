#include "smallsh.h"
#define VERYBIG 200
char *prompt = "Command> ";

char dirname[VERYBIG];

int main() {
	sigsetjmp(position,1);
	while(userin(getcwd(dirname,VERYBIG)))
	{
		procline();
	}
	return 0;
}
