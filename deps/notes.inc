;Standard 1st Octave Notes
NTE_DO PROC
    MOV     AX, 2280        ;Frequency for DO
    MOV     STOR, AX
    CALL    SOUNDER         
    RET  
NTE_DO ENDP
           

           
NTE_RE PROC
    MOV     AX, 2031        ;Frequency for RE
    MOV     STOR, AX
    CALL    SOUNDER         
    RET
NTE_RE ENDP
                    
NTE_MI PROC
    MOV     AX, 1810        ;Frequency for MI
    MOV     STOR, AX
    CALL    SOUNDER         
    RET
NTE_MI ENDP

NTE_FA PROC
    MOV     AX, 1710         ;Frequency for FA
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_FA ENDP
                    
NTE_SO PROC
    MOV     AX, 1525        ;Frequency for SO
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_SO ENDP

NTE_LA PROC
    MOV     AX, 1360        ;Frequency for LA
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_LA ENDP
                    
NTE_TI PROC
    MOV     AX, 1210        ;Frequency for TI
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_TI ENDP   

;Standard 2nd Octave Notes
NTE_DO2 PROC
    MOV     AX, 1140        ;Frequency for DO (2nd octave)
    MOV     STOR, AX
    CALL    SOUNDER         
    RET
NTE_DO2 ENDP

NTE_RE2 PROC
    MOV     AX, 1015        ;Frequency for RE (2nd octave)
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_RE2 ENDP
                
NTE_MI2 PROC
    MOV     AX, 0905        ;Frequency for MI (2nd octave)
    MOV     STOR, AX
    CALL    SOUNDER       
    RET
NTE_MI2 ENDP

NTE_FA2 PROC
    MOV     AX, 0855 ;FREQUENCY FOR FA (2ND OCTAVE)
    MOV     STOR, AX 
    CALL    SOUNDER       
    RET
NTE_FA2 ENDP

NTE_SO2 PROC
    MOV     AX, 0763  ;FREQUENCY FOR SO (2ND OCTAVE)
    MOV     STOR, AX
    CALL    SOUNDER       
    RET
NTE_SO2 ENDP

NTE_LA2 PROC
    MOV     AX, 0680    ;FREQUENCY FOR LA (2ND OCTAVE)
    MOV     STOR, AX
    CALL    SOUNDER       
    RET
NTE_LA2 ENDP

NTE_TI2 PROC
    MOV     AX, 0605    ;FREQUENCY FOR TI (2ND OCTAVE)
    MOV     STOR, AX
    CALL    SOUNDER       
    RET
NTE_TI2 ENDP

;Sharp Keys
NTE_DOS PROC
    MOV     AX, 2152        ;Frequency for DO# (1st octave)
    MOV     STOR, AX
    CALL    SOUNDER         
    RET
NTE_DOS ENDP                    

NTE_RES PROC
    MOV     AX, 1917        ;Frequency for RE# (1st octave)
    MOV     STOR, AX
    CALL    SOUNDER         
    RET
NTE_RES ENDP

NTE_FAS PROC
    MOV     AX, 1612         ;Frequency for FA# (1st octave)
    MOV     STOR, AX
    CALL    SOUNDER         
    RET   
NTE_FAS ENDP

NTE_SOS PROC
    MOV     AX, 1436         ;Frequency for SO# (1st octave)
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_SOS ENDP

NTE_LAS PROC
    MOV     AX, 1292         ;Frequency for LA# (1st octave)
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_LAS ENDP
            
NTE_DO2S PROC
    MOV     AX, 1076         ;Frequency for DO# (2nd octave)
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_DO2S ENDP

NTE_RE2S PROC
    MOV     AX, 0958         ;Frequency for RE# (2nd octave)
    MOV     STOR, AX
    CALL    SOUNDER         
    RET       
NTE_RE2S ENDP    