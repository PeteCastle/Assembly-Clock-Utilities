.DATA
    ALRM1 DB 13,10,13,10,"                                  .-'`'-.                                   ", "$"
    ALRM2 DB 13,10,"                        ,-'`'.   '._     \     ______                      ","$"
    ALRM3 DB 13,10,"                       /    .'  ___ `-._  |    \ .-'`                      ","$"
    ALRM4 DB 13,10,"                      |   .' ,-' __ `'/.`.'  ___\\                         ","$"
    ALRM5 DB 13,10,"              ______  \ .' \',-' 12 '-.  '.  `-._ \                        ","$"
    ALRM6 DB 13,10,"              '`-. /   ` / / 11    7 1 `.  `.    '.\                       ","$"
    ALRM7 DB 13,10,"                 //___  . '10     /    2 \  ;                              ","$"
    ALRM8 DB 13,10,"                / _.-'  | |      O      3|  |  ______                      ","$"
    ALRM9 DB 13,10,"               /.'      | |9      \      '  '  '`-. /                      ","$"
    ALRM10 DB 13,10,"                ______ '  \ 8     \   4/  /      //___                    ","$"
    ALRM11 DB 13,10,"                 \ .-'`  '. `'.7  6  5.'  '      / _.-'                    ","$"
    ALRM12 DB 13,10,"               ___\\       `. _ `'''` _.'\\-.   /.'                        ","$"
    ALRM13 DB 13,10,"               `-._ \       .//`''--''   (   )                            ","$"
    ALRM14 DB 13,10,"                   '.\     (   )          '-`                             ","$"
    ALRM15 DB 13,10,"                            `-'                                           ","$" 
    ALRM16 DB 13,10,"                             ALARM CLOCK                             ","$"
    ALRM17 DB 13,10,13,10,13,10,"       +++            +++             +++             +++           +++ ","$"
    ALRM18 DB 13,10,"      | Q |          | W +           | E |           | R |         | T |","$"
    ALRM19 DB 13,10,"       +++            +++             +++             +++           +++ ","$"
    ALRM20 DB 13,10,"      CLOCK          ALARM           TIMER         STOPWATCH       CLOSE",13,10,13,10,13,10,"$"

	;TEMP ONLY REMOVE LATER
	TEST1 DB "COND REACHED HERE1","$"
	TEST2 DB "COND REACHED HERE2","$"
	TEST3 DB "COND REACHED HERE3","$"
	TEST4 DB "COND REACHED HERE4","$"
	TEST5 DB "COND REACHED HERE5","$"

	ALRMMSG DB "ALARM!!!!!!!","$"

	STAT_ON DB "ALARM ON ","$"
	STAT_OF DB "ALARM OFF","$"

	SET_ALARM DB 0 ; Set alarm
	SET_WKDAY DB 0 ; Set weekday
		;Uses bitwise operations to retrieve value
			;Bit 0 = Sunday
			;Bit 6 = Saturday
	SET_HOUR DB 4
	SET_MIN DB 11
	SET_MDDAY DB 0 ; Set midday : Binary 0 = AM, 1 = PM


.CODE

AL_MAIN PROC
		INIT:
			
			CALL RST_CRSR
			CALL CLRSCR

			MOV DH,5 ;Row and Column (DL) for Hour
			MOV DL,40
			CALL SET_CRSR
			MOV AH, 0
			MOV AL, byte ptr [SET_HOUR]
			CALL DISP_DT	

			MOV DH,5 ;Row and Column (DL) for Minute
			MOV DL,50
			CALL SET_CRSR
			MOV AH, 0
			MOV AL, byte ptr [SET_MIN]
			CALL DISP_DT

			MOV DH,5 ;Row and Column (DL) for Midday
			MOV DL,60
			CALL SET_CRSR
			mov dl, 'A'     ; To print /
			mov ah, 02h
			int 21h
			mov dl, 'M'     ; To print /
			mov ah, 02h
			int 21h

			MOV CX, 6
			MOV BP, offset SUN
			MOV DL, 10 ; Row and Column (DL) for sun 
			MOV DH, 7	

			CALL DISP_OFF
			MOV CX, 6
			MOV BP, offset MON
			MOV DL, 10 ; Row and Column (DL) for Monday
			MOV DH, 8

			CALL DISP_OFF
			MOV CX, 7
			MOV BP, offset TUE
			MOV DL, 10 ; Row and Column (DL) for TUE
			MOV DH, 9

			CALL DISP_OFF 
			MOV CX, 9
			MOV BP, offset WED
			MOV DL, 10 ; Row and Column (DL) for WED
			MOV DH, 10

			CALL DISP_OFF
			MOV CX, 8
			MOV BP, offset THU
			MOV DL, 10 ; Row and Column (DL) for WED
			MOV DH, 11

			CALL DISP_OFF
			MOV CX, 6
			MOV BP, offset FRI
			MOV DL, 10 ; Row and Column (DL) for WED
			MOV DH, 12

			CALL DISP_OFF
			MOV CX, 8
			MOV BP, offset SAT
			MOV DL, 10 ; Row and Column (DL) for SAT
			MOV DH, 13

			CALL DISP_OFF
			
			MOV DL, 60 ; Row and Column (DL) for ALARM OF/ON 
			MOV DH, 1	
			MOV CX, 9
			MOV BP, offset STAT_OF
			CALL DISP_OFF

		ALARM:
			MOV AH, 0CH
			MOV AL, 0FFH
			INT 21H
			
			CALL DELAY
			
			; Check if time is equal to alarm
			MOV AH, 0
			MOV AL, byte ptr [SET_ALARM] ;Checks if alarm is on
			CMP AL, 0FFh
			JNE AL_RET
			
			CALL GET_TIME
			MOV DH, 0
			MOV DL, CL
			PUSH DX
			MOV DH, 0
			MOV DL, CH
			PUSH DX
			CALL GET_DATE
			MOV DL, AL
			PUSH DX

			; ;REMOVE LATER
			; LEA DX, TEST1
			; MOV AH, 09H
			; INT 21H

			;Check if within the WEEKDAY
			MOV AH, 0
			MOV AL, byte ptr [SET_WKDAY]
			POP CX
			CALL READ_BIT
			CMP AL, 1
			JNE AL_RET

			; ;REMOVE LATER
			; LEA DX, TEST2
			; MOV AH, 09H
			; INT 21H

			;Check for hour
			MOV AH, 0
			MOV AL, byte ptr [SET_HOUR]
			MOV BL, byte ptr [SET_MDDAY]

			;Special case for 12AM
			CMP AL, 12
			JNE NOT_12AM
			CMP BL, 0
			JNE NOT_12AM
			MOV AL, 0

			; Special case for 12pm
			NOT_12AM:	
			CMP BL, 0
			JE NOT_PM
			CMP AL, 12
			JGE NOT_PM
			ADD AL, 12
			NOT_PM:
			POP BX
			
			CMP AL, BL
			JNE AL_RET

			
			; ;REMOVE LATER
			; LEA DX, TEST3
			; MOV AH, 09H
			; INT 21H
			
			;Check for minute
			MOV AH, 0
			MOV AL, byte ptr [SET_MIN]
			POP BX
			CMP AL, BL
			JNE AL_RET

			LEA DX, ALRMMSG
			MOV AH, 09H
			INT 21H

		AL_RET:
			CALL GETKINAS
			; CALL GETKIN
			
			CMP AL, ';'
			JE SEMICLN

			CMP AL, '.'
			JE PERIOD

			; CMP AL, 'Q'
			; JE KEY_Q

			; Note that apostrophe may not work for JSDOS TASM
			; But works for DOSBOX TASM
			CMP AL, 39 ; Apostrophe
			JE APSTPHE

			CMP AL, '/'
			JE SLASH

			CMP AL, 'P'
			JE KEY_P
			CMP AL, 'p'
			JE KEY_P

			CMP AL, ' ' ; Space
			JE KEY_SPCE

			CMP AL, 'A'
			JE KEY_A
			CMP AL, 'a'
			JE KEY_A

			CMP AL, 'S'
			JE KEY_S
			CMP AL, 's'
			JE KEY_S

			CMP AL, 'D'
			JE KEY_D
			CMP AL, 'd'
			JE KEY_D

			CMP AL, 'F'
			JE KEY_F
			CMP AL, 'f'
			JE KEY_F

			CMP AL, 'g'
			JE KEY_G
			CMP AL, 'G'
			JE KEY_G

			CMP AL, 'H'
			JE KEY_H
			CMP AL, 'h'
			JE KEY_H

			CMP AL, 'J'
			JE KEY_J
			CMP AL, 'j'
			JE KEY_J

			JMP ALARM
		PERIOD:
			MOV DH,5 ;Row and Column (DL) for Hour
			MOV DL,40
			CALL SET_CRSR

			MOV AL, byte ptr [SET_HOUR]
			SUB AL, 1
			JZ HR_NEGA
			MOV byte ptr [SET_HOUR], AL
			CALL DISP_DT
			JMP ALARM
			HR_NEGA:
				MOV AL, 12
				MOV byte ptr [SET_HOUR], AL
				CALL DISP_DT
				JMP ALARM	 

		SEMICLN:
			MOV DH,5 ;Row and Column (DL) for Hour
			MOV DL,40
			CALL SET_CRSR

			MOV AL, byte ptr [SET_HOUR]
			ADD AL, 1
			CMP AL, 12
			JG ABV_12
			MOV byte ptr [SET_HOUR], AL
			CALL DISP_DT
			JMP ALARM
			ABV_12:
				MOV AL, 1
				MOV byte ptr [SET_HOUR], AL
				CALL DISP_DT
				JMP ALARM
			
		APSTPHE: 
			MOV DH,5 ;Row and Column (DL) for Minute
			MOV DL,50
			CALL SET_CRSR

			MOV AL, byte ptr [SET_MIN]
			ADD AL, 1
			CMP AL, 59
			JG ABV_59
			MOV byte ptr [SET_MIN], AL
			CALL DISP_DT
			JMP ALARM
			ABV_59:
				MOV AL, 0
				MOV byte ptr [SET_MIN], AL
				CALL DISP_DT
				JMP ALARM
		SLASH:
			MOV DH,5 ;Row and Column (DL) for Minute
			MOV DL,50
			CALL SET_CRSR
			
			MOV AL, byte ptr [SET_MIN]
			SUB AL, 1
			JS MN_NEGA
			MOV byte ptr [SET_MIN], AL
			CALL DISP_DT
			JMP ALARM
			MN_NEGA:
				MOV AL, 59
				MOV byte ptr [SET_MIN], AL
				CALL DISP_DT
				JMP ALARM	
		KEY_P:
			MOV DH,5 ;Row and Column (DL) for Midday
			MOV DL,60
			CALL SET_CRSR

			MOV AL, byte ptr [SET_MDDAY]
			NOT AL
			MOV byte ptr [SET_MDDAY], AL
			
			MOV AL, byte ptr [SET_MDDAY]
			CMP AL, 0FFh
			JE MD_PM
			mov dl, 'A'     ; To print /
			mov ah, 02h
			int 21h

			mov dl, 'M'     ; To print /
			mov ah, 02h
			int 21h
			JMP ALARM
			MD_PM:
				mov dl, 'P'     ; To print /
				mov ah, 02h
				int 21h

				mov dl, 'M'     ; To print /
				mov ah, 02h
				int 21h
				JMP ALARM
		KEY_SPCE: 
			MOV AL, byte ptr [SET_ALARM]
			NOT AL
			MOV byte ptr [SET_ALARM], AL

			MOV DL, 60 ; Row and Column (DL) for ALARM OF/ON 
			MOV DH, 1	
			MOV CX, 9

			MOV AL, byte ptr [SET_ALARM]
			CMP AL, 0FFh
			JE ALRM_ON

			
			MOV BP, offset STAT_OF
			CALL DISP_OFF
			JMP ALARM
			ALRM_ON:
	
				MOV BP, offset STAT_ON
				CALL DISP_ON
				JMP ALARM
	
		KEY_A:
			MOV CX, 0	
			CALL A_WD_BIT

			MOV CX, 6
			MOV BP, offset SUN
			MOV DL, 10 ; Row and Column (DL) for sun 
			MOV DH, 7	

			JMP WK_COND 
		KEY_S:
			MOV CX, 1
			CALL A_WD_BIT

			MOV CX, 6
			MOV BP, offset MON
			MOV DL, 10 ; Row and Column (DL) for Monday
			MOV DH, 8

			JMP WK_COND 
		KEY_D:
			MOV CX, 2
			CALL A_WD_BIT

			MOV CX, 7
			MOV BP, offset TUE
			MOV DL, 10 ; Row and Column (DL) for TUE
			MOV DH, 9

			JMP WK_COND 
		KEY_F:
			MOV CX, 3
			CALL A_WD_BIT

			MOV CX, 9
			MOV BP, offset WED
			MOV DL, 10 ; Row and Column (DL) for WED
			MOV DH, 10

			JMP WK_COND 

		KEY_G:
			MOV CX, 4
			CALL A_WD_BIT

			MOV CX, 8
			MOV BP, offset THU
			MOV DL, 10 ; Row and Column (DL) for WED
			MOV DH, 11

			JMP WK_COND 
		KEY_H:
			MOV CX, 5
			CALL A_WD_BIT

			MOV CX, 6
			MOV BP, offset FRI
			MOV DL, 10 ; Row and Column (DL) for WED
			MOV DH, 12

			JMP WK_COND 

		KEY_J:
			MOV CX, 6
			CALL A_WD_BIT

			MOV CX, 8
			MOV BP, offset SAT
			MOV DL, 10 ; Row and Column (DL) for SAT
			MOV DH, 13

			JMP WK_COND 

		WK_COND: ;Standard weekday conditions
			CMP AL, 1
			JE IS_EQU
			CALL DISP_OFF
			JMP ALARM
			IS_EQU:
				CALL DISP_ON
				JMP ALARM

    ; RET
AL_MAIN ENDP

A_WD_BIT PROC ;Inverts and reads weekday bits
	MOV AH, 0
	MOV AL, byte ptr [SET_WKDAY]
	CALL INV_BIT
	MOV byte ptr [SET_WKDAY], AL
	CALL READ_BIT
	RET
A_WD_BIT ENDP

; CHK_ALRM PROC
; 	MOV AH, 0
; 	MOV AL, byte ptr [SET_ALARM] ;Checks if alarm is on
; 	CMP AL, 0FFh
; 	JNE AL_RET
	
; 	CALL GET_TIME
; 	MOV DH, 0
; 	MOV DL, CL
; 	PUSH DX
; 	MOV DH, 0
; 	MOV DL, CH
; 	PUSH DX
; 	CALL GET_DATE
; 	MOV DL, AL
; 	PUSH DX

; 	;Check if within the WEEKDAY
; 	MOV AH, 0
; 	MOV AL, byte ptr [SET_WKDAY]
; 	POP CX
; 	CALL READ_BIT
; 	CMP AL, 1
; 	JNE AL_RET

; 	;Check for hour
; 	MOV AH, 0
; 	MOV AL, byte ptr [SET_HOUR]
; 	MOV BL, byte ptr [SET_MDDAY]
; 	CMP BL, 0FFh
; 	JNE NOT_PM
; 	ADD AL, 12
; 	NOT_PM:
; 	POP BX
; 	CMP AL, BL
; 	JNE AL_RET

; 	;Check for minute
; 	MOV AH, 0
; 	MOV AL, byte ptr [SET_MIN]
; 	POP BX
; 	CMP AL, BL
; 	JNE AL_RET

; 	LEA DX, ALRMMSG
; 	MOV AH, 09H
; 	INT 21H

; 	AL_RET:
; 		RET
; CHK_ALRM ENDP

DISP_ON PROC ; Prints day on
	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000010b
	MOV AH, 13h
	INT 10H
	RET
DISP_ON ENDP

DISP_OFF PROC ; Prints day OFF
	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00001000b
	MOV AH, 13h
	INT 10H
	RET
DISP_OFF ENDP


; already merged inm ain code
; A_DIS_MD PROC ;Displays midday value
; 	MOV AL, byte ptr [SET_MDDAY]
; 	CMP AL, 0FFh
; 	JE MD_PM
; 	mov dl, 'A'     ; To print /
; 	mov ah, 02h
; 	int 21h

; 	mov dl, 'M'     ; To print /
; 	mov ah, 02h
; 	int 21h
; 	RET
; 	MD_PM:
; 		mov dl, 'P'     ; To print /
;         mov ah, 02h
;         int 21h

; 		mov dl, 'M'     ; To print /
; 		mov ah, 02h
; 		int 21h
; 		RET
; A_DIS_MD ENDP

; Already moved in main code
; A_INV_ST PROC ;Inverts alarm status (on/off)
; 	MOV AL, byte ptr [SET_ALARM]
; 	NOT AL
; 	MOV byte ptr [SET_ALARM], AL
; 	RET
; A_INV_ST ENDP

; A_DIS_ST PROC ;Displays alarm status (on/off)
; 	MOV AL, byte ptr [SET_ALARM]
; 	CMP AL, 0FFh
; 	JE ALRM_ON
; 	LEA DX, STAT_OF
; 	MOV AH, 09H
; 	INT 21H
; 	RET
; 	ALRM_ON:
; 		LEA DX, STAT_ON
; 		MOV AH, 09H
; 		INT 21H
; 		RET
; A_DIS_ST ENDP

; A_INV_MD PROC ;Inverts midday value
; 	MOV AL, byte ptr [SET_MDDAY]
; 	NOT AL
; 	MOV byte ptr [SET_MDDAY], AL
; 	RET
; A_INV_MD ENDP

; A_INC_HR PROC ; Increment hour for alarm
; 	MOV AL, byte ptr [SET_HOUR]
; 	ADD AL, 1
; 	CMP AL, 12
; 	JG ABV_12
; 	MOV byte ptr [SET_HOUR], AL
; 	RET
; 	ABV_12:
; 		MOV AL, 0
; 		MOV byte ptr [SET_HOUR], AL
; 		RET
; A_INC_HR ENDP

; Already moved in main code
; A_DEC_HR PROC ; Decrement hour for alarm
; 	MOV AL, byte ptr [SET_HOUR]
; 	SUB AL, 1
; 	JS HR_NEGA
; 	MOV byte ptr [SET_HOUR], AL
; 	RET
; 	HR_NEGA:
; 		MOV AL, 12
; 		MOV byte ptr [SET_HOUR], AL
; 		RET	 
; A_DEC_HR ENDP

; A_INC_MN PROC ; Increment minute for alarm
; 	MOV AL, byte ptr [SET_MIN]
; 	ADD AL, 1
; 	CMP AL, 59
; 	JG ABV_59
; 	MOV byte ptr [SET_MIN], AL
; 	RET
; 	ABV_59:
; 		MOV AL, 0
; 		MOV byte ptr [SET_MIN], AL
; 		RET
; A_INC_MN ENDP

; A_DEC_MN PROC ; Decrement minute for alarm
; 	MOV AL, byte ptr [SET_MIN]
; 	SUB AL, 1
; 	JS MN_NEGA
; 	MOV byte ptr [SET_MIN], AL
; 	RET
; 	MN_NEGA:
; 		MOV AL, 59
; 		MOV byte ptr [SET_MIN], AL
; 		RET	
; A_DEC_MN ENDP



		
    	