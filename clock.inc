.DATA

    CLCK1 DB 13,10,13,10,"               .d8888b.  888      .d88888b.   .d8888b.  888    d8P          ", "$"                
    CLCK2 DB 13,10,"              d88P  Y88b 888     d88P' 'Y88b d88P  Y88b 888   d8P           ", "$"             
    CLCK3 DB 13,10,"              888    888 888     888     888 888    888 888  d8P            ", "$"            
    CLCK4 DB 13,10,"              888        888     888     888 888        888d88K             ", "$"  
    CLCK5 DB 13,10,"              888        888     888     888 888        8888888b            ", "$" 
    CLCK6 DB 13,10,"              888    888 888     888     888 888    888 888  Y88b           ", "$" 
    CLCK7 DB 13,10,"              Y88b  d88P 888     Y88b. .d88P Y88b  d88P 888   Y88b          ", "$" 
    CLCK8 DB 13,10,"                'Y8888P'  88888888 'Y88888P'   'Y8888P'  888    Y88b        ", "$" 
    CLCK9 DB 13,10,13,10,"             +++++++++++++++++++++++++     ++++++++++++++++++++++++++     ", "$" 
    CLCK10 DB 13,10,"             | DATE | JUNE 03, 2023  |     | TIME++| HR MN SC MS    |      ", "$" 
    CLCK11 DB 13,10,"             | DAY  | WED            |     | ++++++| 10:52:12.52 PM |      ", "$" 
    CLCK12 DB 13,10,"             +++++++++++++++++++++++++     ++++++++++++++++++++++++++      ", "$" 
    CLCK13 DB 13,10,"                                                                           ", "$" 
    CLCK14 DB 13,10,"                           +++++++++++++++++++++++++++++                   ", "$" 
    CLCK15 DB 13,10,"                           |     GOD BLESS EVERYONE    |                   ", "$" 
    CLCK16 DB 13,10,"                           +++++++++++++++++++++++++++++                   ", "$"
    CLCK19 DB 13,10,13,10,".-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-.","$"
    CLCK20 DB "       +++            +++             +++             +++           +++ ","$"
    CLCK21 DB 13,10,"      | Q |          | W +           | E |           | R |         | T |","$"
    CLCK22 DB 13,10,"       +++            +++             +++             +++           +++ ","$"
    CLCK23 DB 13,10,"      CLOCK          ALARM           TIMER         STOPWATCH       CLOSE","$"


.CODE

CK_MAIN PROC
    CK_INIT:

        CALL RST_CRSR
        CALL CLRSCR
        CALL COLOR
        CALL CLCK_GUI
        CALL CLCK_HKY
        
    CLOCK:
        CALL DELAY
        
        MOV DX, 0D35H    ;DH DL Row/Column
        CALL SET_CRSR
        CALL PRNT_TME

        MOV DX, 0C16H
        CALL SET_CRSR
        CALL PRNT_DTE

        MOV DX, 0D16H
        CALL SET_CRSR
        CALL PRNT_DOW


        MOV AH, 01H
        INT 16H
        JZ CLK_NPR
        MOV AH, 0
        INT 16H
        JMP CLK_KYPR

        CLK_KYPR:	;Alarm Key press
            CALL MODE_MGR
        CLK_NPR: ; Clock  no press
            JMP CLOCK

        ; MOV AH, 01H
        ; INT 16H
        ; CALL ENDPROG
        ; JMP START

    RET
CK_MAIN ENDP

CLCK_GUI PROC ;Timer Gui

		LEA DX, CLCK1
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK2
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK3
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK4
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK5
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK6
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK7
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK8
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK9
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK10
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK11
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK12
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK13
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK14
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK15
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK16
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK19
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK20
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK21
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK22
		MOV AH, 09H
		INT 21H

        LEA DX, CLCK23
		MOV AH, 09H
		INT 21H

        ret
CLCK_GUI ENDP

CLCK_HKY PROC ; Displays alarm hotkey
 
	; MOV DL, 3  ; column/row
	; MOV DH, 6	
    ; MOV BP, offset HK_X
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

	RET
CLCK_HKY ENDP