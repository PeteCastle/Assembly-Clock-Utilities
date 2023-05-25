.model small
.stack 100h

.data
    prompt db 13, 10, 'Hello Gaiz!', '$'

.code
    start:

        call color    ; Call the color procedure to set the background color
       ; call output

       ; mov ax, 4C00h  ; Exit program
       ; int 21h

;output proc
  ;  mov ah, 09h
    ;lea dx, prompt
   ; int 21h
   ; ret
;output endp

color proc
    MOV AH, 06h    ; Scroll up function
    XOR AL, AL     ; Clear entire screen
    XOR CX, CX     ; Upper left corner CH=row, CL=column
    MOV DX, 184FH  ; lower right corner DH=row, DL=column 
    MOV BH, 42H   ; Red and Green
    INT 10H
    ret
color endp

end start
