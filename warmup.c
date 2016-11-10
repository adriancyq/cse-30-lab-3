#include <stdio.h>
#include <stdlib.h>
#include "warmup.h"

unsigned int *char_freqs(FILE *fp){
   int nextChar;                                    /* Next char in file */
   unsigned int * charCounter;                      /* Frequency array */

    /* Initialize int array for frequencies */
    charCounter = malloc(sizeof(int) * 256);

    /* Check if the file pointer is valid */
    if(!fp){
        return NULL;
    }

    /* Read entire file one char at a time */
    while(1){

        /* Get the next char */
        nextChar = fgetc(fp);

        /* Check if we have reached the end of file */
        if (feof(fp)){
            break;
        }

        /* Increment the number of chars for that char */
        charCounter[nextChar]++;
    }

    /* Return pointer to array containing frequencies of each char */
    return charCounter;
    }
  
int reorder_bytes(int num) {
    int byteMask = 0xFF;                            /* Grab a single byte */
    int bitsInByte = 8;                             /* 1 byte = 8 bits */
    int first, second, third, fourth;               /* Individual bytes */
    int reversed;                                   /* Reversed int */

    /* Assuming int is four bytes, separate them by ANDing with byteMask
    and repeatedly shifting by one byte (8 bits) */
    fourth = num & byteMask;
    num = num >> 8;

    third = num & byteMask;
    num = num >> 8;

    second = num & byteMask;
    num = num >> 8;

    first = num & byteMask;

    /* Reverse the order of the bytes */
    fourth = fourth << (3 * bitsInByte);
    third = third << (2 * bitsInByte);
    second = second << (1 * bitsInByte);

    /* Concatenate all four together */
    reversed = fourth | third | second | first;
    return reversed;
}