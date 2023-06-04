.DATA
	JAN DB "January","$"
    FEB DB "February","$"
    MAR DB "March","$"
    APR DB "April","$"
    MAY DB "May","$"
    JUN DB "June","$"
    JUL DB "July","$"
    AUG DB "August","$"
    SEP DB "September","$"
    OCT DB "October","$"
    NOV DB "November","$"
    DECE DB "December","$" ;DEC - Reserved word

    MON DB "Monday","$"
    TUE DB "Tuesday","$"
    WED DB "Wednesday","$"
    THU DB "Thursday","$"
    FRI DB "Friday","$"
    SAT DB "Saturday","$"
    SUN DB "Sunday","$" 

.CODE
; INT 21h / AH=2Ch - get system time;
; return: CH = hour. CL = minute. DH = second. DL = 1/100 seconds.
GET_TIME PROC
    MOV AH, 2CH
    INT 21H
    RET
GET_TIME ENDP

; INT 21h / AH=2Ah - get system date;
; return: CX = year (1980-2099). DH = month. DL = day. AL = day of week (00h=Sunday)
GET_DATE PROC
    MOV AH, 2AH
    INT 21H
    RET
GET_DATE ENDP

PRNT_TME PROC
    CALL GET_TIME
    ;Hour
    MOV AL, CH
    MOV BL, DL

    CMP CH, 12
    JB X
    IS_PM:
        SUB AL, 12
    X:
        CALL DISP_DT
        MOV DL, ':'
        MOV AH, 02H
        INT 21H
        
        ;Minute
        MOV AL, CL
        CALL DISP_DT

        MOV DL, ':'
        MOV AH, 02H
        INT 21H

        ;Seconds
        MOV AL, DH
        CALL DISP_DT

        MOV DL, '.'
        MOV AH, 02H
        INT 21H

        ;Milliseconds
        MOV AL, BL
        CALL DISP_DT

        ;AM OR PM
        MOV DL, ' '
        MOV AH, 02H
        INT 21H

        CMP CH, 12
        JB IS_AM
        JAE IS_PM2

        IS_AM:
            MOV DL, 'A'
            MOV AH, 02H
            INT 21H
            JMP H_END
        IS_PM2:
            MOV DL, 'P'
            MOV AH, 02H
            INT 21H
            JMP H_END

        H_END:
            MOV DL, 'M'
            MOV AH, 02H
            INT 21H
    RET

PRNT_TME ENDP

PRNT_DTE PROC
    CALL GET_DATE

    PUSH DX
   
    CMP DH, 1
    JE IS_JAN

    CMP DH, 2
    JE IS_FEB

    CMP DH, 3
    JE IS_MAR

    CMP DH, 4
    JE IS_APR

    CMP DH, 5
    JE IS_MAY

    CMP DH, 6
    JE IS_JUN

    CMP DH, 7
    JE IS_JUL

    CMP DH, 8
    JE IS_AUG

    CMP DH, 9
    JE IS_SEP

    CMP DH, 10
    JE IS_OCT

    CMP DH, 11
    JE IS_NOV

    CMP DH, 12
    JE IS_DEC

    IS_JAN:
        LEA DX, JAN
		MOV AH, 09H
		INT 21H
        JMP YEAR
    IS_FEB:
        LEA DX, FEB
		MOV AH, 09H
		INT 21H
        JMP YEAR
    IS_MAR:
        LEA DX, MAR
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_APR:
        LEA DX, APR
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_MAY:
        LEA DX, MAY
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_JUN:
        LEA DX, JUN
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_JUL:
        LEA DX, JUL
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_AUG: 
        LEA DX, AUG
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_SEP:
        LEA DX, SEP
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_OCT:
        LEA DX, OCT
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_NOV: 
        LEA DX, NOV
        MOV AH, 09H
        INT 21H
        JMP YEAR
    IS_DEC: 
        LEA DX, DECE
        MOV AH, 09H
        INT 21H
        JMP YEAR

    YEAR:
        MOV dl, ' '     ; To print /
        MOV ah, 02h
        INT 21h

        POP DX
        MOV al, dl      ; day in dl
        CALL DISP_DT

        MOV dl, ','     ; To print /
        MOV ah, 02h
        INT 21h

        MOV dl, ' '     ; To print /
        MOV ah, 02h
        INT 21h

        MOV dl, '2'     ; To print /
        MOV ah, 02h
        INT 21h

        MOV dl, '0'     ; To print /
        MOV ah, 02h
        INT 21h

        ADD cx, 0F830h  ; To negate the effects of 16bit value,
        MOV ax, cx      ; year in ax 
        CALL DISP_DT       ; call disp procedure to display year
    RET
PRNT_DTE ENDP

PRNT_DOW PROC
    CALL GET_DATE

    CMP AL, 0
    JE IS_SUN

    CMP AL, 1
    JE IS_MON

    CMP AL, 2
    JE IS_TUE

    CMP AL, 3
    JE IS_WED

    CMP AL, 4
    JE IS_THU

    CMP AL, 5
    JE IS_FRI

    CMP AL, 6
    JE IS_SAT

    IS_SUN:
        LEA DX, SUN
        MOV AH, 09H
        INT 21H
        RET
    
    IS_MON:
        LEA DX, MON
        MOV AH, 09H
        INT 21H
        RET

    IS_TUE:
        LEA DX, TUE
        MOV AH, 09H
        INT 21H
        RET

    IS_WED:
        LEA DX, WED
        MOV AH, 09H
        INT 21H
        RET

    IS_THU:
        LEA DX, THU
        MOV AH, 09H
        INT 21H
        RET

    IS_FRI:
        LEA DX, FRI
        MOV AH, 09H
        INT 21H
        RET

    IS_SAT:
        LEA DX, SAT
        MOV AH, 09H
        INT 21H
        RET
PRNT_DOW ENDP

DEC_EQV PROC
    AAM
    MOV BX, AX
    ADD BX, 3030H  
    RET
DEC_EQV ENDP

DISP_DT PROC
    CALL DEC_EQV

    MOV DL, BH
    MOV AH, 02H
    INT 21H

    MOV DL, BL
    MOV AH, 02H
    INT 21H

    RET
DISP_DT ENDP

ADD_SEC PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    ADD DH, 1

    CMP DH, 60
    JGE ADD1
    RET
    ADD1:
        CALL ADD_MIN
        MOV DH, 0
        RET
ADD_SEC ENDP

ADD_MIN PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    ADD CL, 1
    CMP CL, 60
    JGE ADD2
    RET
    ADD2:
        CALL ADD_HR
        MOV CL, 0
        RET
    

ADD_MIN ENDP

ADD_HR PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    ADD CH, 1
    CMP CH, 24
    JGE ADD3
    RET
    ADD3:
        CALL ADD_DAY
        MOV CH, 0
        RET
ADD_HR ENDP
    
ADD_DAY PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    ADD BX,1
    RET
ADD_DAY ENDP

SUB_SEC PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    DEC DH
    CMP DH, 0
    JL SUB1
    RET
    SUB1:
        CALL SUB_MIN
        MOV DH, 59
        RET

SUB_SEC ENDP

SUB_MIN PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    DEC CL
    CMP CL, 0
    JL SUB2
    RET
    SUB2:
        CALL SUB_HR
        MOV CL, 59
        RET
SUB_MIN ENDP

SUB_HR PROC ; For timer
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    DEC CH
    CMP CH, 0
    JL SUB3
    RET
    SUB3:
        CALL SUB_DAY
        MOV CH, 23
        RET
SUB_HR ENDP

SUB_DAY PROC
    ; Input: BX = Days, CH = Hour, CL = Minute, DH = Second
    DEC BX
    RET
SUB_DAY ENDP
