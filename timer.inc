.DATA
        ;              777777                 
        ;             77777777                
        ;               ~~~~                  
        ;    7777  BBBBBBBBBBBBBB  777        
        ;     7~BBBB##       5##BBBB~7        
        ;     BBB#       &&  55555#BBB        
        ;    BBB         && 55555555BBB       
        ;   BBB          &&5555555555BBB      
        ;   BB#          &&5555555555#BB      
        ;  BBB           BB55555555555BBB     
        ;  BBB          B  &&         BBB     
        ;   BB#       B      &&      #BB      
        ;    BB#                    #BB       
        ;     BBB#                #BBB        
        ;      BBBB#            #BBBB         
        ;         BBBBBBBBBBBBBBBB            
        ;              BBBBBB 
    TMR1 DB 13,10,"                                                         777777             ", "$"                
    TMR2 DB 13,10,"              ****TIMER****                             77777777           ", "$"             
    TMR3 DB 13,10,"                                                          ++++             ", "$"            
    TMR4 DB 13,10,"                                              7777  BBBBBBBBBBBBBB  777    ", "$"  
    TMR5 DB 13,10,"       START      STOP          PAUSE/UNPAUSE  7~BBBB##       5##BBBB~7", "$" 
    TMR6 DB 13,10,"                                                 BBB#       &&  55555#BBB    ", "$" 
    TMR7 DB 13,10,"        ++++   ++++   ++++   ++++               BBB         && 55555555BBB   ", "$" 
    TMR8 DB 13,10,"       | 00 | | 00 | | 00 | | 00 |            BBB          &&5555555555BBB   ", "$" 
    TMR9 DB 13,10,"        ++++   ++++   ++++   ++++             BB#          &&5555555555#BB   ", "$" 
    TMR10 DB 13,10,"                                             BBB           BB55555555555BBB  ", "$" 
    TMR11 DB 13,10,"       - DAY +           - MINUTE +          BBB          B  &&         BBB  ", "$" 
    TMR12 DB 13,10,"                                               BB#       B      &&      #BB   ", "$" 
    TMR13 DB 13,10,"       - HOUR +          - SECOND +             BB#                    #BB    ", "$" 
    TMR14 DB 13,10,"                                                 BBB#      CLOCK     #BBB     ", "$" 
    TMR15 DB 13,10,"                                                    BBBB#            #BBBB    ", "$" 
    TMR16 DB 13,10,"          STATUS:                                     BBBBBBBBBBBBBBBB        ", "$" 
    TMR17 DB 13,10,"          CHANGE RINGTONE: Sweet Child                     BBBBBB             ", "$"
    LINE1 DB 13,10,13,10,13,10,".-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-.","$"
    TMR18 DB "       +++            +++             +++             +++           +++ ","$"
    TMR19 DB 13,10,"      | Q |          | W +           | E |           | R |         | T |","$"
    TMR20 DB 13,10,"       +++            +++             +++             +++           +++ ","$"
    TMR21 DB 13,10,"      CLOCK          ALARM           TIMER         STOPWATCH       CLOSE","$"
    
    TMR_SDAY DW 0 ;Timer Set Day
    TMR_SHR DB 0 ;Timer Set Hour
    TMR_SMIN DB 0 ;Timer Set Minute
    TMR_SSEC DB 0 ;Timer Set Second
    TMR_RDAY DW 0 ;Timer Remaining Day
    TMR_RHR DB 0 ;Timer Remaining Hour
    TMR_RMIN DB 0 ;Timer Remaining Minute
    TMR_RSEC DB 0 ;Timer Remaining Second
    TMR_RUN DB 0 ;Timer Running?
    TMR_ACT DB 0 ;Timer Active?
    TDBG_MDE DB 0 ; Boolean for debug mode

    TRUN_MSG DB 'Timer Running','$'
    TPSE_MSG DB 'Timer Paused ','$'
    TSET_MSG DB 'Set Timer    ','$'
    TTUP_MSG DB 'Times Up!    ','$'




.CODE
TMR_MAIN PROC
    TMR_INIT:

        CALL RST_CRSR
        CALL CLRSCR
        CALL COLOR
	    CALL TIMRGUI
        CALL DIS_STMR
        CALL TDIS_SET
        CALL TMR_HKY

    TIMER:
        MOV AH, 01H
        INT 16H
        JZ TMR_NPR
        MOV AH, 0
        INT 16H
        JMP TMR_KYPR
        TMR_KYPR: ; Stopwatch key press
            CMP AL, 'K'
            JE T_KEY_K
            CMP AL, 'k'
            JE T_KEY_K

            CMP AL, 'M'
            JE T_KEY_M
            CMP AL, 'm'
            JE T_KEY_M

            CMP AL, 'l'
            JE T_KEY_L
            CMP AL, 'L'
            JE T_KEY_L

            CMP AL, ','
            JE T_KEY_CM
 
            CMP AL, ';'
            JE T_KEY_SN

            CMP AL, '.'
            JE T_KEY_DT 

            CMP AL, 39
            JE T_KEY_AE

            CMP AL, '/'
            JE T_KEY_SH

            CMP AL, 'z'
            JE T_STP
            CMP AL, 'Z'
            JE T_STP

            CMP AL, 'x'
            JE T_SRT
            CMP AL, 'X'
            JE T_SRT

            CMP AL, ' '
            JE T_TGLE

            CMP AL, ']' ;For debugging only, enables 1 second delay
            JE TENA_DBG
            CMP AL, '\';For debugging only, disables 1 second delay
            JE TDIS_DBG
            
            CALL MODE_MGR

            JMP TIMER
        T_KEY_K:
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AX, word ptr [TMR_SDAY]
            INC AX
            CMP AX, 100
            JE TIMER

            MOV word ptr [TMR_SDAY], AX
            CALL DIS_STMR
            JMP TIMER
        T_KEY_M:
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AX, word ptr [TMR_SDAY]
            DEC AL
            CMP AL, 0
            JL TIMER
            MOV word ptr [TMR_SDAY], AX
            CALL DIS_STMR
            JMP TIMER
        T_KEY_L:
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AL, byte ptr [TMR_SHR]
            INC AL
            CMP AL, 24
            JGE T_RST_HR
            MOV byte ptr [TMR_SHR], AL
            CALL DIS_STMR
            JMP TIMER
            T_RST_HR:
                MOV byte ptr [TMR_SHR], 0
                CALL DIS_STMR
                JMP TIMER
        T_KEY_CM: ; Comma
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AL, byte ptr [TMR_SHR]
            DEC AL
            CMP AL, 0
            JLE T_RST_HR1
            MOV byte ptr [TMR_SHR], AL
            CALL DIS_STMR
            JMP TIMER
            T_RST_HR1:
                MOV byte ptr [TMR_SHR], 23
                CALL DIS_STMR
                JMP TIMER
        T_KEY_SN: ; Semicolon
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AL, byte ptr [TMR_SMIN]
            INC AL
            CMP AL, 60
            JGE T_RST_MIN
            MOV byte ptr [TMR_SMIN], AL
            CALL DIS_STMR
            JMP TIMER
            T_RST_MIN:
                MOV byte ptr [TMR_SMIN], 0
                CALL DIS_STMR
                JMP TIMER
        T_KEY_DT: ; Dot
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AL, byte ptr [TMR_SMIN]
            DEC AL
            CMP AL, 0
            JL T_RST_MIN1
            MOV byte ptr [TMR_SMIN], AL
            CALL DIS_STMR
            JMP TIMER
            T_RST_MIN1:
                MOV byte ptr [TMR_SMIN], 59
                CALL DIS_STMR
                JMP TIMER
        T_KEY_AE: ; Apostrophe
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            MOV AL, byte ptr [TMR_SSEC]
            INC AL
            CMP AL, 60
            JGE T_RST_SEC
            MOV byte ptr [TMR_SSEC], AL
            CALL DIS_STMR
            JMP TIMER
            T_RST_SEC:
                MOV byte ptr [TMR_SSEC], 0
                CALL DIS_STMR
                JMP TIMER
        TDIS_DBG:
            MOV byte ptr [TDBG_MDE],0
            JMP TIMER
        TENA_DBG:
            MOV byte ptr [TDBG_MDE],1
            JMP TIMER
        T_SRT:
            MOV AH, byte ptr [TMR_ACT] ; If timer is active, ignore keypress
            CMP AH, 1
            JE TIMER

            ; If timer set is empty (all zero), ignore keypress
            MOV AX, word ptr [TMR_SDAY]
            MOV AH, 0
            OR AL, byte ptr [TMR_SSEC]
            OR AL, byte ptr [TMR_SMIN]
            OR AL, byte ptr [TMR_SHR]
            JZ TIMER

            MOV AX, word ptr [TMR_SDAY]
            MOV word ptr [TMR_RDAY], AX

            MOV AH,byte ptr [TMR_SHR]
            MOV byte ptr [TMR_RHR], AH

            MOV AH,byte ptr [TMR_SMIN]
            MOV byte ptr [TMR_RMIN], AH

            MOV AH,byte ptr [TMR_SSEC]
            MOV byte ptr [TMR_RSEC],AH

            MOV byte ptr [TMR_ACT], 1
            MOV byte ptr [TMR_RUN], 1

            CALL TDIS_ON
            JMP TIMER
        T_STP: ; Timer stop
            MOV byte ptr [TMR_RUN], 0
            MOV byte ptr [TMR_ACT], 0
            CALL DIS_STMR
            CALL TDIS_SET
            JMP TIMER
        T_KEY_SH: ;Slash
            MOV AL, byte ptr [TMR_SSEC] 
            DEC AL
            CMP AL, 0
            JL T_RST_SEC1
            MOV byte ptr [TMR_SSEC], AL
            CALL DIS_STMR
            JMP TIMER
            T_RST_SEC1:
                MOV byte ptr [TMR_SSEC], 59
                CALL DIS_STMR
                JMP TIMER
        T_TGLE: ; Timer toggle
            CMP byte ptr [TMR_ACT], 0
            JE TIMER
            MOV AL, byte ptr [TMR_RUN]
            CMP AL, 1
            JE T_OFF
            ; T_ON:
                MOV byte ptr [TMR_RUN], 1
                CALL TDIS_ON
                JMP TIMER
            T_OFF:
                CALL TDIS_OFF
                MOV byte ptr[TMR_RUN], 0
                JMP TIMER

        TICK_TMR: 
            CMP byte ptr [TDBG_MDE], 0 ; If debugging is disabled, skip; enable 1 sec delay)
            JNE TNO_DBG
            CALL DELAY_1SC
            TNO_DBG:

            MOV BX, word ptr [TMR_RDAY]
            MOV CH, byte ptr [TMR_RHR]
            MOV CL, byte ptr [TMR_RMIN]
            MOV DH, byte ptr [TMR_RSEC]
            CALL SUB_SEC
            MOV word ptr [TMR_RDAY], BX
            MOV byte ptr [TMR_RHR], CH
            MOV byte ptr [TMR_RMIN], CL
            MOV byte ptr [TMR_RSEC], DH
            CALL DIS_RTMR
            

            ;Checks if timer expired (from seconds to day)
            MOV AL, byte ptr [TMR_RSEC]
            CMP AL, 0
            JNE TIMER

            MOV AL, byte ptr [TMR_RMIN]
            CMP AL, 0
            JNE TIMER

            MOV AL, byte ptr [TMR_RHR]
            CMP AL, 0
            JNE TIMER

            MOV AX, word ptr [TMR_RDAY]
            CMP AX, 0
            JNE TIMER

            ;Timer expired
            CALL TDIS_UP
            CALL RING2
            JMP T_STP    
            
        TMR_NPR: ;Stopwatch no press
            MOV AH, byte ptr [TMR_ACT]
            CMP AH, 0
            JE TIMER
            MOV AH, byte ptr [TMR_RUN]
            CMP AH, 1
            JE TICK_TMR
            JMP TIMER
TMR_MAIN ENDP

DIS_RTMR PROC ; Display Remaining Timer
    MOV DH,8 ;Row and Column (DL) for Timer Day
    MOV DL,9
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_RDAY]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Timer Hour
    MOV DL,16
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_RHR]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Timer Minute
    MOV DL,23
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_RMIN]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Timer Second
    MOV DL,30
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_RSEC]

    CALL DISP_DT	
    RET
DIS_RTMR ENDP

DIS_STMR PROC ; Display Set Timer
    MOV DH,8 ;Row and Column (DL) for Timer Day
    MOV DL,9
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_SDAY]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Timer Hour
    MOV DL,16
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_SHR]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Timer Minute
    MOV DL,23
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_SMIN]
    CALL DISP_DT	

    MOV DH,8 ;Row and Column (DL) for Timer Second
    MOV DL,30
    CALL SET_CRSR
    MOV AH, 0
    MOV AL, byte ptr [TMR_SSEC]
    CALL DISP_DT	
    RET
DIS_STMR ENDP

TDIS_ON PROC ; Timer status ON
    MOV DH,16 ;Row and Column (DL) for Timer Status Label ON
    MOV DL,18
    MOV BP, offset TRUN_MSG
    mov CX,13

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000010b
	MOV AH, 13h
	INT 10H
	RET
TDIS_ON ENDP

TDIS_SET PROC ; Timer status SET
    MOV DH,16 ;Row and Column (DL) for Timer Status Label SET
    MOV DL,18
    MOV BP, offset TSET_MSG
    mov CX,13

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000010b
	MOV AH, 13h
	INT 10H
	RET
TDIS_SET ENDP

TDIS_OFF PROC ;Timer status OFF

    MOV DH,16 ;Row and Column (DL) for Timer Status Label OFF
    MOV DL,18
    MOV BP, offset TPSE_MSG
    mov CX,13

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000100b
	MOV AH, 13h
	INT 10H
	RET
TDIS_OFF ENDP

TDIS_UP PROC ;Timer status UP

    MOV DH,16 ;Row and Column (DL) for Timer Status Label UP
    MOV DL,18
    MOV BP, offset TTUP_MSG
    mov CX,13

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000100b
	MOV AH, 13h
	INT 10H
	RET
TDIS_UP ENDP

TIMRGUI PROC ;Timer Gui

		LEA DX, TMR1
		MOV AH, 09H
		INT 21H

        LEA DX, TMR2
		MOV AH, 09H
		INT 21H

        LEA DX, TMR3
		MOV AH, 09H
		INT 21H

        LEA DX, TMR4
		MOV AH, 09H
		INT 21H

        LEA DX, TMR5
		MOV AH, 09H
		INT 21H

        LEA DX, TMR6
		MOV AH, 09H
		INT 21H

        LEA DX, TMR7
		MOV AH, 09H
		INT 21H

        LEA DX, TMR8
		MOV AH, 09H
		INT 21H

        LEA DX, TMR9
		MOV AH, 09H
		INT 21H

        LEA DX, TMR10
		MOV AH, 09H
		INT 21H

        LEA DX, TMR11
		MOV AH, 09H
		INT 21H

        LEA DX, TMR12
		MOV AH, 09H
		INT 21H

        LEA DX, TMR13
		MOV AH, 09H
		INT 21H

        LEA DX, TMR14
		MOV AH, 09H
		INT 21H

        LEA DX, TMR15
		MOV AH, 09H
		INT 21H

        LEA DX, TMR16
		MOV AH, 09H
		INT 21H

        LEA DX, TMR17
		MOV AH, 09H
		INT 21H

        LEA DX, LINE1
		MOV AH, 09H
		INT 21H

        LEA DX, TMR18
		MOV AH, 09H
		INT 21H

        LEA DX, TMR19
		MOV AH, 09H
		INT 21H

        LEA DX, TMR20
		MOV AH, 09H
		INT 21H

        LEA DX, TMR21
		MOV AH, 09H
		INT 21H

        ret

TIMRGUI ENDP

TMR_HKY PROC ; Displays alarm hotkey
 
	MOV DL, 3  ; column/row
	MOV DH, 5	
    MOV BP, offset HKT_ST
    mov CX,3
	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00001110b
	MOV AH, 13h
	INT 10H

    MOV DL, 7
	MOV DH, 22	
    MOV BP, offset HK_Q
	INT 10H

	MOV DL, 22
	MOV DH, 22	
    MOV BP, offset HK_W
	INT 10H

	MOV DL, 38
	MOV DH, 22	
    MOV BP, offset HK_E
	INT 10H

	MOV DL, 54
	MOV DH, 22	
    MOV BP, offset HK_R
	INT 10H

	MOV DL, 68
	MOV DH, 22	
    MOV BP, offset HK_T
	INT 10H

	MOV DL, 14 
	MOV DH, 5	
    MOV BP, offset HKT_S
	INT 10H

    MOV DL, 3 
	MOV DH, 11	
    MOV BP, offset HKT_M
	INT 10H

    MOV DL, 15 
	MOV DH, 11	
    MOV BP, offset HKT_K
	INT 10H

    MOV DL, 3 
	MOV DH, 13	
    MOV BP, offset HKT_DC
	INT 10H

    MOV DL, 16 
	MOV DH, 13	
    MOV BP, offset HKT_L
	INT 10H

    MOV DL, 21 
	MOV DH, 11	
    MOV BP, offset HKT_DM
	INT 10H

    MOV DL, 36
	MOV DH, 11	
    MOV BP, offset HKT_IM
	INT 10H

    MOV DL, 21 
	MOV DH, 13	
    MOV BP, offset HKT_DS
	INT 10H

    MOV DL, 36
	MOV DH, 13	
    MOV BP, offset HKT_IS
	INT 10H

    MOV CX, 7
    MOV DL, 24 
	MOV DH, 5	
    MOV BP, offset HKT_SP
	INT 10H

	RET
TMR_HKY ENDP