#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER 256

void error(char *a) {
	printf("%s\n", a)
	exit(1);
}
void main(int argc, char *argv[]) {
	int source;
	int destination;
	char buff[BUFFER];
	int read_B;
	
	if (argc != 3){
		error("File-to-file error");
	}
	if (source = open(argv[1], O_RDONLY)) == -1){
		error("File could not be opened for read");
	}
	if (destination = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
		error("File could not be created to write");
	}
	while ((read_B = read(source, buff, BUFFER)) !=0) {
		if (write(destination, buff, read_B) == -1) {
			error("Writing to file failed, error");
		}
	}
	if (close(source) == -1) {
		error("Source file close error");
	}
	if (close(destination) == -1) {
		error("Destinaton file close error");
	}
	exit(0);
}
	
