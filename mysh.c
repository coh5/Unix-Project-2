
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
	//I need to figure out here how to add redirection into files
	
    while (p != NULL)
    {
		//had the argument had a dollar sign in front of it we would need to extract the argument out.
		if(p[0] == '>') //This is for redirection
		{


			int fd=open("afile2.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);
			
			if (fd < 0){ exit(1);}
			dup2(fd, 1);
			close(fd);
			
		}
		else if(p[0] == '|') {
		
			int pid1, pid2;
			int pp[2];
			if (pipe(pp) < 0) perror("error piping");
				pid1=fork();
			if (pid1==0) { // execute foo
				dup2(pp[1], 1);
				close(pp[0]);
				close(pp[1]);

			}
			pid2=fork();
			if (pid2==0) { // execute foo15a
				dup2(pp[0], 0);
				close(pp[0]);
				close(pp[1]);

			}
		close(pp[0]);
		close(pp[1]);
			
			
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

		//printf("Below is array 0\n");
		//printf("%s\n",array[0]);

	
		pid_t pid=fork();
    if (pid==0) { //child process
		//char *cmd = "./";
		char cmd[50];
		strcpy(cmd, "./");
		strcat(cmd, array[0]);

				

	
		if(	execvp(cmd, array) == -1){
			
			perror("error executing");
			exit(0);
		}
		
	
    }
    else { // pid!=0; parent process *
        waitpid(pid,0,0); // wait for child to exit 
    }
}

char *line2(void)
{
	
    char *line = NULL;
	size_t size;
	//this should get the line and the size of the address.
    if (getline(&line, &size, stdin) == -1) {
        printf("No line\n");
    } else {
	
	strtok(line, "\n"); //remove a null character
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
  	line = line2();

	
	sh_split(line, array);
	

	if(strcmp(array[0], "exit") == 0){ 
		exit(0);}
	
	sh_execute(array);

	free(line);

	}
	

	


	//sh_execute();    
	
  	return 0;
}
