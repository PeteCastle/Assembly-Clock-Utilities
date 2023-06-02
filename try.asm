.MODEL small
.STACK 100h

.DATA
    myVariable DW -10    ; Declare a word-sized variable with a negative value (-10)
    negativeSign DB '-'   ; Negative sign character

.CODE
start:
    mov ax,5
    ADD AX, myVariable  ; Add the value of myVariable to AX

    INT 1

END start
