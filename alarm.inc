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
             
.CODE
ALARM PROC
        CALL RST_CRSR
        CALL CLRSCR

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

        CALL GETKIN
    RET
ALARM ENDP