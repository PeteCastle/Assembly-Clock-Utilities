
.model small
.stack 100h
.code
    start:
    MOV cx, 10      ; Loop Counter

    print_loop:
        MOV ah, 02h ; Interrupt to print char
        MOV dl, '*' ; Character to print
        INT 21h     ; 
        loop print_loop

    MOV ah, 4Ch    ; Exit program
    INT 21h

end START