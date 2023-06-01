.DATA
    HK_Q DB " Q ","$"
    HK_W DB " W ","$"
    HK_E DB " E ","$"
    HK_R DB " R ","$"
    HK_T DB " T ","$"
    HK_Y DB "[Y]","$"
    HK_A DB "[A]","$"
    HK_S DB "[S]","$"
    HK_D DB "[D]","$"
    HK_F DB "[F]","$"
    HK_G DB "[G]","$"
    HK_H DB "[H]","$"
    HK_J DB "[J]","$"
    HK_Z DB "[Z]","$"
    HK_X DB "[X]","$"
    HK_C DB "[C]","$"
    HK_V DB "[V]","$"
    HK_K DB "[B]","$"
    HK_L DB "[L]","$"
    HK_M DB "[M]","$"
    HK_U DB "[U]","$"
    HK_P DB "[P]","$"
    HK_SE DB  "[SPACE]","$"
    HK_CA DB "[,]","$"
    HK_DT DB "[.]","$"
    HK_SN DB "[;]","$"
    HK_SH DB "[/]","$"
    HK_AE DB "[']","$"
    HK_RSB DB "]","$"
    ; HK_LSB "[","$"
    HK_BL DB "\","$"

; .CODE
;     MENU_HKY PROC
;     PUSH DS
; 	POP ES
; 	MOV AL, 1
; 	MOV BH, 0
; 	MOV BL, 00001110b
; 	MOV DL, 7
; 	MOV DH, 22	
;     MOV BP, offset HK_Q
; 	INT 10H

; 	MOV DL, 22
; 	MOV DH, 22	
;     MOV BP, offset HK_W
; 	INT 10H

; 	MOV DL, 38
; 	MOV DH, 22	
;     MOV BP, offset HK_E
; 	INT 10H

; 	MOV DL, 54
; 	MOV DH, 22	
;     MOV BP, offset HK_R
; 	INT 10H

; 	MOV DL, 68
; 	MOV DH, 22	
;     MOV BP, offset HK_T
; 	INT 10H
; 	RET
;     MENU_HKY ENDP