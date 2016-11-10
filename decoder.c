/**
 * ALL IMPLEMENTATIONS AND HELPER FUNCTIONS FOR DECODER WILL BE IN THIS FILE.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "decoder.h"
 
/**
 * Takes a char c and int index as input. 
 * Extracts the bit at the input index from the char c. The 0 index
 * refers to the LSB, so for example, index 2 should extract the 3rd
 * least significant bit.
 *
 * @param c the char to extract a bit from
 * @param index the index of the bit to extract
 * @returns the value of the bit at index in c
 */
int extractBit(char c, int index){
    int mask;                               /* Mask to extract desired bit */
    int extractedBit;                       /* Desired bit */

    /* Create the mask by shifting 1 by (index) bits */
    mask = 1 << index; 

    /* Extract the desired bit */
    extractedBit = c & mask;

    /* If there exists a 1 at any position in extracted bit, it is greater 
    than 0 */
    if (extractedBit > 0) {
        return 1;
    }

    /* No set bits anywhere */
    else {
        return 0;
    }
}

/**
 * Takes a 6 character array b as input and returns the corresponding
 * char from MAPPING that is indexed by the binary ASCII string b.
 * For example, if b = "010101", then the char that is mapped to it is 
 * in MAPPING, index 1*16 + 1*4 + 1*1 = 21.
 *
 * @param b a pointer to a 6 character array, with ASCII '1's and '0's
 * @returns the corresponding character from MAPPING
 */
char decodeChar(char *b){
    int index;
    int exponent = 5;
    int asciiOffset;
    int mappingIndex = 0;
    char decodedChar;

    /* Create the index that maps to associated char in MAPPING */
    for (index = 0; index < 6; index++) {

        /* Grab each char, convert to int, raise to corresponding power */
        mappingIndex += (b[i] - asciiOffset) * (2^exponent);
        exponent--;
    }

    /* Decode the char */
    decodedChar = MAPPING[mappingIndex];
    return decodedChar;
}

/**
 * Takes a FILE handle in as input (corresponding to
 * an encoded file) and reads the file, char by char. The
 * bit at the input index of each char is extracted (by calling
 * extractBit). The least significant bit is in index 0.
 *
 * For each character, if the extracted bit is 0, output ASCII '0' to
 * the output file. If the extracted bit is 1, output ASCII
 * '1' to the output file.
 *
 * @param in the input file handle to read from
 * @param out the output file to write the extracted ASCII binary into
 * @param index the index of the bit to extract from each char
*/
void codeToBinary(FILE *in, FILE *out, int index){
    int asciiOffset = 48;           /* ASCII '0' is 48, ASCII '1' is 49 */
    int encodedChar;                /* char grabbed from input stream */
    int extractedBit;               /* desired bit in encodedChar */
    char writeChar;                 /* char to write out */

    /* Check if we have valid filestreams */
    if ((!in) || (!out)) {
        return;
    }

    while (1) {

        /* Grab the next encoded char */
        encodedChar = fgetc(in);

        /* Check if we have reached end of file */
        if (encodedChar == EOF) {
            break;
        }

        /* Extract the bit we care about as an int */
        extractedBit = extractBit(encodedChar, index);

        /* If bit is 1, write out ASCII '1' */
        if (extractedBit) {
            writeChar = '1';
        }

        /* If bit is 0, write out ASCII '0' */
        else {
            writeChar = '0';
        }

        /* Write out the char to output */
        fwrite(writeChar, sizeof(char), 1, out);
    }

    return;
}



/**
 * Takes a FILE handle in as input (corresponding to a
 * "binary" decoded file) and reads the file, 6 chars at a
 * time. Each 6 chars (all ASCII 0's and 1's) should be read into a
 * char array and decoded into its corresponding char (by calling
 * decodeChar). The resulting chars would be output to the FILE handle
 * pointed to by out.
 *
 * @param in the input file, encoded as ASCII '1's and '0's
 * @Param out the decoded output file (ASCII)
*/
void binaryToText(FILE *in, FILE *out){
    char inputBuffer[6];                        /* Stores 6 input chars */
    char decodedChar;                           /* decoded char from buffer */

    /* Check if we have valid filestreams */
    if ((!in) || (!out)) {
        return;
    }

    while (1) {

        /* Read 6 chars at a time */
        charsRead = fread(inputBuffer, sizeof(char), 6, in);

        /* Check for EOF */
        if (charsRead != 6) {
            break;
        }

        /* Decode the char and write it out */
        decodedChar = decodeChar(inputBuffer);
        fwrite(decodedChar, sizeof(char), 1, out);
    }

    return;
}



/**
 * Reads in a file from the specified input path and outputs a a binary decoding to
 * specified bin path and a fully decoded version to specified output path.
 * This should simply open the necessary files, call the above helper functions
 * in the correct sequence, and close the necessary files.
 *
 * @param input the path to the input file
 * @param bin the path to the decoded ASCII binary output file
 * @param output the path to the decoded output file
 * @param index The index of the bit from which binary values should be extracted
 */
void decodeFile(char* input, char* bin, char* output, int index){
    FILE * in;                      /* Encoded chars */
    FILE * out;                     /* Decoded chars */
    FILE * binaryIn;                /* encode to binary */

    /* Open filestreams for encoded, binary, and output */
    in = fopen(input, "rb");
    binaryIn = fopen(bin, "wb");
    out = fopen(output, "wb");

    /* Check that they are valid */
    if((!in) || (!out) || (!binaryIn)) {
        return;
    }

    /* Convert the encoded message to binary */
    codeToBinary(in, binaryIn, index);
    fclose(in);
    fclose(binaryIn);

    /* Convert the binary to text */
    binaryIn = fopen(bin, "rb");
    binaryToText(binaryIn, out);
    fclose(binaryIn);
    fclose(out);

}