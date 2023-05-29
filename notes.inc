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
    MOV     AX, 1809        ;Frequency for MI
    MOV     STOR, AX
    CALL    SOUNDER         
    RET
NTE_MI ENDP

NTE_FA PROC
    MOV     AX, 1715         ;Frequency for FA
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_FA ENDP
                    
NTE_SO PROC
    MOV     AX, 1521        ;Frequency for SO
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_SO ENDP

NTE_LA PROC
    MOV     AX, 1355        ;Frequency for LA
    MOV     STOR, AX
    CALL    SOUNDER        
    RET
NTE_LA ENDP
                    
NTE_TI PROC
    MOV     AX, 1207        ;Frequency for TI
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