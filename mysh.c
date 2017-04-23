
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This is not completed yet!

void sh_split(char *line)
{

    int i = 0;
    char *p = strtok (line, " ");
    char *array[10];


    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
	
	//printf("%d\n", i);

    for (int b = 0; b < 3; ++b) 
        printf("%s\n", array[b]);

	array[i] = NULL;
	//i = i - 1;
	

		pid_t pid=fork();
    if (pid==0) { /* child process */
		//char *cmd = "./";
		char cmd[50];
		strcpy(cmd, "./");
		strcat(cmd, array[0]);
		
		//printf("%s\n",cmd);
		execvp(cmd, array);
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }

    //return 0;
}

void sh_execute()
{
	//not using this function yet
}

char *loop(void)
{
    char *line = NULL;
	size_t size;
	//this should get the line and the size of the address.
    if (getline(&line, &size, stdin) == -1) {
        printf("No line\n");
    } else {
	return line;
        //printf("%s\n", line);
    }
	
}

static char* skipwhite(char* b)
{
	//strchr(cmd, ' '); think you can use this to test
	//while (test for spaces here) ++s;
	return b;
}

int main(int argc, char **argv)
{
  	printf("$ ");
	char *line;
 	// Run command loop.
  	line = loop();

	sh_split(line);
	//sh_execute();    
	free(line);
  	return 0;
}
