
.model small
.stack 100h

.code
        
    start:
    mov cx, 10      ; Loop Counter

    print_loop:
        mov ah, 02h ; Interrupt to print char
        mov dl, '*' ; Character to print
        int 21h     ; 
        loop print_loop

    mov ah, 4Ch    ; Exit program
    int 21h

end start