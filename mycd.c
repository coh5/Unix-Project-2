#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void error(char *err) 
{
	printf("%s\n", err);
	exit(1);
}


void main(int argc, char *argv[]) 
{
	DIR *dir;
	
	if (argc != 2)
	{
		error("Invalid Syntax: ./mycd [directory]");
	}
	
	if ( (dir = opendir(argv[1])) == NULL )
	{
		error("Directory could not be opened");
	}

	if (closedir(dir) == -1)
	{
		error("Directory could not be closed");
	}

	exit(0);
}
