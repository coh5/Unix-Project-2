
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int saved_stdout;
int sh_stoutput(){
	return saved_stdout;
}


void sh_split(char *line, char **array)
{
    int i = 0; //This is an index for the array
	
    char *p = strtok (line, " ");
	


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
			p = strtok (p, "<");
			array[i++] = p; 
		}
		else {
       	 	array[i++] = p;
		}

      	 	p = strtok (NULL, " ");

    }
	if( i == 3 ){
		if(array[1][0] == '|')
		{
		int pid1, pid2;
		int pp[2];
		if (pipe(pp) < 0);
		pid1=fork();
		if (pid1==0) { // execute foo
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);

		//this is pipelineing actual ls until ours works
		char *cmd = "./myls";
		char *argv[2];
		argv[0] = "ls";
		argv[1] = NULL;
		execvp(cmd, argv);
		}
		pid2=fork();
		if (pid2==0) { // execute foo15a
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

		}
	}
	if(i == 0){
	 	//printf("yay\n");
		i++;
		array[0] = "0";
	}

	array[i] = NULL;
	
}

void sh_execute(char **array)
{

	pid_t pid=fork();
    if (pid==0 && array[0] != "exit" && array[0] != "0") { //child process
		char cmd[50];
		strcpy(cmd, "./");
		strcat(cmd, array[0]);	

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
	//this should get the line and the size of the line.
	int p = getline(&line, &size, stdin);
    if (p == -1) {
       printf("No line\n");
    } else if (p == 1){
		
		return NULL;
	}
	else{
	strtok(line, "\n"); //remove a null character
	return line;
    }
	

	
}

static char* skipwhite(char* b)
{
	//strchr(cmd, ' '); think you can use this to test
	//while (test for spaces here) ++s;
	return b;
}

int main()
{
	saved_stdout = dup(1);
	char *line;
	char *array[10]; //prolly need to check for number of arguments later.
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
