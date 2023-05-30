.DATA
    TMR_DAY DW 0
    TMR_HR DB 0 
    TMR_MIN DB 0
    TMR_SEC DB 0
    LAP_DAY DB 0
    LAP_HR DB 0
    LAP_MIN DB 0
    LAP_SEC DB 0

    TMR_RUN DB 0 ; Boolean for timer running

    RUN_MSG DB 'Stopwatch Running','$'
    PSE_MSG DB 'Stopwatch Paused','$'
.CODE
    TMR_MAIN PROC
        TMR_INIT:
            CALL CLRSCR
            CALL DISP_TMR
            ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
        TIMER:

            ; Clear Keyboard Buffer
			MOV AH, 0CH
			MOV AL, 0FFH
			INT 21H

            CALL GETKINas

            CMP AL, ' '
            JE TMR_TGLE


            MOV AH, byte ptr [TMR_RUN]
            CMP AH, 0FFH
            JE TICK

            JMP TIMER

            ; CMP AL, 
            ; JMP TIMER
            
        TMR_TGLE:
            MOV AL, byte ptr [TMR_RUN]
            NOT AL
            MOV byte ptr [TMR_RUN], AL  
            JMP TIMER
        TICK:
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

            CALL DELAY_1SC
            JMP TIMER

    TMR_MAIN ENDP

    ; TCK_TMER PROC
    ;     MOV BX, word ptr [TMR_DAY]
    ;     MOV CH, byte ptr [TMR_HR]
    ;     MOV CL, byte ptr [TMR_MIN]
    ;     MOV DH, byte ptr [TMR_SEC]
    ;     CALL ADD_SEC
        
    ;     MOV  word ptr [TMR_DAY], BX
    ;     MOV  byte ptr [TMR_HR], CH           
    ;     MOV  byte ptr [TMR_MIN], CL
    ;     MOV  byte ptr [TMR_SEC], DH

    ;     CALL DISP_TMR

    ;     CALL DELAY_1SC
    ;     RET
    ; TCK_TMER ENDP

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

    DISP_LTR ENDP

    

    
