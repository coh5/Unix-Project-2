
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This is not completed yet!

void sh_execute()
{
	printf("sh_execute\n");
	pid_t pid=fork();
    if (pid==0) { /* child process */
        static char *argv[]={"echo","Foo is my name.",NULL};
        execvp("foo6",argv);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }
}

char *loop(void)
{
    char *line = NULL;
	size_t size;
	//this should get the line and the size of the address.
    if (getline(&line, &size, stdin) == -1) {
        printf("No line\n");
    } else {
        printf("%s\n", line);
    }
	
}

int main(int argc, char **argv)
{
  	
	char *line;
 	// Run command loop.
  	line = loop();

	sh_execute();    

  	return 0;
}

