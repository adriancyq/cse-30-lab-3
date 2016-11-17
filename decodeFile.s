.syntax unified

.data 
read: .asciz "rb"
write: .asciz "wb"

.text

.align 3
.global decodeFile
.func decodeFile, decodeFile
.type decodeFile, %function

decodeFile:
    
    @ Parameters:
    @ R0: char * input 
    @ R1: char * bin
    @ R2: char * output 
    @ R3: int index 

    @ Dictionary of Registers 
    @ R5: encoded input stream
    @ R6: binary stream 
    @ R7: output stream
    @ R8: char * input 
    @ R9: char * bin 
    @ R10: char * output 
    @ R11: int index 

    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
    @-----------------------
    
    @ Save all the parameters in different registers 
    MOV R8, R0
    MOV R9, R1 
    MOV R10, R2
    MOV R11, R3

    @ Open filesteram for encoded input and prepare parameters for fread 
    LDR R1, =read 
    MOV R0, R8 
    BL fopen
    MOV R5, R0 

    @ Open filesteram for binary and prepare parameters for fread 
    LDR R1, =write
    MOV R0, R9 
    BL fopen
    MOV R6, R0 

    @ Open filesteram for output and prepare parameters for fread 
    LDR R1, =write  
    MOV R0, R10 
    BL fopen
    MOV R7, R0

    @ Convert encoded message to binary 
    MOV R0, R5 
    MOV R1, R6 
    MOV R2, R3
    BL codeToBinary

    @ Close encoded input stream and binary output stream
    MOV R0, R5
    BL fclose 
    MOV R0, R6
    BL fclose 

    @ Reopen binary file to READ 
    MOV R0, R9
    MOV R1, =read 
    BL fopen
    MOV R6, R0 

    @ Convert binary to text 
    MOV R0, R6 
    MOV R1, R7
    BL binaryToText 

    @ Close the binary and output streams
    MOV R0, R6
    BL fclose 
    MOV R0, R7
    BL fclose 

    @-----------------------
return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
