/**
 * THIS FILE MAY BE USED FOR TEST CODE. IT WILL NOT BE COLLECTED
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "common.h"
#include "decoder.h"
#include "encoder.h"

int main(int argc, char *argv[]){
	char c[] = "010101";

	printf("Char is: %c\n", decodeChar(c));
	return 0;
}
