
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

	include hotkeys.inc

	;User Input Variables
	INPUT DB 128 (?) ; User input
	STOR DW 0                       
.CODE
include utils.inc
include notes.inc
include timer.inc
include swatch.inc
include alarm.inc
include datetime.inc
include clock.inc
include math.inc
include sound.inc

.STARTUP 
	
	CALL RST_CRSR
	call color
	CALL RING1

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

	TITIN:
		CALL GETKIN
		CALL MODE_MGR
		JMP TITIN
	ALA_WIN:
		CALL AL_MAIN
		JMP TITSCR
	TIM_WIN:
		CALL TMR_MAIN
		JMP TITSCR
	SWA_WIN:
		CALL SW_MAIN
		JMP TITSCR
	CLK_WIN:
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