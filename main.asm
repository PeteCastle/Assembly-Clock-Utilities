
.MODEL SMALL
.STACK 100H
.386

.DATA
	;Title Screen Data
	
	TIT1 DB 13,10,13,10,13,10,"                               .'`~~~~~~~~~~~`'.                        ","$"
	TIT2 DB 13,10,"                               (  .'11 12 1'.  )                        ","$"
	TIT3 DB 13,10,"                               |  :10 \|   2:  |                        ","$" 
	TIT4 DB 13,10,"                               |  :9   @   3:  |                        ","$"
	TIT5 DB 13,10,"                               |  :8       4;  |                        ","$"
	TIT6 DB 13,10,"                               '. '..7 6 5..' .'                        ","$"
	TIT7 DB 13,10,"                                ~-------------~                         ","$" 
	TIT8 DB 13,10,"        __   __     __   ____  _  _         ___  __     __    ___  __ _ ","$"
	TIT9 DB 13,10,"       / _\ (  )   / _\ (  _ \( \/ )       / __)(  )   /  \  / __)(  / )","$"
   TIT10 DB 13,10,"      /    \/ (_/\/    \ )   // \/ \      ( (__ / (_/\(  O )( (__  )  ( ","$"
   TIT11 DB 13,10,"      \_/\_/\____/\_/\_/(__\_)\_)(_/       \___)\____/ \__/  \___)(__\_)","$"
   TIT12 DB 13,10,13,10,"               Made by: Aparici, Cayco, Morales J, Soliven, Villar           ","$"
   TIT13 DB 13,10,13,10,13,10,"       +++            +++             +++             +++           +++ ","$"
   TIT14 DB 13,10,"      | Q |          | W +           | E |           | R |         | T |","$"
   TIT15 DB 13,10,"       +++            +++             +++             +++           +++ ","$"
   TIT16 DB 13,10,"      CLOCK          ALARM           TIMER         STOPWATCH       CLOSE",13,10,13,10,13,10,"$"

	include deps/hotkeys.inc
	

	
	;User Input Variables
	INPUT DB 128 (?) ; User input
	STOR DW 0                       

.CODE
include deps/utils.inc
include deps/notes.inc
include deps/sound.inc
include core/timer.inc
include core/swatch.inc
include core/alarm.inc
include deps/datetime.inc
include core/clock.inc
include deps/math.inc

.STARTUP 
	CALL RST_CRSR
	call color
	; Print title screen
	TITSCR:

		LEA DX, TIT1
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT2
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT3
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT4
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT5
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT6
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT7
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT8
		MOV AH, 09H
		INT 21H

		LEA DX, TIT9
		MOV AH, 09H
		INT 21H

		LEA DX, TIT10
		MOV AH, 09H
		INT 21H

		LEA DX, TIT11
		MOV AH, 09H
		INT 21H

		LEA DX, TIT12
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIT13
		MOV AH, 09H
		INT 21H

		LEA DX, TIT14
		MOV AH, 09H
		INT 21H

		LEA DX, TIT15
		MOV AH, 09H
		INT 21H

		LEA DX, TIT16
		MOV AH, 09H
		INT 21H
		CALL CURS_OFF
		CALL INTRO

	TITIN:
		CALL GETKIN

		CMP AL, 'a'
		JE EASTR_DO
		CMP AL, 'A'
		JE EASTR_DO
		
		CMP AL, 'S'
		JE EASTR_RE
		CMP AL, 's'
		JE EASTR_RE

		CMP AL, 'd'
		JE EASTR_MI
		CMP AL, 'D'
		JE EASTR_MI

		CMP AL, 'f'
		JE EASTR_FA
		CMP AL, 'F'
		JE EASTR_FA

		CMP AL, 'g'
		JE EASTR_SO
		CMP AL, 'G'
		JE EASTR_SO

		CMP AL, 'h'
		JE EASTR_LA
		CMP AL, 'H'
		JE EASTR_LA

		CMP AL, 'j'
		JE EASTR_TI
		CMP AL, 'J'
		JE EASTR_TI

		CMP AL, 'k'
		JE ESTR_DO2
		CMP AL, 'K'
		JE ESTR_DO2

		CMP AL, 'L'
		JE ESTR_RE2
		CMP AL, 'l'
		JE ESTR_RE2

		JMP ESTR_AC
		EASTR_DO:
			CALL NTE_DO
			JMP TITIN
		EASTR_RE:
			CALL NTE_RE
			JMP TITIN
		EASTR_MI:
			CALL NTE_MI
			JMP TITIN
		EASTR_FA:
			CALL NTE_FA
			JMP TITIN
		EASTR_SO:
			CALL NTE_SO
			JMP TITIN
		EASTR_LA:
			CALL NTE_LA
			JMP TITIN
		EASTR_TI:
			CALL NTE_TI
			JMP TITIN
		ESTR_DO2:
			CALL NTE_DO2
			JMP TITIN
		ESTR_RE2:
			CALL NTE_RE2
			JMP TITIN
		ESTR_AC:
			CALL MODE_MGR
			JMP TITIN
	ALA_WIN:
		CALL NTE_RE
		CALL AL_MAIN
		JMP TITSCR
	TIM_WIN:
		CALL NTE_MI
		CALL TMR_MAIN
		JMP TITSCR
	SWA_WIN:
		CALL NTE_FA
		CALL SW_MAIN
		JMP TITSCR
	CLK_WIN:
		CALL NTE_DO
		CALL CK_MAIN
		JMP TITSCR
	END_WIN:
		CALL ENDPROG


   .EXIT
END

MENU_HKY PROC
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
MENU_HKY ENDP