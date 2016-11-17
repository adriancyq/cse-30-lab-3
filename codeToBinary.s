.syntax unified

.text

.align 3
.global codeToBinary
.func codeToBinary, codeToBinary
.type codeToBinary, %function

@void codeToBinary(FILE *in, FILE *out, int index);

codeToBinary:

    @ Parameters:
    @ R0: input stream 
    @ R1: output stream 
    @ R2: index 

    @ Dictionary of Registers 
    @ R6: extractBit
    @ R7: encoded char 
    @ R8: output buffer (writechar)
    @ R9: input stream 
    @ R10: output stream
    @ R11: index 

    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    @ Move parameters elsewhere 
    MOV R9, R0
    MOV R10, R1
    MOV R11, R2

    @ Allocate space for output buffer 
    MOV R0, #1 
    BL malloc 
    MOV R8, R0 

loop:
    
    @ Grab the next encoded char 
    MOV R0, R9
    BL fgetc
    MOV R7, R0 

    @ Check if we have reached end of file 
    CMP R7, #0
    BEQ endOfFile

    @ Extract the bit we care about 
    MOV R0, R7
    MOV R1, R11 
    BL extractBit 
    MOV R6, R0 

    @ Determine if extracted bit is 0 or 1
    CMP R6, #0
    BEQ writeZero

    @ write char is 1 
    MOV R3, #49
    STR R3, [R8]
    B writeOut 

writeZero:
    
    @ Write char is 0
    MOV R3, #48
    STR R3, [R8]

writeOut:
    
    @ Write out char 
    MOV R0, R8
    MOV R1, #1
    MOV R2, #1
    MOV R3, R10 
    BL fwrite

    @ get the next char 
    B loop



endOfFile:

    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
