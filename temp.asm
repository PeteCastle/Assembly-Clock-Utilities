.model small
.stack 100h

.data
    message db 'Hello, World!', '$'
    message1 db 'a','$'

.code
start:
    MOV ax, @data
    MOV ds, ax

    ; Set the foreground color to light blue
    MOV ah, 09h
    MOV BL, 06H
    INT 10h

    ; Print the message
    MOV ah, 09h
    MOV DX, offset message
    ; MOV CX, 4
    INT 21h

    MOV AX, 4C00h
    INT 21H
    RET
end start
