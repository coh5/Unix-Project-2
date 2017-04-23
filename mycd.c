#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void error(char *err) 
{
	printf("%s\n", err);
	exit(1);
}

void main(int argc, char *argv[]) 
{
	DIR *dir = opendir("/home");
	int close;
	
	if (argc > 2)
	{
		error("Too many arguments: ./mycd  -or-  ./mycd [directory]");
	}


	/*	[ ./mycd ]	**[ ./mycd ~ ]** (some reason can't use "~" as argument)
	/* Moves to user's home directory from anywhere */
	if (argc == 1)
	{
		printf("TEST1\n");
		while ( (dir = opendir("/home")) == NULL )
		{
			printf("TEST2\n");
			rewinddir(dir);
		}
	}

	/*	[ ./mycd . ]
	/* "Reload" directory */
	else if (strcmp(argv[1], ".") == 0)
	{
		printf("\n");
	}

	/*	[ ./mycd .. ]
	/* Moves use one directory up from current position */
	else if (strcmp(argv[1], "..") == 0)
	{
		printf("TEST3\n");
		rewinddir(dir);
	}
	
	/*	[ ./mycd (DirectoryName) ]
	/* Opens specified directory */
	else
	{
		printf("TEST4\n");
		dir = opendir(argv[1]);

		if (dir == NULL)
		{
			error("Directory could not be opened");
		}
	}

//Not entirely sure where to closedir, or if it is necessary? 
/*
	close = closedir(dir);
	if (close == -1)
	{
		error("Directory could not be closed");
	}
*/
	exit(0);
}
