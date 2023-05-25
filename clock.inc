CLOCK PROC
    START:
        CALL CLRSCR
        CALL PRNT_TME
        CALL PRNT_DTE
        CALL PRNT_DOW


        ; MOV AH, 01H
        ; INT 16H
        ; CALL ENDPROG
        ; JMP START

    RET
CLOCK ENDP