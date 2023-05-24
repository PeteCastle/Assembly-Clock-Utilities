CURS_OFF PROC ;NEAR
    MOV     CH, 10h         ;Hides cursor
    MOV     AH, 01H         ;Interrupt for set text-mode sursor shape
    INT     10h             
    RET
CURS_OFF ENDP

CURS_ON PROC ;NEAR 
    MOV     CX, 0506h       ;Show cursor
    MOV     AH, 01H         ;Interrupt for set text-mode sursor shape
    INT     10H             
    RET
CURS_ON ENDP

DELAY PROC
    MOV     AH, 00H         
    INT     01AH            ;Get system time
    ADD     DX,  4          ;Delay amount (in loops)
    MOV     BX, DX          ;Stores the DX (clock ticks since 12AM) to BX

    PZ:
        INT     01AH            ;Get system time (again)
        CMP     DX, BX          ;Compare the current time with the time stored in BX
        JL      PZ              ;Jumps to PZ if DX is less than BX
        ; Note that since delay is 4, it would take 4 loops before this procedure ends.
    RET
DELAY ENDP