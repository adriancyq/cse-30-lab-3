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
    // TODO Implement me!
    //works
    int ascii = (int) c +1;
    int *bitArray = calloc(8,sizeof(int));
    int soFar =0;

    for (int i=7; i>=0; i--){
    	int exponent = 1;
    	for(int n = 0; n<i;n++){
    		exponent = 2*exponent;
    	}
    	if(soFar+exponent < ascii){
    		soFar += exponent;
    		bitArray[i] = 1;
    	}
    	else{
    		bitArray[i] = 0;
    	}
    }
    if(bitArray[index]==1){
    	return 1;
    }
    else{
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
    // TODO Implement me!
    //works
    int total=0;
    for(int i=0; i<6; i++){
    	int indexVal = (int)(b[i]-'0');
    	int exponent = 1;
    	for(int n =5-i;n>0;n--){
    		exponent = 2*exponent;
    	}
    	total += indexVal*exponent;
    }
    char finalAnswer = MAPPING[total];
    return finalAnswer;
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
    // TODO Implement me!
    //doesnt work
    int charValue = 0;

    do{
    	charValue = fgetc(in);
    	char c = (char) charValue;
    	int bitValue = extractBit(c, index);
    	if(bitValue==0){
    		fprintf(out,"0");
    	}
    	else{
    		fprintf(out, "1");
    	}
    } while(charValue!=EOF);
    fclose(in);
    fclose(out);
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
    // TODO Implement me!
    //doesnt work
    int charValue;
    do{
    	char *charArray = calloc(6,sizeof(char));
    	for(int i = 0;i<6; i++){
    		charArray[i] = fgetc(in);
    		charValue = (int) charArray[i];
    	}
    	char answer = decodeChar(charArray);
    	fprintf(out,"%c", answer);
    } while(charValue!=EOF);
    fclose(in);
    fclose(out);
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
    // TODO Implement me!
	 //doesnt work
    FILE *inputFile = fopen(input, "r");
    FILE *outputFile = fopen(output, "w");
    FILE *binFile = fopen(bin, "w");
    codeToBinary(inputFile,binFile,index);
    binaryToText(binFile,outputFile);
    fclose(inputFile);
    fclose(outputFile);
    fclose(binFile);
}