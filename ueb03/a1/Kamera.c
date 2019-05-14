#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

        if(argc != 2) {
                printf("Usage: Kamera <filename>\n");
                return 1;
        }

        int datei = open(argv[1], O_RDONLY);
        if (datei == -1) {
                perror(NULL);
                return -1;
        }

        char kamera[15];
        if  (lseek(datei,0x9e,SEEK_SET) == -1) {
                perror(NULL);
                return -1;
        }

        if ( read (datei, kamera,15) == -1) {
                perror(NULL);
                return -1;
        }
        printf("Kameraname: %s\n", kamera);

        char lens[25];
        if (lseek (datei,0xe77,SEEK_SET) == -1) {
                perror(NULL);
                return -1;
        }
        if ( read (datei,lens,25) == -1) {
                perror(NULL);
                return -1;
        }
        printf("Linse: %s\n", lens);

        char firmware[6];
        if ( lseek (datei,0x64b,SEEK_SET) == -1) {
                perror(NULL);
                return -1;
        }
        if ( read (datei,firmware,6) == -1) {
                perror(NULL);
                return -1;
        }
        printf("Firmware: %s\n", firmware);

        char datum[20];
        lseek (datei,0xce,SEEK_SET);
        if ( read (datei,datum,20) == -1) {
                perror(NULL);
                return -1;
        }
        printf("Datum: %s\n", datum);

        close(datei);
}
