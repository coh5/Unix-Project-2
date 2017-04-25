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
#include <dirent.h>

int loption(char** argv)
{
	
	struct stat buf;
	if(lstat(argv[2], &buf) < 0) {
	   perror("file cannot be opened");
	   return 1;
	}
	
	unsigned short rights = buf.st_mode & (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

	unsigned int link = buf.st_nlink;

	char usrname[50];
	struct passwd *user = getpwuid(buf.st_uid);
	strncpy(usrname, user->pw_name, 49);
	usrname[49] = '\0';

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

	printf("%3o %u %s %s %u %s %s", rights, link, usrname, groupname, size, time, argv[2]);

	return 0;
}

int main (int argc, char *argv[]) {

	DIR *dp;
        FILE *fp;
	struct dirent *dirp;
    	struct stat sb;
	int i = 0;
        int j, k = 100, count = -1;
	int lsolo = 0;
	char temp[100];
	char sort[100][100];

	if(argc ==1 || argv[1] == "|") dp = opendir ("./");
	else if(argc ==2) {
	   if(strcmp(argv[1], "-l") == 0) {
	      dp = opendir ("./");
	      lsolo = 1;
	   }
	   else {
              dp = opendir(argv[1]);
	      if (!dp) {
	         printf("myls: cannot access %s: No such directory\n", argv[1]);
	         return 0;
              }
              dp = opendir(argv[1]);
	   }
	}
	else if(argc ==3) {
	   if(strcmp(argv[1], "-l") == 0) {
              dp = opendir(argv[2]);
	      fp = fopen(argv[2],"r");
	      if (!dp && !fp) {
	         printf("myls: cannot access %s: No such file or directory\n", argv[2]);
	         return 0;
              }
	      loption(argv);
	   }
	   else printf("myls: Invalid option: Only supports -l");
	}
	else if(argc > 3) {
	   printf("myls: Too many arguments: ls [option] [file or dir]\n");
	   return 0;
        }

	
	if(argc < 3) {
	   while ((dirp = readdir(dp)) != NULL) count++;
	   rewinddir(dp);
	   while ((dirp = readdir(dp)) != NULL) {
	      if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0);
	      else strcpy(sort[i], dirp->d_name);
	      i++;
	   }

  	for(k=0;k<=1000;k++) {
  	   for(i=0;i<=count;i++)
              for(j=i+1;j<=count;j++){
                 if(strcmp(sort[i],sort[j])>0) {
                    strcpy(temp,sort[i]);
                    strcpy(sort[i],sort[j]);
                    strcpy(sort[j],temp);
                 }
              } 

	}

	if(lsolo == 0) {
	   i = 0;
	   rewinddir(dp);
 	   while ((dirp = readdir(dp)) != NULL) {
 	      printf("%s  ", sort[i]);
	      i++;
	   }
	   printf("\n");
	}
	else if(lsolo == 1) {
	   count = i;
	   i = 2;
	   rewinddir(dp);
	   while ((dirp = readdir(dp)) != NULL && i < count) {
	      argv[2] = sort[i];
	      loption(argv);
	      printf("\n");
	      i++;
	   }
	   printf("\n");
	}


	closedir(dp);
	exit(0);
        }
}
