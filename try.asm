.model small
.stack 100h

.data

.code
    ; Entry point of the program
    start:
        mov bx, 39h
        sub bx, 6ch
        mov ax, bx
        aas

        int 1h
    end start