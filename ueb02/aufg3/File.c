#include<stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

int processFile(char file[]);

int zeit(time_t aktuelleZeit);

int main(int number, char** arguments) {
        int i;
        for(int i = 0; i < number; i++) {
                if(i == 0)
                        continue;
                processFile(arguments[i]);
        }
        return 0;
}

int processFile(char fileString[]) {
        int file = 0;
        file = open(fileString, O_RDONLY);
        struct stat fileStat;
		char buffer[80];

        int i = lstat(fileString, &fileStat);

        if(i != 0) {
                        printf("Diese Datei existiert nicht!");
                        return -1;
                }
				
		switch (fileStat.st_mode & S_IFMT) {
			case S_IFBLK:  printf("block device\n");            break;
			case S_IFCHR:  printf("character device\n");        break;
			case S_IFDIR:  printf("directory\n");               break;
			case S_IFIFO:  printf("FIFO/pipe\n");               break;
			case S_IFLNK:  printf("symlink\n");                 break;
			case S_IFREG:  printf("regular file\n");            break;
			case S_IFSOCK: printf("socket\n");                  break;
			default:       printf("unknown?\n");                break;
		}
		
		printf("Userid: %i",fileStat.st_uid);
		printf("GroupID: %i",fileStat.st_gid);
		getlogin_r(buffer,80);
		printf("Aktueller User: %s",buffer);

        printf("Mode: %lo (octal)\n",
            (unsigned long) (fileStat.st_mode & ~S_IFMT));
			printf("Last Access: ");
			zeit( fileStat.st_atime );
			printf("Last modified: ");
			zeit(fileStat.st_mtime);
			printf("Last statuschange: ");
			zeit(fileStat.st_ctime);


}

int zeit(time_t aktuelleZeit){
    struct tm *zeitStruct;
    zeitStruct = localtime(&aktuelleZeit);

    time(&aktuelleZeit);
    char *stringTokens = strtok(ctime(&aktuelleZeit)," ");
    int i = 0;

    while(stringTokens != NULL){
        if(i == 4){
            printf("%s ",zeitStruct->tm_zone);
        } else {
            printf("%s ",stringTokens);
            stringTokens = strtok(NULL," ");
        }
        i = i+1;
    }
}