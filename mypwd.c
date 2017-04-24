#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error(char *err) 
{
	printf("%s\n", err);
	exit(1);
}


void main(int argc, char *argv[]) 
{	
	char cwd[1024];
	
	if (argc > 1)
	{
		error("Too many arugments for ./pwd");
	}
	
	if(getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		error("getcwd() error");
	}
	exit(0);
}
