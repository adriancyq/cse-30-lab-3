.syntax unified

.text

.align 3
.global decodeChar
.func decodeChar, decodeChar
.type decodeChar, %function

@ char decodeChar(char *b)
decodeChar:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    @ YOUR CODE GOES HERE
    @-----------------------

    @ Initialize indices for char array and MAPPING array
    MOV R1, #0
    MOV R2, #0

    @ Initialize exponent used for determining index of MAPPING array
    MOV R3, #5

loop:
    
    @ For (index = 0; index < 6; index++)
    CMP R1, #6
    BGE foundMappingIndex

    @ Load char at specified position from the array
    LDRB R4, [R0, R1]

    @ Subtract the ASCII value for '0' to convert to int 
    SUB R4, R4, #48

    @ Multiply by exponent to convert binary to decimal
    LSL R4, R4, R3

    @ Add to index of MAPPING array 
    ADD R2, R2, R4 

    @ Update counters
    ADD R1, R1, #1
    SUB R3, R3, #1
    B loop

foundMappingIndex:
    
    @ Load address of MAPPING array
    LDR R5, =MAPPING 

    @ Get char at generated index (R2)
    LDRB R6, [R5, R2]


    @ (your code)
    @ put your return value in r0 here:
    MOV R0, R6 

    @-----------------------
return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
