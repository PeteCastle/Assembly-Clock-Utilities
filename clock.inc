CK_MAIN PROC
    CK_INIT:
        CALL CLRSCR

    CLOCK:

        CALL DELAY
        
        MOV DX, 0508H
        CALL SET_CRSR
        CALL PRNT_TME

        MOV DX, 0608H
        CALL SET_CRSR
        CALL PRNT_DTE

        MOV DX, 0708H
        CALL SET_CRSR
        CALL PRNT_DOW


        MOV AH, 01H
        INT 16H
        JZ CLK_NPR
        MOV AH, 0
        INT 16H
        JMP CLK_KYPR

        CLK_KYPR:	;Alarm Key press
            CALL MODE_MGR
        CLK_NPR: ; Clock  no press
            JMP CLOCK

        ; MOV AH, 01H
        ; INT 16H
        ; CALL ENDPROG
        ; JMP START

    RET
CK_MAIN ENDP