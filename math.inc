.CODE
    INV_BIT PROC
        ; Inverts a specific bit from an input
        ; Args:
            ; AX - Input
            ; CX - Bit # to invert (0 = lowest bit; 7 = highest bit)
        MOV BX, 1
        SHL BX, CL
        XOR AX, BX
        RET
    INV_BIT ENDP

    READ_BIT PROC
        ; Reads a specific bit from an input
        ; Args:
            ; AX - Input
            ; CX - Bit # to read (0 = lowest bit; 7 = highest bit)
        ; Returns:
            ; AX - Bit value
        MOV BX, 1
        SHL BX, CL
        AND AX, BX
        SHR AX, CL
        RET
    READ_BIT ENDP