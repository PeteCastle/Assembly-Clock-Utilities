.model small
.stack 100h

.data

.code
start:
    mov ax, @data
    mov ds, ax
    
    call COLOR_MA   ; Call the COLOR_MA procedure
    
    ; Rest of your program goes here
    
    mov ah, 4Ch     ; Exit program function
    int 21h         ; Call DOS interrupt 21h
    
COLOR_MA proc
    MOV BH, 0
    MOV BL, 05h    ; MAGENTA text only
    MOV AH, 0Bh
    INT 10H
    ret
COLOR_MA endp

end start
