
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
     .---.
    @ @   )   
    ^     |
   [|]    | ##
   /      |####
  (       |####      
   \| /   |#BP#
  / |.'   |### 
 _\ ``\   )##
/,,_/,,____#
*/

int saved_stdout;//For save the standard out
int sh_stoutput(){
	return saved_stdout;
}

void sh_split(char *line, char **array)
{
    int i = 0; //This is an index for the array
    char *p = strtok (line, " ");
	char *c;//just points to the same place as p
	
    while (p != NULL)
    {
		if(p[0] == '>') //This is for redirection
		{	
			char *file = strtok (p, ">");
			int fd=open(file, O_WRONLY|O_CREAT|O_TRUNC, 0600);
			if (fd < 0){ exit(1);}
			dup2(fd, 1);
			close(fd);
			
		}
		else if(p[0] == '<') //This is for redirection
		{	
			strcpy(c,c + 1);	
			array[i++] = c;
		}
		else {
       	 	array[i++] = p;
		}
      	 	p = strtok (NULL, " ");
			c = p;
    }
		
	if( i == 3 ){
		if(array[0] != NULL && array[1][0] == '|' && array[2] != NULL)//for piping
		{
		int pid1, pid2;
		int pp[2];
		if (pipe(pp) < 0);
		pid1=fork();
		if (pid1==0) { 
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);
		//Check for which type of command to execute.
		char cmd[50];
		if(array[0][0] == 'm' && array[0][1] == 'y'){
			strcpy(cmd, "./");
			strcat(cmd, array[0]);	}
		else {
			strcpy(cmd, array[0]);	
		}	
		char *argv[2];
		argv[0] = array[0];
		argv[1] = NULL;
		execvp(cmd, argv);
		}
		pid2=fork();
		if (pid2==0) { // execute the pipeline
		dup2(pp[0], 0);
		close(pp[0]);
		close(pp[1]);

		char *cmd = "./pipeline2";
		char *argv[2];
		argv[0] = "pipline";
		argv[1] = NULL;
		execvp(cmd, argv);
		}
		close(pp[0]);
		close(pp[1]);
		array[0] = "stop";
		}
	}

	if(i == 0){
		i++;
		array[0] = "0";//Set to 0 so it does not try to execute
	}
	array[i] = NULL;
	
}

void sh_execute(char **array)
{

	pid_t pid=fork();
    if (pid==0 && array[0] != "stop" && array[0] != "0") { //child process
		//char *cmd = "./";
		char cmd[50];
		//check for regular or my commands
		if(array[0][0] == 'm' && array[0][1] == 'y'){
			strcpy(cmd, "./");
			strcat(cmd, array[0]);	}
		else {
			strcpy(cmd, array[0]);	
		}	

		if(	execvp(cmd, array) == -1){
			
			perror("error executing");
			exit(0);
		}
    }
    else if(pid>0){ // pid!=0; parent process *
        waitpid(pid,0,0); // wait for child to exit 
    }
	else {
		exit(0);
		//do nothing
	}
	dup2(saved_stdout, 1);
}

char *line2(void)
{
	
    char *line = NULL;
	size_t size;
	//this should get the line and the size of the address.
	int p = getline(&line, &size, stdin);
    if (p == -1) {
       printf("No line\n"); exit(0);
    } else if (p == 1){
		
		return NULL;
	}
	else{
	strtok(line, "\n"); //remove a null character
	return line;
    }
	return line;
}


int main()
{
	saved_stdout = dup(1);
	char *line;
	char *array[10]; //it only reads 10
	while(1) {
 	// Run command loop.
  	line = line2();

	sh_split(line, array);
	if(strcmp(array[0], "exit") == 0){ 
		printf("this is exit\n");
		//exit(0);
		exit(0);
		}
	
	sh_execute(array);

	free(line);
	}
  	return 0;
}
