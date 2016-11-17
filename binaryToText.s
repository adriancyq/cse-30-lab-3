.syntax unified
.data

teststr: .asciz "%c\n"
.text

.align 3
.global binaryToText
.func binaryToText, binaryToText
.type binaryToText, %function

binaryToText:

    @ Parameters:
    @ R0: FILE *in
    @ R1: FILE *out 

    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
    @-----------------------
    
    @ Check if we have valid input stream 
    CMP R0, #0
    BEQ invalidFileStream

    @ Check if we have valid output stream
    CMP R1, #1
    BEQ invalidFileStream

    @ Store streams elsewhere
    MOV R10, R0 
    MOV R11, R1 

    @ Allocate a 6 char array as input buffer
    MOV R0, #6
    BL malloc
    MOV R9, R0 

    @ Allocate space for one char as output buffer 
    MOV R0, #1
    BL malloc 
    MOV R8, R0 

loop:
    
    @ Prepare parameters for fread
    MOV R0, R9                      @ Input buffer  
    MOV R1, #1                      @ sizeof(char)
    MOV R2, #6                      @ number of chars 
    MOV R3, R10                     @ input stream 

    @ Read in 6 chars at a time 
    BL fread
    
    @ Check for EOF
    CMP R0, #6
    BNE endOfFile

    @ Decode the char and write it out 
    MOV R0, R9 
    BL decodeChar

    @ Store the char 
    STR R0, [R8]

    @ Write out decoded char 
    MOV R0, R8      @ error here: takes in address of char, not char itself
    MOV R1, #1                      @ sizeof(char)
    MOV R2, #1                      @ one char 
    MOV R3, R11                     @ Output stream 
    BL fwrite

    @ Loop back to beginning to decode another char 
    @B loop


endOfFile:
    MOV R0, R9 
    BL free 
    
invalidFileStream:
    @ put your return value in r0 here:

    @-----------------------
return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
