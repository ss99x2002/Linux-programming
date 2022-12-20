#include "smallsh.h"
#define VERYBIG 200
char *prompt = "Command> ";

char dirname[VERYBIG];

int main() {
	while(userin(getcwd(dirname,VERYBIG)) !=EOF)
		procline();
	return 0;
}
