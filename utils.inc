 CURS_OFF PROC ;NEAR
    MOV     CH, 10h         ;Hides cursor
    MOV     AH, 01H         ;Interrupt for set text-mode sursor shape
    INT     10h             
    RET
CURS_OFF ENDP

CURS_ON PROC ;NEAR 
    MOV     CX, 0506h       ;Show cursor
    MOV     AH, 01H         ;Interrupt for set text-mode sursor shape
    INT     10H             
    RET
CURS_ON ENDP

DELAY PROC
    MOV     AH, 00H         
    INT     01AH            ;Get system time
    ADD     DX,  4          ;Delay amount (in loops)
    MOV     BX, DX          ;Stores the DX (clock ticks since 12AM) to BX

    PZ:
        INT     01AH            ;Get system time (again)
        CMP     DX, BX          ;Compare the current time with the time stored in BX
        JL      PZ              ;Jumps to PZ if DX is less than BX
        ; Note that since delay is 4, it would take 4 loops before this procedure ends.
    RET
DELAY ENDP

DELAY_1SC PROC

    mov     cx, 0fh
    mov     dx, 4240h
    mov     ah, 86h
    int     15h
    RET
DELAY_1SC ENDP

; sets up the keyboard buffer by initializing the head and tail pointers to the appropriate values, allowing the system to track keyboard input.
CLR_KEYB PROC ;NEAR
    PUSH    ES                      ; Save ES
    PUSH    DI                      ; Save DI
    MOV     AX, 40H                 ; Load BIOS segment into AX
    MOV     ES, AX                  ; Transfer to ES
    MOV     AX, 1AH                 ; Load keyboard pointer into AX
    MOV     DI, AX                  ; Store in DI
    MOV     AX, 1EH                 ; Load keyboard buffer start into AX
    MOV     ES: WORD PTR [DI], AX   ; Move to the head pointer
    INC     DI                      ; Move pointer to the keyboard tail pointer
    INC     DI                      
    MOV     ES: WORD PTR [DI], AX   ; Move to the tail pointer
    POP     DI                      ; Restore DI
    POP     ES                      ; Restore ES
    RET                             ; Return from the procedure
CLR_KEYB ENDP

; controlling the PC speaker to generate a sound of a specific frequency
SOUNDER PROC ;NEAR
    MOV     AL, 0B6H        ;Load control value into AL
    OUT     43H, AL         ;Send control value to port 43H
    MOV     AX, STOR        ;Load frequency value into AX
    OUT     42H, AL         ;Send LSB of frequency to port 42H
    MOV     AL, AH          ;Move MSB of frequency to AL
    OUT     42H, AL         ;Send MSB of frequency to port 42H
    IN      AL, 061H        ;Read the state of port 61H
    OR      AL, 03H         ;Turn on the speaker by setting the appropriate bits
    OUT     61H, AL         ;Turn on the speaker by sending the updated state to port 61H
    CALL    DELAY           ;Delay for a certain period of time
    AND     AL, 0FCH        ;Turn off the speaker by clearing the appropriate bits
    OUT     61H, AL         ;Turn off the speaker by sending the updated state to port 61H
    CALL    CLR_KEYB        ;Call the function to clear the keyboard buffer
    RET
SOUNDER ENDP

CLRSCR PROC
    MOV AH, 06h ; Scroll up window
    MOV AL, 00h ; Clears entire window
    MOV BH, 07h
    MOV CX, 0     ; Top left corner of the screen
    MOV DX, 184Fh ; Bottom right corner of the screen
    
    INT 10h       ; Call BIOS interrupt to clear the screen
    
    RET
CLRSCR ENDP

COLOR proc
    MOV AH, 06h    ; Scroll up function
    XOR AL, AL     ; Clear entire screen
    XOR CX, CX     ; Upper left corner CH=row, CL=column
    MOV DX, 184FH  ; lower right corner DH=row, DL=column 
    MOV BH, 74H   ; white and red
    INT 10H
    ret
COLOR endp

COL_RED PROC ; Red Text Only

COL_RED ENDP

GETKIN PROC ;Get Key Input ( blocking; synchronous) -> Stores input in INPUT variable (AL)
    MOV AH, 08H         ;Interrupt for get keyboard input
    MOV INPUT, AL
    INT 21H
    ret
GETKIN ENDP

GETKINAS PROC
    ;Get Key input (non blocking; asynchronous)
    ; INT 16h / AH = 01h - check for keystroke in the keyboard buffer.
        ; return:
        ; ZF = 1 if keystroke is not available.
        ; ZF = 0 if keystroke available.
        ; AH = BIOS scan code.
        ; AL = ASCII character.
    MOV AH, 01H
    INT 16H
    ret
GETKINAS ENDP

ENDPROG PROC
    ; MOV AH, 08H
    INT 20H
    RET
ENDPROG ENDP

RST_CRSR PROC
    ; Sets Cursor Position at (0,0)
	MOV AX, 0003h
	MOV BX, 0
	MOV DX, 0000h
	INT 10H
    RET
RST_CRSR ENDP

SET_CRSR PROC
    ; Sets Cursor Position at (X,Y)
    ; Required Args: DH = row, DL = column
    MOV AX, 0200h
    MOV BX, 0
    
    INT 10H
    RET
SET_CRSR ENDP