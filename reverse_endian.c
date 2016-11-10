#include <stdio.h>
#include <stdlib.h>
#include "warmup.h"

int main(int argc, char** argv){
    FILE * inStream;                                    /* Input file */
    FILE * outStream;;                                  /* Output file */
    int inBuffer;                                       /* Current integer */
    int reversedIn;                         /* Integer in reversed endian */
    int intsRead;

     /* Check that user passed in two arguments */
    if (argc < 2) { 
        printf("Not enough arguments, please try again m8. \n");
        return 0;
    }

    /* Open two filestreams, one to read, the other to write */
    inStream = fopen(argv[1], "rb");
    outStream = fopen(argv[2], "wb");

    /* Continue reading until end of file */
    while(1) {

        /* Read four bytes at a time */
        intsRead = fread(&inBuffer, sizeof(int), 1, inStream);

        /* Write out only if we read one whole int (4 bytes) */
        if (intsRead != 1) {
            break;
        }

        /* Reverse the int and write output to file */
        else {
            reversedIn = reorder_bytes(inBuffer);
            fwrite(&reversedIn, sizeof(int), 1, outStream);
        }
    }

    /* Close filestreams */
    fclose(inStream);
    fclose(outStream);
    return 0;
}