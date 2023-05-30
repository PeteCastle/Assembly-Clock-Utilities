.DATA
    TMR_DAY DW 0
    TMR_HR DB 0 
    TMR_MIN DB 0
    TMR_SEC DB 0
    LAP_DAY DB 0
    LAP_HR DB 0
    LAP_MIN DB 0
    LAP_SEC DB 0
    LAP_CNT DB 0


    TMR_RUN DB 0 ; Boolean for timer running
    DBG_MDE DB 0 ; Boolean for debug mode
    RUN_MSG DB 'Stopwatch Running','$'
    PSE_MSG DB 'Stopwatch Paused ','$'
.CODE
    TMR_MAIN PROC
        TMR_INIT:
            CALL CLRSCR
            CALL DISP_TMR
            CALL SDIS_OFF
            ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
        TIMER:
            ; call getkin
            ; CALL GETKINAS

        MOV AH, 01H
        INT 16H
        JZ TMR_NPR
        MOV AH, 0
        INT 16H
        JMP TMR_KYPR

        TMR_KYPR: 
            CMP AL, 'z'
            JE TMR_PSE
            CMP AL, 'Z'
            JE TMR_PSE
           
            CMP AL, 'x'
            JE TMR_SRT
            CMP AL, 'X'
            JE TMR_SRT

            CMP AL, 'c'
            JE LAP
            CMP AL, 'C'
            JE LAP

            CMP AL, 'V'
            JE TMR_RST
            CMP AL, 'v'
            JE TMR_RST

            CMP AL, ']' ;For debugging only, enables 1 second delay
            JE ENA_DBG
            CMP AL, '\';For debugging only, disables 1 second delay
            JE DIS_DBG

            JMP TIMER
        TMR_NPR: ;Timer resume
            MOV AH, byte ptr [TMR_RUN]
            CMP AH, 1
            JE TICK
        TMR_PSE: ;Timer pause
            CALL SDIS_OFF
            MOV byte ptr [TMR_RUN], 0 
            JMP TIMER
        TMR_SRT: ; Timer start
            CALL SDIS_ON
            MOV byte ptr [TMR_RUN],1    
            JMP TIMER
        TMR_RST: ; Timer reset
            MOV  word ptr [TMR_DAY], 0
            MOV  byte ptr [TMR_HR], 0
            MOV  byte ptr [TMR_MIN], 0
            MOV  byte ptr [TMR_SEC], 0
            MOV  word ptr [LAP_DAY], 0
            MOV  byte ptr [LAP_HR], 0
            MOV  byte ptr [LAP_MIN], 0
            MOV  byte ptr [LAP_SEC], 0
            MOV  byte ptr [LAP_CNT], 0
            MOV  byte ptr [TMR_RUN], 0

            JMP TMR_INIT
        DIS_DBG:
            MOV byte ptr [DBG_MDE],0
            JMP TIMER
        ENA_DBG:
            MOV byte ptr [DBG_MDE],1
            JMP TIMER
        LAP:
            CALL DISP_LLT
            MOV  word ptr [LAP_DAY], 0
            MOV  byte ptr [LAP_HR], 0
            MOV  byte ptr [LAP_MIN], 0
            MOV  byte ptr [LAP_SEC], 0
            ADD LAP_CNT, 1
            JMP TIMER
        
        TICK: ; Tick timer (1sec)
            CMP byte ptr [DBG_MDE], 0
            JNE NO_DBG
            CALL DELAY_1SC
            NO_DBG:
            MOV BX, word ptr [TMR_DAY]
            MOV CH, byte ptr [TMR_HR]
            MOV CL, byte ptr [TMR_MIN]
            MOV DH, byte ptr [TMR_SEC]
            CALL ADD_SEC
            MOV  word ptr [TMR_DAY], BX
            MOV  byte ptr [TMR_HR], CH           
            MOV  byte ptr [TMR_MIN], CL
            MOV  byte ptr [TMR_SEC], DH
            CALL DISP_TMR
        TICK_LAP: ; Tagalog ng fold
            MOV BX, word ptr [LAP_DAY]
            MOV CH, byte ptr [LAP_HR]
            MOV CL, byte ptr [LAP_MIN]
            MOV DH, byte ptr [LAP_SEC]
            CALL ADD_SEC
            MOV  word ptr [LAP_DAY], BX
            MOV  byte ptr [LAP_HR], CH
            MOV  byte ptr [LAP_MIN], CL
            MOV  byte ptr [LAP_SEC], DH
            CMP LAP_CNT, 0
            JE NO_LAPS
            CALL DISP_LTR
            NO_LAPS:
                JMP TIMER
    TMR_MAIN ENDP


DISP_TMR PROC ;Displays timer (normal)
    MOV DH,5 ;Row and Column (DL) for Timer Day
    MOV DL,40
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_DAY]
    CALL DISP_DT	

    MOV DH,5 ;Row and Column (DL) for Timer Hour
    MOV DL,45
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_HR]
    CALL DISP_DT	

    MOV DH,5 ;Row and Column (DL) for Timer Minute
    MOV DL,50
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_MIN]
    CALL DISP_DT	

    MOV DH,5 ;Row and Column (DL) for Timer Second
    MOV DL,55
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_SEC]
    CALL DISP_DT	
    RET
DISP_TMR ENDP

DISP_LTR PROC ; Displays lap timer
    MOV DH,8 ;Row and Column (DL) for Lap Timer Day
    MOV DL,40
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_DAY]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Lap Timer Hour
    MOV DL,45
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_HR]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Lap Timer Minute
    MOV DL,50
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_MIN]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Lap Timer Second
    MOV DL,55
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_SEC]
    CALL DISP_DT	
    RET
DISP_LTR ENDP

DISP_LLT PROC ; Displays row in laps list
    ; MOV AX, 2
    ; ADD AX, LAP_CNT

    ; MOV DH, 2 + byte ptr [LAP_CNT] ;Row and Column (DL) for Laps List (first row)
    MOV DH, 2
    ADD DH, byte ptr [LAP_CNT]
    
    MOV DL, 10
    CALL SET_CRSR

    mov dl, '#'     ; To print #
    mov ah, 02h
    int 21h

    MOV AH, 0
    mov AL, byte ptr [LAP_CNT]
    add AL, 1
    CALL DISP_DT

    mov dl, ' '     ; To print  
    mov ah, 02h
    int 21h

    ; If Lap day is zero, it is not displayed
    MOV AH, 0
    MOV AL, byte ptr [LAP_DAY]
    CMP AL, 0
    JE LLC1
    CALL DISP_DT	

    mov dl, ' '     ; To print  
    mov ah, 02h
    int 21h

    ; If lap hour is zero, it is not displat]yed
    LLC1:
    MOV AH, 0
    MOV AL, byte ptr [LAP_HR]
    CMP AL, 0
    JE LLC2
    CALL DISP_DT

    mov dl, ':'     ; To print :
    mov ah, 02h
    int 21h

    LLC2:
    MOV AH, 0
    MOV AL, byte ptr [LAP_MIN]
    CALL DISP_DT

    mov dl, ':'     ; To print :
    mov ah, 02h
    int 21h

    MOV AH, 0
    MOV AL, byte ptr [LAP_SEC]
    CALL DISP_DT
    RET
DISP_LLT ENDP

SDIS_ON PROC ; Stopwatch status ON

    MOV DH,3 ;Row and Column (DL) for Timer Status Label
    MOV DL,40
    MOV BP, offset RUN_MSG
    mov CX,17

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000010b
	MOV AH, 13h
	INT 10H
	RET
SDIS_ON ENDP

SDIS_OFF PROC ;Stopwatch status OFF

    MOV DH,3 ;Row and Column (DL) for Timer Status Label
    MOV DL,40
    MOV BP, offset PSE_MSG
    mov CX,17

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000100b
	MOV AH, 13h
	INT 10H
	RET
SDIS_OFF ENDP


    
