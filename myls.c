#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>
#include <libgen.h>

int loption(char** argv)
{
	
	struct stat buf;
	if(lstat(argv[2], &buf) < 0) {
	   perror("cannot open file");
	   return 1;
	}

	unsigned char type;
	if(S_ISDIR(buf.st_mode)) type = 'd';
	else if (S_ISREG(buf.st_mode)) type = '.';
	else if (S_ISLNK(buf.st_mode)) type = 'l';
	
	unsigned short rights = buf.st_mode & (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

	unsigned int link = buf.st_nlink;

	char username[50];
	struct passwd *user = getpwuid(buf.st_uid);
	strncpy(username, user->pw_name, 49);
	username[49] = '\0';

	char groupname[50];
	struct group *grp = getgrgid(buf.st_uid);
	strncpy(groupname, grp->gr_name, 49);
	groupname[49] = '\0';

	unsigned int size = buf.st_size;

	char time[50];
	strncpy(time, ctime(&buf.st_atime), 50);
	time[49] = '\0';
	int len = strlen(time);
	if(time[len-1] == '\n') time[len-1] = '\0';

	printf("%c %3o %u %s %s %u %s %s\n", type, rights, link, username, groupname, size, time, basename(argv[1]));

	return 0;
}

int main (int argc, char *argv[]) {

	DIR *dp;
	struct dirent *dirp;

	if(argc ==1) dp = opendir ("./");
	else if(argc ==2) dp = opendir(argv[1]);
	//else if(argc ==3) printf("Test");
	else if(strcmp(argv[1], "-l") == 0) loption(argv);

	
	//if(argc < 3)
	//while ((dirp = readdir(dp)) != NULL) printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
