.DATA
    SW_DAY DW 0
    SW_HR DB 0 
    SW_MIN DB 0
    SW_SEC DB 0
    LAP_DAY DB 0
    LAP_HR DB 0
    LAP_MIN DB 0
    LAP_SEC DB 0
    LAP_CNT DB 0


    SW_RUN DB 0 ; Boolean for stopwatch running
    SDBG_MDE DB 0 ; Boolean for debug mode
    SRUN_MSG DB 'Stopwatch Running','$'
    SPSE_MSG DB 'Stopwatch Paused ','$'
.CODE
    SW_MAIN PROC
        SW_INIT:
            CALL CLRSCR
            CALL DISP_SW
            CALL SDIS_OFF
        STOPWATCH:
            MOV AH, 01H
            INT 16H
            JZ SW_NPR
            MOV AH, 0
            INT 16H
            JMP SW_KYPR
        SW_KYPR: ; Stopwatch key press
            CMP AL, 'z'
            JE SW_PSE
            CMP AL, 'Z'
            JE SW_PSE
           
            CMP AL, 'x'
            JE SW_SRT
            CMP AL, 'X'
            JE SW_SRT

            CMP AL, 'c'
            JE LAP
            CMP AL, 'C'
            JE LAP

            CMP AL, 'V'
            JE SW_RST
            CMP AL, 'v'
            JE SW_RST

            CMP AL, ']' ;For debugging only, enables 1 second delay
            JE SENA_DBG
            CMP AL, '\';For debugging only, disables 1 second delay
            JE SDIS_DBG

            CALL MODE_MGR

            JMP STOPWATCH
        SW_NPR: ;Stopwatch no press
            MOV AH, byte ptr [SW_RUN]
            CMP AH, 1
            JE TICK_SW
        SW_PSE: ;Stopwatch pause
            CALL SDIS_OFF
            MOV byte ptr [SW_RUN], 0 
            JMP STOPWATCH
        SW_SRT: ; Stopwatch start
            CALL SDIS_ON
            MOV byte ptr [SW_RUN],1    
            JMP STOPWATCH
        SW_RST: ; Stopwatch reset
            MOV  word ptr [SW_DAY], 0
            MOV  byte ptr [SW_HR], 0
            MOV  byte ptr [SW_MIN], 0
            MOV  byte ptr [SW_SEC], 0
            MOV  word ptr [LAP_DAY], 0
            MOV  byte ptr [LAP_HR], 0
            MOV  byte ptr [LAP_MIN], 0
            MOV  byte ptr [LAP_SEC], 0
            MOV  byte ptr [LAP_CNT], 0
            MOV  byte ptr [SW_RUN], 0

            JMP SW_INIT
        SDIS_DBG:
            MOV byte ptr [SDBG_MDE],0
            JMP STOPWATCH
        SENA_DBG:
            MOV byte ptr [SDBG_MDE],1
            JMP STOPWATCH
        LAP:
            CALL DISP_LLT
            MOV  word ptr [LAP_DAY], 0
            MOV  byte ptr [LAP_HR], 0
            MOV  byte ptr [LAP_MIN], 0
            MOV  byte ptr [LAP_SEC], 0
            ADD LAP_CNT, 1
            JMP STOPWATCH
        
        TICK_SW: ; Tick stopwatch (1sec)
            CMP byte ptr [SDBG_MDE], 0 ; If debugging is disabled, skip; enable 1 sec delay)
            JNE SNO_DBG
            CALL DELAY_1SC
            SNO_DBG:
            MOV BX, word ptr [SW_DAY]
            MOV CH, byte ptr [SW_HR]
            MOV CL, byte ptr [SW_MIN]
            MOV DH, byte ptr [SW_SEC]
            CALL ADD_SEC
            MOV  word ptr [SW_DAY], BX
            MOV  byte ptr [SW_HR], CH           
            MOV  byte ptr [SW_MIN], CL
            MOV  byte ptr [SW_SEC], DH
            CALL DISP_SW
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
                JMP STOPWATCH
    SW_MAIN ENDP


DISP_SW PROC ;Displays stopwatch (normal)
    MOV DH,5 ;Row and Column (DL) for Stopwatch Day
    MOV DL,40
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [SW_DAY]
    CALL DISP_DT	

    MOV DH,5 ;Row and Column (DL) for Stopwatch Hour
    MOV DL,45
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [SW_HR]
    CALL DISP_DT	

    MOV DH,5 ;Row and Column (DL) for Stopwatch Minute
    MOV DL,50
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [SW_MIN]
    CALL DISP_DT	

    MOV DH,5 ;Row and Column (DL) for Stopwatch Second
    MOV DL,55
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [SW_SEC]
    CALL DISP_DT	
    RET
DISP_SW ENDP

DISP_LTR PROC ; Displays lap stopwatch
    MOV DH,8 ;Row and Column (DL) for Lap Stopwatch Day
    MOV DL,40
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_DAY]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Lap Stopwatch Hour
    MOV DL,45
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_HR]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Lap Stopwatch Minute
    MOV DL,50
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_MIN]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Lap Stopwatch Second
    MOV DL,55
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [LAP_SEC]
    CALL DISP_DT	
    RET
DISP_LTR ENDP

DISP_LLT PROC ; Displays row in laps list
    MOV DH, 2 ;Row and Column (DL) for Laps List (first row)
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

    MOV DH,3 ;Row and Column (DL) for Stopwatch Status Label
    MOV DL,40
    MOV BP, offset SRUN_MSG
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

    MOV DH,3 ;Row and Column (DL) for Stopwatch Status Label
    MOV DL,40
    MOV BP, offset SPSE_MSG
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


    
