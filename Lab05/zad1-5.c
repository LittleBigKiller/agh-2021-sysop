#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Uzycie: ./zad1-5 <buff_size> <src_file> <trg_file>\n");
        return 0;
    }
    long BUFF_SIZE = strtol(argv[1], NULL, 10);

    if (BUFF_SIZE <= 0 || BUFF_SIZE > 4194304) {
        printf("Bledny rozmiar bufora\n");
        return 0;
    }

    FILE * fs;
    FILE * ft;
    char buffer[BUFF_SIZE];
    int i;
    /* open binary file*/
    fs = fopen(argv[2], "rb");
    ft = fopen(argv[3], "wb");
    if (fs == NULL) {
        perror("fopen(fs)\n");
        exit(EXIT_FAILURE);
    }
    else if (ft == NULL) {
        perror("fopen(ft)\n");
        exit(EXIT_FAILURE);
    }
    else {
        while (!feof(fs)) {
            i = fread(&buffer, sizeof(char), BUFF_SIZE, fs);
            fwrite(&buffer, sizeof(char), i, ft);
        }
    }
    fclose(fs);
    fclose(ft);
    return 0;
}
