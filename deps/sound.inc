.DATA
    RTONE1_N DB "Sweet Child", "$"
    RTONE2_N DB "Mundo      ", "$"
    RTONE3_N DB "Magbalik   ", "$"

    RTONE_ID DB 1 ; Alarm sound index -> Used to determine which sound to play
	
.CODE
    CHG_RINDX PROC
        MOV AL, byte ptr [RTONE_ID]
        INC AL
        CMP AL, 4
        JE RST_RIDX
        MOV byte ptr [RTONE_ID], AL
        RET
        RST_RIDX:
            MOV byte ptr [RTONE_ID], 1
            RET
    CHG_RINDX ENDP

    DIS_RTONE PROC

        PUSH DS
	    POP ES
        ; MOV DS, SEG RTONE1_N
        MOV CX, 11
        MOV BH, 0
        MOV BL, 00001110b
    
        MOV AL, byte ptr [RTONE_ID]
        CMP AL, 1
        JE D_RT1
        CMP AL, 2
        JE D_RT2
        CMP AL, 3
        JE D_RT3
        RET
        D_RT1:
            MOV BP, offset RTONE1_N
            JMP D_RSTR
        D_RT2:
            MOV BP, offset RTONE2_N
            JMP D_RSTR
        D_RT3:
            MOV BP, offset RTONE3_N
            JMP D_RSTR
        D_RSTR:
            MOV AL, 1
            MOV AH, 13h
            INT 10h
            RET
    DIS_RTONE ENDP

    TRIG_ALM PROC ; TRIGGER ALARM
        MOV AL, byte ptr [RTONE_ID] ; Get alarm sound index
        CMP AL, 1
        JE RTONE_1
        CMP AL, 2
        JE RTONE_2
        CMP AL, 3
        JE RTONE_3
        RET
        C_RT1:
            CALL RTONE_1
            RET
        C_RT2:
            CALL RTONE_2
            RET
        C_RT3:
            CALL RTONE_3
            RET
    TRIG_ALM ENDP

    INTRO PROC ; INTRO
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_MI
        CALL NTE_FA
        CALL NTE_SO
        CALL NTE_LA
        CALL NTE_TI
        CALL NTE_DO2
        RET
    INTRO ENDP

    RTONE_1 PROC ; SWEET CHILD
        CALL NTE_DO ;FIRST BAR
        CALL NTE_DO2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_DO
        CALL NTE_DO2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_RE ; 2ND BAR
        CALL NTE_DO2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_RE
        CALL NTE_DO2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_FA ; 3RD BAR
        CALL NTE_DO2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_DO2
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_RE2
        CALL NTE_SO
        CALL NTE_DO2
        CALL NTE_DO
        CALL NTE_RE2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_FA2
        CALL NTE_SO
        CALL NTE_MI2
        CALL NTE_SO
        CALL NTE_RE2
        CALL NTE_DO
        CALL DELAY
        RET
    RTONE_1 ENDP

    RTONE_2 PROC ; MUNDO
        CALL NTE_DO ;FIRST BAR
        CALL NTE_RE
        CALL NTE_FA
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_FA

        CALL NTE_DO ;2ND BAR
        CALL NTE_RE
        CALL NTE_FA
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_FA

        CALL NTE_DO ;3RD BAR
        CALL NTE_RE
        CALL NTE_FA
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_FA

        CALL NTE_DO ;LAST BAR
        CALL NTE_RE
        CALL NTE_FA
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_LA
        CALL DELAY
        CALL NTE_DO
        CALL NTE_RE
        CALL NTE_FA
        CALL DELAY
        RET
    RTONE_2 ENDP

    RTONE_3 PROC ; MAGBALIK
        CALL NTE_DO2 
        CALL DELAY
        CALL NTE_SO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_RE2
        CALL NTE_MI2
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_SO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_RE2
        CALL NTE_MI2
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_SO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL NTE_MI2
        CALL DELAY
        CALL NTE_FA2
        CALL DELAY
        CALL DELAY
        CALL NTE_MI2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_FA2
        CALL DELAY
        CALL DELAY
        CALL NTE_MI2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2 
        CALL DELAY
        CALL NTE_SO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_RE2
        CALL NTE_MI2
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_SO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_RE2
        CALL NTE_MI2
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_SO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_RE2
        CALL DELAY
        CALL NTE_MI2
        CALL DELAY
        CALL NTE_FA2
        CALL DELAY
        CALL DELAY
        CALL NTE_MI2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        CALL DELAY
        CALL NTE_FA2
        CALL DELAY
        CALL DELAY
        CALL NTE_MI2
        CALL DELAY
        CALL DELAY
        CALL NTE_DO2
        RET
    RTONE_3 ENDP

    OUTRO PROC ; OUTRO FOR EXIT PROGRAM
        CALL NTE_DO2
        CALL NTE_TI
        CALL NTE_LA
        CALL NTE_SO
        CALL NTE_FA
        CALL NTE_MI
        CALL NTE_RE
        CALL NTE_DO
        RET
    OUTRO ENDP