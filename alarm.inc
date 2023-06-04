.DATA
	ALRM0 DB 13,10, "                                                      		     [SPACE] ", "$"
    ALRM1 DB 13,10,"                        .-'`'-.               ______________________________ ", "$"
    ALRM2 DB 13,10,"              ,-'`'.   '._     \     ______                 ++++++++++       ","$"
    ALRM3 DB 13,10,"             /    .'  ___ `-._  |    \ .-'`      SET TIME: |   :      |      ","$"
    ALRM4 DB 13,10,"             |   .' ,-' __ `'/.`.'  ___\\                   ++++++++++       ","$"
    ALRM5 DB 13,10,"    ______  \ .' \',-' 12 '-.  '.  `-._ \   		[.] - Hour + [;]","$"
    ALRM6 DB 13,10,"    '`-. /   ` / / 11    7 1 `.  `.    '.\  		[/] - Minute + [']","$" ;
    ALRM7 DB 13,10,"       //___  . '10     /    2 \  ;            		[P] AM/PM","$"
    ALRM8 DB 13,10,"      / _.-'  | |      O      3|  |  ______      ","$"
    ALRM9 DB 13,10,"     /.'      | |9      \      '  '  '`-. /      ","$"          
    ALRM10 DB 13,10,"       ______ '  \ 8     \   4/  /      //___   ","$"
    ALRM11 DB 13,10,"       \ .-'`  '. `'.7  6  5.'  '      / _.-'   ","$"
    ALRM12 DB 13,10,"      ___\\       `. _ `'''` _.'\\-.   /.'      ","$"
    ALRM13 DB 13,10,"      `-._ \       .//`''--''   (   )           ","$"
    ALRM14 DB 13,10,"          '.\     (___)          '-`            ","$"
    ALRM15 DB 13,10,"         AAAAA  L      AAAAA  RRRR   M   M      ","$"
	ALRM16 DB 13,10,"        A     A L     A     A R   R  MM MM      ","$"
	ALRM22 DB 13,10,"        AAAAAA  L     AAAAAA  RRR    M M M           RINGTONE:        ","$"
	ALRM23 DB 13,10,"        A     A LLLLL A     A R  R   M   M     ","$" 
	ALRM17 DB 13,10,".-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-.","$"
    ALRM18 DB "       +++            +++             +++             +++           +++ ","$"
    ALRM19 DB 13,10,"      | Q |          | W +           | E |           | R |         | T |","$"
    ALRM20 DB 13,10,"       +++            +++             +++             +++           +++ ","$"
    ALRM21 DB 13,10,"      CLOCK          ALARM           TIMER         STOPWATCH       CLOSE","$"

	ALRMMSG DB "ALARM!!!!!!!","$"

	STAT_ON DB "ALARM ON  ","$"
	STAT_OF DB "ALARM OFF ","$"

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
		CALL CURS_OFF
		CALL ALRM_GUI
		CALL ALRM_HKY
		
		MOV DL, 63 ; Row and Column (DL) for RINGTONE NAME
		MOV DH, 18	
		CALL DIS_RTONE

		MOV DH,4 ;Row and Column (DL) for Hour
		MOV DL,61
		CALL SET_CRSR
		MOV AH, 0
		MOV AL, byte ptr [SET_HOUR]
		CALL DISP_DT	

		MOV DH,4 ;Row and Column (DL) for Minute
		MOV DL,64
		CALL SET_CRSR
		MOV AH, 0
		MOV AL, byte ptr [SET_MIN]
		CALL DISP_DT

		MOV DH,4 ;Row and Column (DL) for Midday
		MOV DL, 67
		CALL SET_CRSR
		MOV dl, 'A'     ; To print A
		MOV ah, 02h
		INT 21h
		MOV dl, 'M'     ; To print M
		MOV ah, 02h
		INT 21h

		MOV CX, 6
		MOV BP, offset SUN
		MOV DL, 53 ; Row and Column (DL) for sun 
		MOV DH, 10	

		CALL ADIS_OFF
		MOV CX, 6
		MOV BP, offset MON
		MOV DL, 53 ; Row and Column (DL) for Monday
		MOV DH, 12

		CALL ADIS_OFF
		MOV CX, 7
		MOV BP, offset TUE
		MOV DL, 53 ; Row and Column (DL) for TUE
		MOV DH, 14

		CALL ADIS_OFF 
		MOV CX, 9
		MOV BP, offset WED
		MOV DL, 53 ; Row and Column (DL) for WED
		MOV DH, 16

		CALL ADIS_OFF
		MOV CX, 8
		MOV BP, offset THU
		MOV DL, 68 ; Row and Column (DL) for THU
		MOV DH, 10

		CALL ADIS_OFF
		MOV CX, 6
		MOV BP, offset FRI
		MOV DL, 68 ; Row and Column (DL) for FRI
		MOV DH, 12

		CALL ADIS_OFF
		MOV CX, 8
		MOV BP, offset SAT
		MOV DL, 68 ; Row and Column (DL) for SAT
		MOV DH, 14

		CALL ADIS_OFF
		
		MOV DL, 60 ; Row and Column (DL) for ALARM OF/ON 
		MOV DH, 1	
		MOV CX, 10
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

		;Check if within the WEEKDAY
		MOV AH, 0
		MOV AL, byte ptr [SET_WKDAY]
		POP CX
		CALL READ_BIT
		CMP AL, 1
		JNE AL_RET

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

		;Check for minute
		MOV AH, 0
		MOV AL, byte ptr [SET_MIN]
		POP BX
		CMP AL, BL
		JNE AL_RET

		LEA DX, ALRMMSG
		MOV AH, 09H
		INT 21H
		
		CALL TRIG_ALM

		MOV byte ptr[SET_ALARM], 0
		MOV DL, 60 ; Row and Column (DL) for ALARM OF/ON 
		MOV DH, 1	
		MOV CX, 10
		MOV BP, offset STAT_OF
		CALL ADIS_OFF
		JMP ALARM

	AL_RET:
		MOV AH, 01H
		INT 16H
		JZ ALM_NPR
		MOV AH, 0
		INT 16H
		JMP ALM_KYPR

		ALM_KYPR:	;Alarm Key press
		CMP AL, ';'
		JE SEMICLN

		CMP AL, '.'
		JE PERIOD

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

		CMP AL, 'u'
		JE KEY_U
		CMP AL, 'U'
		JE KEY_U

		CALL MODE_MGR

		JMP ALARM
	ALM_NPR:
		JMP ALARM
	PERIOD:
		MOV DH,4 ;Row and Column (DL) for Hour
		MOV DL,61
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
		MOV DH,4 ;Row and Column (DL) for Hour
		MOV DL,61
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
		MOV DH,4 ;Row and Column (DL) for Minute
		MOV DL,64
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
		MOV DH,4 ;Row and Column (DL) for Minute
		MOV DL,64
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
		MOV DH,4 ;Row and Column (DL) for Midday
		MOV DL,67
		CALL SET_CRSR

		MOV AL, byte ptr [SET_MDDAY]
		NOT AL
		MOV byte ptr [SET_MDDAY], AL
		
		MOV AL, byte ptr [SET_MDDAY]
		CMP AL, 0FFh
		JE MD_PM
		MOV dl, 'A'     ; To print A
		MOV ah, 02h
		INT 21h

		MOV dl, 'M'     ; To print M
		MOV ah, 02h
		INT 21h
		JMP ALARM
		MD_PM:
			MOV dl, 'P'     ; To print /
			MOV ah, 02h
			INT 21h

			MOV dl, 'M'     ; To print /
			MOV ah, 02h
			INT 21h
			JMP ALARM
	KEY_SPCE: 
		CALL NTE_DO2
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
		MOV DL, 53 ; Row and Column (DL) for sun 
		MOV DH, 10	

		JMP WK_COND 
	KEY_S:
		MOV CX, 1
		CALL A_WD_BIT

		MOV CX, 6
		MOV BP, offset MON
		MOV DL, 53 ; Row and Column (DL) for Monday
		MOV DH, 12

		JMP WK_COND 
	KEY_D:
		MOV CX, 2
		CALL A_WD_BIT

		MOV CX, 7
		MOV BP, offset TUE
		MOV DL, 53 ; Row and Column (DL) for TUE
		MOV DH, 14

		JMP WK_COND 
	KEY_F:
		MOV CX, 3
		CALL A_WD_BIT

		MOV CX, 9
		MOV BP, offset WED
		MOV DL, 53 ; Row and Column (DL) for THU
		MOV DH, 16

		JMP WK_COND 
	KEY_G:
		MOV CX, 4
		CALL A_WD_BIT

		MOV CX, 8
		MOV BP, offset THU
		MOV DL, 68 ; Row and Column (DL) for FRI
		MOV DH, 10

		JMP WK_COND 
	KEY_H:
		MOV CX, 5
		CALL A_WD_BIT

		MOV CX, 6
		MOV BP, offset FRI
		MOV DL, 68 ; Row and Column (DL) for WED
		MOV DH, 12

		JMP WK_COND 
	KEY_J:
		MOV CX, 6
		CALL A_WD_BIT

		MOV CX, 8
		MOV BP, offset SAT
		MOV DL, 68 ; Row and Column (DL) for SAT
		MOV DH, 14

		JMP WK_COND 
	KEY_U:
		CALL CHG_RINDX
		MOV DL, 63 ; Row and Column (DL) for RINGTONE NAME
		MOV DH, 18	
		CALL DIS_RTONE
		JMP WK_COND
	WK_COND: ;Standard weekday conditions
		CMP AL, 1
		JE IS_EQU
		CALL ADIS_OFF
		JMP ALARM
		IS_EQU:
			CALL ADIS_ON
			JMP ALARM
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
	LEA DX, ALRM0
	MOV AH, 09H
	INT 21H

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

	LEA DX, ALRM22
	MOV AH, 09H
	INT 21H

	LEA DX, ALRM23
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

	LEA DX, ALRM21
	MOV AH, 09H
	INT 21H

	RET
ALRM_GUI ENDP


ALRM_HKY PROC ; Displays alarm hotkey
	MOV DL, 49  
	MOV DH, 10	
    MOV BP, offset HK_A
    MOV CX,3

	PUSH DS
	POP ES
	MOV AL, 1
	MOV BH, 0
	MOV BL, 00001110b
	MOV AH, 13h
	INT 10H

	MOV DL, 49 
	MOV DH, 12	
    MOV BP, offset HK_S
	INT 10H

	MOV DL, 49 
	MOV DH, 14	
    MOV BP, offset HK_d
	INT 10H

	MOV DL, 49 
	MOV DH, 16
    MOV BP, offset HK_F
	INT 10H

	MOV DL, 49 
	MOV DH, 18	
    MOV BP, offset HK_U
	INT 10H

	MOV DL, 64 
	MOV DH, 10
    MOV BP, offset HK_G
	INT 10H

	MOV DL, 64 
	MOV DH, 12	
    MOV BP, offset HK_H
	INT 10H
	
	MOV DL, 64 
	MOV DH, 14
    MOV BP, offset HK_J
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

	MOV DL, 56 
	MOV DH, 6	
    MOV BP, offset HK_DT
	INT 10H

	MOV DL, 56 
	MOV DH, 7	
    MOV BP, offset HK_SH
	INT 10H

	MOV DL, 56 
	MOV DH, 8	
    MOV BP, offset HK_P
	INT 10H

	MOV DL, 69 
	MOV DH, 6	
    MOV BP, offset HK_SN
	INT 10H

	MOV DL, 71 
	MOV DH, 7	
    MOV BP, offset HK_AE
	INT 10H

	MOV CX,7
	MOV DL, 70 
	MOV DH, 1	
    MOV BP, offset HK_SE
	INT 10H

	RET
ALRM_HKY ENDP
		
    	