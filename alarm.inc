.DATA
	; SPACE1 DB 13,10,"               		     										  +++++++++				","$"
    ; SPACE2 DB 13,10,"                            									     |           | 				","$"
    ; SPACE3 DB 13,10,"                         														++++++++++ 				","$"
	SPACE DB 13,10, "                                                      		     [SPACE] ", "$"
    ALRM1 DB 13,10,"                        .-'`'-.                      		     ", "$"
    ALRM2 DB 13,10,"              ,-'`'.   '._     \     ______                      ","$"
    ALRM3 DB 13,10,"             /    .'  ___ `-._  |    \ .-'`   [.] Hour [:] Minute [P] AM/PM","$"
    ALRM4 DB 13,10,"             |   .' ,-' __ `'/.`.'  ___\\                        ","$"
    ALRM5 DB 13,10,"    ______  \ .' \',-' 12 '-.  '.  `-._ \                        ","$"
    ALRM6 DB 13,10,"    '`-. /   ` / / 11    7 1 `.  `.    '.\    [A]                 ","$"
    ALRM7 DB 13,10,"       //___  . '10     /    2 \  ;           [S]                 ","$"
    ALRM8 DB 13,10,"      / _.-'  | |      O      3|  |  ______   [D]                   ","$"
    ALRM9 DB 13,10,"     /.'      | |9      \      '  '  '`-. /   [F]                   ","$"
    ALRM10 DB 13,10,"       ______ '  \ 8     \   4/  /      //___ [G]                    ","$"
    ALRM11 DB 13,10,"       \ .-'`  '. `'.7  6  5.'  '      / _.-' [H]                    ","$"
    ALRM12 DB 13,10,"      ___\\       `. _ `'''` _.'\\-.   /.'    [S]                     ","$"
    ALRM13 DB 13,10,"      `-._ \       .//`''--''   (   )                            ","$"
    ALRM14 DB 13,10,"          '.\     (   )          '-`                             ","$"
    ALRM15 DB 13,10,"                   `-'                                           ","$" 
    ALRM16 DB 13,10,"                    ALARM CLOCK                         	      ","$"
    ALRM17 DB 13,10,13,10,"       +++            +++             +++             +++           +++ ","$"
    ALRM18 DB 13,10,"      | Q |          | W +           | E |           | R |         | T |","$"
    ALRM19 DB 13,10,"       +++            +++             +++             +++           +++ ","$"
    ALRM20 DB 13,10,"      CLOCK          ALARM           TIMER         STOPWATCH       CLOSE","$"

	;TEMP ONLY REMOVE LATER
	TEST1 DB "COND REACHED HERE1","$"
	TEST2 DB "COND REACHED HERE2","$"
	TEST3 DB "COND REACHED HERE3","$"
	TEST4 DB "COND REACHED HERE4","$"
	TEST5 DB "COND REACHED HERE5","$"

	ALRMMSG DB "ALARM!!!!!!!","$"


	
	STAT_ON DB "ALARM ON ","$"
	STAT_OF DB "ALARM OFF","$"

	colon DB ":", "$"

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
		ALM_INIT:
			
			CALL RST_CRSR
			CALL CLRSCR
			CALL COLOR
			CALL ALRM_GUI

			MOV DH,5 ;Row and Column (DL) for Hour
			MOV DL,55
			CALL SET_CRSR
			MOV AH, 0
			MOV AL, byte ptr [SET_HOUR]
			CALL DISP_DT	

			MOV DH,5 ;Row and Column (DL) for Minute
			MOV DL,58
			CALL SET_CRSR
			MOV AH, 0
			MOV AL, byte ptr [SET_MIN]
			CALL DISP_DT

			MOV DH,5 ;Row and Column (DL) for Midday
			MOV DL, 61
			CALL SET_CRSR
			mov dl, 'A'     ; To print /
			mov ah, 02h
			int 21h
			mov dl, 'M'     ; To print /
			mov ah, 02h
			int 21h

		
			MOV CX, 6
			MOV BP, offset SUN
			MOV DL, 50 ; Row and Column (DL) for sun 
			MOV DH, 7	

			CALL ADIS_OFF
			MOV CX, 6
			MOV BP, offset MON
			MOV DL, 50 ; Row and Column (DL) for Monday
			MOV DH, 8

			CALL ADIS_OFF
			MOV CX, 7
			MOV BP, offset TUE
			MOV DL, 50 ; Row and Column (DL) for TUE
			MOV DH, 9

			CALL ADIS_OFF 
			MOV CX, 9
			MOV BP, offset WED
			MOV DL, 50 ; Row and Column (DL) for WED
			MOV DH, 10

			CALL ADIS_OFF
			MOV CX, 8
			MOV BP, offset THU
			MOV DL, 50 ; Row and Column (DL) for WED
			MOV DH, 11

			CALL ADIS_OFF
			MOV CX, 6
			MOV BP, offset FRI
			MOV DL, 50 ; Row and Column (DL) for WED
			MOV DH, 12

			CALL ADIS_OFF
			MOV CX, 8
			MOV BP, offset SAT
			MOV DL, 50 ; Row and Column (DL) for SAT
			MOV DH, 13

			CALL ADIS_OFF
			
			MOV DL, 60 ; Row and Column (DL) for ALARM OF/ON 
			MOV DH, 1	
			MOV CX, 9
			MOV BP, offset STAT_OF
			CALL ADIS_OFF

		ALARM:
			; Clear Keyboard Buffer
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
			
			CALL RING2

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
			MOV DL,55
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
			MOV DL,55
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
			MOV DL,58
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
			MOV DL,58
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
			MOV DL,61
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
			CALL ADIS_OFF
			JMP ALARM
			ALRM_ON:
	
				MOV BP, offset STAT_ON
				CALL ADIS_ON
				JMP ALARM
	
		KEY_A:
			MOV CX, 0	
			CALL A_WD_BIT

			MOV CX, 6
			MOV BP, offset SUN
			MOV DL, 50 ; Row and Column (DL) for sun 
			MOV DH, 7	

			JMP WK_COND 
		KEY_S:
			MOV CX, 1
			CALL A_WD_BIT

			MOV CX, 6
			MOV BP, offset MON
			MOV DL, 50 ; Row and Column (DL) for Monday
			MOV DH, 8

			JMP WK_COND 
		KEY_D:
			MOV CX, 2
			CALL A_WD_BIT

			MOV CX, 7
			MOV BP, offset TUE
			MOV DL, 50 ; Row and Column (DL) for TUE
			MOV DH, 9

			JMP WK_COND 
		KEY_F:
			MOV CX, 3
			CALL A_WD_BIT

			MOV CX, 9
			MOV BP, offset WED
			MOV DL, 50 ; Row and Column (DL) for WED
			MOV DH, 10

			JMP WK_COND 

		KEY_G:
			MOV CX, 4
			CALL A_WD_BIT

			MOV CX, 8
			MOV BP, offset THU
			MOV DL, 50 ; Row and Column (DL) for WED
			MOV DH, 11

			JMP WK_COND 
		KEY_H:
			MOV CX, 5
			CALL A_WD_BIT

			MOV CX, 6
			MOV BP, offset FRI
			MOV DL, 50 ; Row and Column (DL) for WED
			MOV DH, 12

			JMP WK_COND 

		KEY_J:
			MOV CX, 6
			CALL A_WD_BIT

			MOV CX, 8
			MOV BP, offset SAT
			MOV DL, 50 ; Row and Column (DL) for SAT
			MOV DH, 13

			JMP WK_COND 

		WK_COND: ;Standard weekday conditions
			CMP AL, 1
			JE IS_EQU
			CALL ADIS_OFF
			JMP ALARM
			IS_EQU:
				CALL ADIS_ON
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

ADIS_ON PROC ; Alarm status ON
	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00000010b
	MOV AH, 13h
	INT 10H
	RET
ADIS_ON ENDP

ADIS_OFF PROC ;Alarm status of
	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00001000b
	MOV AH, 13h
	INT 10H
	RET
ADIS_OFF ENDP

ALRM_GUI PROC ;Alarm Gui

		; LEA DX, SPACE3
		; MOV AH, 09H
		; INT 21H 

		LEA DX, SPACE
		MOV AH, 09H
		INT 21H 

		; LEA DX, SPACE2
		; MOV AH, 09H
		; INT 21H 

		; LEA DX, SPACE3
		; MOV AH, 09H
		; INT 21H 

		; LEA DX, SPACE4
		; MOV AH, 09H
		; INT 21H 

		LEA DX, ALRM1
		MOV AH, 09H
		INT 21H
		
		LEA DX, ALRM2
		MOV AH, 09H
		INT 21H
		
		LEA DX, ALRM3
		MOV AH, 09H
		INT 21H
		
		LEA DX, ALRM4
		MOV AH, 09H
		INT 21H
		
		LEA DX, ALRM5
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM6
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM7
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM8
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM9
		MOV AH, 09H
		INT 21H
		
		LEA DX, ALRM10
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM11
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM12
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM13
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM14
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM15
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM16
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM17
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM18
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM19
		MOV AH, 09H
		INT 21H

		LEA DX, ALRM20
		MOV AH, 09H
		INT 21H

ALRM_GUI ENDP
		
    	