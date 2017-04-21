#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	int filedes, change;
	for (int i = 1; i < argc; i++) {
		filedes = open(argv[i], O_RDONLY);
		if (filedes < 0) {
			printf("Bad file read, no such file exists\n");
			continue;
		}
		while (read(filedes, &change, 1) == 1) {
			write (STDOUT_FILENO, &change, 1);	
		}
		close (filedes);
	}
}
		
