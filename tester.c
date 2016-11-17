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
	decodeFile("testin.txt", "testbin.txt", "testout.txt", 1);
	return 0;
}
