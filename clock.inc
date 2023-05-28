CLOCK PROC
    START:
        CALL DELAY
        CALL CLRSCR

        MOV DX, 0508H
        CALL SET_CRSR
        CALL PRNT_TME

        MOV DX, 0608H
        CALL SET_CRSR
        CALL PRNT_DTE

        MOV DX, 0708H
        CALL SET_CRSR
        CALL PRNT_DOW

        CALL GETKINAS

        JZ START


        ; MOV AH, 01H
        ; INT 16H
        ; CALL ENDPROG
        ; JMP START

    RET
CLOCK ENDP