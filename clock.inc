CLOCK PROC
    START:
        CALL CLRSCR
        ; MOVE MO YUNG CURSOR DITO
        CALL PRNT_TME
        ; GANON DIND ITO
        CALL PRNT_DTE
        ; GANON DIN DITO
        CALL PRNT_DOW

        CALL GETKIN
        ; MOV AH, 01H
        ; INT 16H
        ; CALL ENDPROG
        ; JMP START

    RET
CLOCK ENDP