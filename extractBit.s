.syntax unified

.text

.align 3
.global extractBit
.func extractBit, extractBit
.type extractBit, %function

@ int extractBit(char c, int index)
extractBit:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}

    @ YOUR CODE GOES HERE
    MOV R8, #0         @ value for 0
    MOV R6, #1         @ value for 1
    LSL R6, R6, R1     @1<<index
    AND R7, R0, R6     @c & mask stored in r7
    CMP R7, R8         @compare extractBit to 0
    BGT greaterthan    @branch to greater than
    B lessthan         @else, branch to less than
     
greaterthan: 
         MOV R0, #1    @return 1 because greaterthan
         B return
lessthan:              @return 0 becasuse lessthan
         MOV R0, #0

return:                @make sure r0 is return value 
         MOV R0, R0
    @ (your code)
    @ put your return value in r0 here:

    @return value

    @-----------------------
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
