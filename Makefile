CC=gcc
SOURCES=tester.c common.c encoder.c decoder.c
HEADERS=decoder.h encoder.h common.h
CFLAGS=-g -Wall -std=c99

all: tester

tester: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o tester

arm: 
	$(CC) $(CFLAGS) tester.c common.c binaryToText.s codeToBinary.s decodeChar.s decodeFile.s extractBit.s -o pa3
clean:
	rm -f tester
