#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include <stdlib.h>

// foo15a.c
int main() {
char buf[500];
int len;
while ((len=read(0, buf, 
500)) > 0) write(1, buf, 
len);
return 0;
}
