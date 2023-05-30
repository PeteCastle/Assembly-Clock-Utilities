.MODEL SMALL
.STACK 100H

.DATA
    MSB DW 0       ; Most significant byte of elapsed time
    LSB DW 0       ; Least significant byte of elapsed time
    START_TIME DW 0 ; Start time in milliseconds

.CODE
	start:
    MOV AX, @DATA
    MOV DS, AX

    MOV AL, 0B6H   ; Set PIT command register for Channel 0
    OUT 43H, AL    ; Write the command

    MOV CX, 0      ; Counter for delay

    ; Initialize the PIT for a 1 ms delay
    MOV AX, 1192   ; Load the initial count value (65536 - 1192 = 64344)
    OUT 40H, AL    ; Load least significant byte
    MOV AL, AH
    OUT 40H, AL    ; Load most significant byte

    ; Start the stopwatch
    MOV AL, 20H    ; Enable PIT Channel 0
    OUT 61H, AL    ; Start the PIT

    MOV AH, 0      ; Clear high byte of AX
    MOV CX, 1000   ; Set the delay counter to 1000 (1 second)

DELAY_LOOP:
    NOP            ; Delay loop
    LOOP DELAY_LOOP

    ; Read the elapsed time
    IN AL, 40H     ; Read least significant byte
    MOV AH, AL
    IN AL, 40H     ; Read most significant byte

    MOV BL, AL     ; Store most significant byte in BL
    SUB AL, 20H    ; Subtract the initial count value
    MOV CL, AL     ; Store least significant byte in CL
    SBB BL, AH     ; Subtract the carry from most significant byte

    ; Store the elapsed time in MSB and LSB
    MOV word ptr [MSB], BX
    MOV word ptr [LSB], CX

    ; Display the elapsed time
    MOV AH, 02H    ; Function to display character
    MOV DL, ' '    ; Display space
    INT 21H

    MOV AH, 09H    ; Function to display string
    LEA DX, START_TIME_MSG
    INT 21H

    MOV AX, word ptr [MSB]  ; Display most significant byte of elapsed time
    CALL DISPLAY_HEX

    MOV AX, word ptr [LSB]  ; Display least significant byte of elapsed time
    CALL DISPLAY_HEX

    MOV DL, ' '    ; Display space
    MOV AH, 02H    ; Function to display character
    INT 21H

    MOV AH, 09H    ; Function to display string
    LEA DX, MS_MSG
    INT 21H

    MOV DL, ' '    ; Display space
    MOV AH, 02H    ; Function to display character
    INT 21H

    MOV AH, 09H    ; Function to display string
    LEA DX, LS_MSG
    INT 21H

    MOV AH, 4CH    ; Terminate program
    INT 21H

; Procedure to display a hexadecimal value
DISPLAY_HEX PROC
    PUSH AX        ; Save registers
    PUSH BX
    PUSH CX
    PUSH DX

    MOV BX, 10     ; Divide by 10 to convert to decimal
    XOR CX, CX     ; Clear the quotient
    MOV AX, 0      ; Clear the remainder
    DIV BX         ; Divide AX by BX
    ADD DL, '0'    ; Convert the remainder to ASCII

    PUSH DX        ; Save the first digit

    MOV AH, 02H    ; Function to display character
    INT 21H        ; Display the first digit

    POP DX         ; Restore the first digit

    MOV DL, AH     ; Move the quotient to DL
    ADD DL, '0'    ; Convert the quotient to ASCII

    MOV AH, 02H    ; Function to display character
    INT 21H        ; Display the second digit

    POP DX         ; Restore registers
    POP CX
    POP BX
    POP AX

    RET
DISPLAY_HEX ENDP

; Strings
START_TIME_MSG DB 'Start Time:', 13, 10, '$'
MS_MSG DB 'Elapsed Time (MSB):', 13, 10, '$'
LS_MSG DB 'Elapsed Time (LSB):', 13, 10, '$'

END start
