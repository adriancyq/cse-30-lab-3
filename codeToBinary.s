.syntax unified

.text

.align 3
.global codeToBinary
.func codeToBinary, codeToBinary
.type codeToBinary, %function

@void codeToBinary(FILE *in, FILE *out, int index);

codeToBinary:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    @ YOUR CODE GOES HERE
    @-----------------------
        MOV R11, R0     @r11 is instream
        MOV R10, R1     @r10 is outstream
        MOV R9, R2      @r9 is index, r3 
        MOV R8, #0      @r8 is encodedChar
        MOV R7, #0      @r7 is extractedbit
        
        

whileloop: 
        MOV R0, R11     @encodedChar = fgetc(in)
        BL fgetc        @branch to instream
        MOV R8, R0      @encodedChar is now fgetc(in)
        MOV R0, R11     @r0 is now instream
        BL feof         @end of file for instream
        CMP R0, #0      @if (encodedChar == EOF)
        BNE end      @return when not zero
        MOV R0, R8      @encodedChar is now r0
        MOV R1, R9      @index moved into r1 
        BL extractBit   @extractbit = extractedbit(encodedChar, index)
        MOV R7, R0      @extracedbit = extractbit
        CMP R7, #1      @compare extractedbit to 1
        BNE asciizero   @if not equal to 1, load ascii
        MOV R0, #49     @equal to 1, load ascii 1
        B writeToFile   @write extractedbit to file

asciizero:
        MOV R0, #48     @extractedbit == 1, load into r0 

writeToFile:
        MOV R1, R10     @outstream is in r1
        BL fputc        @fwrite(&writeChar, sizeof(char), 1, out);
        B whileloop     @branch to whileloop until file is finished

    
    @ put your return value in r0 here:

    @-----------------------

end:

    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
