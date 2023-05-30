
.model small            ; assembler directive to allocate memory
                        ; no stack and data segment required here

.DATA 
  message db "TEST"
.code                   ; code segment
    start:
        mov     cx, 0fh
        mov     dx, 4240h
        mov     ah, 86h
        int     15h
        
        mov ah, 09h      ; Display a message after the delay
        lea dx, message
        int 21h

        mov ah, 4Ch      ; Terminate the program
        int 21h
      ; ticks_per_second db 182
      ; mov ah, 00h
      ; int 1Ah

      ; ; Calculate the number of clock ticks for 1 second delay
      ; MOV AX, 0
      ; MOV AL, DL
      ; IMUL AX, 0AH



      ; MOV BH, 0
      ; MOV BL, byte ptr [ticks_per_second]
      ; ADD AX, BX
      ; MOV BX, AX

      ; ; Loop until 1 second delay has elapsed
      ; loop_agn:
      ;   MOV AH, 00H
      ;   INT 1AH

      ;   MOV DH, 0H
      ;   IMUL DH, 0AH

      ;   CMP DX, BX
      ;   JL loop_agn 


      RET

end start             ; end program
                                                             
 