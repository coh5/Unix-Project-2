
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This is not completed yet!
// ERRORS
//  ././ can execute the execution!!

void sh_split(char *line, char **array)
{
    //char buf[] ="abc qwe ccd";
    int i = 0;
    char *p = strtok (line, " ");
    //char *array[10];


	//message = strcat("TEXT " , var);
	
    while (p != NULL)
    {
		//had the argument had a dollar sign in front of it we would need to extract the argument out.
		if(p[0] == '>') {
			printf("%s\n", p); 

			int fd=open("afile2.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);
			
			if (fd < 0){ exit(1);}
			dup2(fd, 1);
			close(fd);
			
		}
		else {
        array[i++] = p;
		}
        p = strtok (NULL, " ");
		
    }
	
	array[i] = NULL;
	
}

void sh_execute(char **array)
{

		pid_t pid=fork();
    if (pid==0) { //child process
		//char *cmd = "./";
		char cmd[50];
		strcpy(cmd, "./");
		strcat(cmd, array[0]);
				

		if(	execvp(cmd, array) == -1){
			perror("error executing");
		}
	
    }
    else { // pid!=0; parent process *
        waitpid(pid,0,0); // wait for child to exit 
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
	
	return line;
        //printf("%s\n", line);
    }
	
}

int main()
{
  	printf("$ ");
	char *line;
	char *array[10]; //prolly need to check for number of arguments later.
	while(1) {
	
 	// Run command loop.
  	line = loop();

	
	sh_split(line, array);
	
	int ret = strcmp(array[0], "exit\n");


	if(strcmp(array[0], "exit\n") == 0){ 
		printf("this is exit\n");
		exit(0);}
	
	sh_execute(array);

	free(line);

	}
	//sh_execute();    
	
  	return 0;
}
