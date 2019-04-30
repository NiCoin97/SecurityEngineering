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

        int i = lstat(fileString, &fileStat);

        if(i != 0) {
                        printf("Diese Datei existiert nicht!");
                        return -1;
                }

        printf("Mode:                     %lo (octal)\n",
            (unsigned long) fileStat.st_mode);
                zeit( fileStat.st_atime );
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