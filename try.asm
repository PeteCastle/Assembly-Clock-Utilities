.model small
.stack 100h

.data
    soundFrequency dw 440          ; Frequency for sound (A4)
    backgroundColor dw 2          ; Background color (green and red)
    buttonClicked db 0            ; Flag to check if button is clicked
    currentTime db 8, 0, 8 dup ('$') ; Current time string

.code
    ; Entry point of the program
    start:
        mov ax, @data
        mov ds, ax

        ; Set video mode to 3 (text mode)
        mov ax, 0003h
        int 10h

        ; Clear the screen
        mov ax, 0600h
        mov bh, 0       ; Page number
        mov cx, 0       ; Starting column
        mov dx, 184fh   ; Ending column and row
        int 10h

        ; Set background color
        mov ah, 0Bh     ; Set background color function
        mov bh, 0       ; Page number
        mov bl, backgroundColor ; Color (green and red)
        int 10h

        ; Print initial time
        call printTime

        ; Set up interrupt for button click
        mov ax, 3511h   ; Mouse event interrupt
        mov bx, 0       ; Button click event
        mov cx, 0       ; Disable mouse
        int 33h

    mainLoop:
        ; Check for button click
        mov ax, 0000h   ; Function 0, check button status
        int 33h
        test bx, 01h    ; Check if left button is clicked
        jnz buttonClicked

        ; Update current time every second
        mov ah, 2ch     ; Get system time function
        int 21h
        cmp ch, 0       ; Check if seconds is zero
        jnz mainLoop    ; If not zero, continue waiting

        ; Play sound
        call playSound

        ; Print current time
        call printTime

        jmp mainLoop    ; Repeat the main loop

    buttonClicked:
        ; Your method trigger code here
        ; For example, print a string
        mov ah, 09h     ; Print string function
        lea dx, clickMessage    ; Message string
        int 21h

        jmp mainLoop    ; Return to the main loop

    printTime:
        ; Get current time
        mov ah, 2ch     ; Get system time function
        int 21h

        ; Convert hours, minutes, and seconds to ASCII characters
        add dl, 30h     ; Convert seconds to ASCII
        mov [currentTime + 6], dl
        mov dl, dh
        add dl, 30h     ; Convert minutes to ASCII
        mov [currentTime + 4], dl
        mov dl, ch
        add dl, 30h     ; Convert hours to ASCII
        mov [currentTime + 2], dl

        ; Print current time
        mov ah, 09h     ; Print string function
        lea dx, currentTime    ; Current time string
        int 21h

        ret

    playSound:
        ; Play sound
        mov al, 0B6h    ; Sound command
        mov bl, soundFrequency  ; Frequency (low byte)
        mov bh, soundFrequency  ; Frequency (high byte)
        mov cx, 1       ; Duration in ticks
        int 10h

        ret

    clickMessage db 'Button clicked!', 0

    end start