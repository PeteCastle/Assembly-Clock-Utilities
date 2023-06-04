.DATA
	 TLRM1 DB 13,10,"                     :7Y!         .JJ.         !Y7:                         ", "$"                
     TLRM2 DB 13,10,"                   .!YJ~. ::      .YY.      :: .~JY!.                       ", "$"             
     TLRM3 DB 13,10,"                  :JY!  ~JY7   :~!7YY7!~:   7YJ~  !YJ:                      ", "$"            
     TLRM4 DB 13,10,"                 :JY^ .?Y7: :!JJ?!~~~~!?JJ!: :7Y?. ^YJ:                     ", "$"  
     TLRM5 DB 13,10,"                .?Y~ .?Y!  !YJ~.        .~JY!  !Y?. ~Y?.                    ", "$" 
     TLRM6 DB 13,10,"                !Y?  7Y7  7Y7              7Y7  7Y7  ?Y!                    ", "$" 
     TLRM7 DB 13,10,"                ?Y~ .JJ: ^Y?.              .?Y^ :JJ. ~Y?                    ", "$" 
     TLRM8 DB 13,10,"                !?: .77. ~J7                7J~ .77. :?!                    ", "$" 
     TLRM9 DB 13,10,"                         ~J7                7J~                             ", "$" 
    TLRM10 DB 13,10,"                         ~J7                7J~                             ", "$" 
    TLRM11 DB 13,10,"                         ~J7                7J~                             ", "$" 
    TLRM12 DB 13,10,"                         !J!                !J!                             ", "$" 
    TLRM13 DB 13,10,"                        .?J^                ^J?                             ", "$" 
    TLRM14 DB 13,10,"                       !J7                  7J!                             ", "$" 
    TLRM15 DB 13,10,"                      !?7.                  .7?!                            ", "$" 
    TLRM16 DB 13,10,"                    ^7??^:^^^^^:::^^:::^^^^^:^??7^                          ", "$"
    TLRM17 DB 13,10,"                   .!!!!!!!!!!!7??!!??7!!!!!!!!!!!.                         ", "$" 
    TLRM18 DB 13,10,"                               ^?7..7?^                                     ", "$"
    TLRM19 DB 13,10,"                                ^7??7^                                      ", "$"
    TLRM20 DB 13,10,13,10,"                    _   _     _   ___ _   _  _  _  _  __ ||||               ", "$"
    TLRM21 DB 13,10,"                   / \ | |   / \ | o \ \_/ || || \| |/ _|L|L|               ", "$"
    TLRM22 DB 13,10,"                  | o || |_ | o ||   / \_/ || || \\ ( |_n                   ", "$"
    TLRM23 DB 13,10,"                  |_n_||___||_n_||_|\\_| |_||_||_|\_|\__/()()               ", "$"



.code

    CALL RST_CRSR
    CALL CLRSCR
    CALL COLOR
    CALL TLRM_GUI




    TLRM_GUI PROC ;Timer Gui
    LEA DX, TMR1
    MOV AH, 09H
    INT 21H

    LEA DX, TMR2
    MOV AH, 09H
    INT 21H

    LEA DX, TMR3
    MOV AH, 09H
    INT 21H

    LEA DX, TMR4
    MOV AH, 09H
    INT 21H

    LEA DX, TMR5
    MOV AH, 09H
    INT 21H

    LEA DX, TMR6
    MOV AH, 09H
    INT 21H

    LEA DX, TMR7
    MOV AH, 09H
    INT 21H

    LEA DX, TMR8
    MOV AH, 09H
    INT 21H

    LEA DX, TMR9
    MOV AH, 09H
    INT 21H

    LEA DX, TMR10
    MOV AH, 09H
    INT 21H

    LEA DX, TMR11
    MOV AH, 09H
    INT 21H

    LEA DX, TMR12
    MOV AH, 09H
    INT 21H

    LEA DX, TMR13
    MOV AH, 09H
    INT 21H

    LEA DX, TMR14
    MOV AH, 09H
    INT 21H

    LEA DX, TMR15
    MOV AH, 09H
    INT 21H

    LEA DX, TMR22
    MOV AH, 09H
    INT 21H

    LEA DX, TMR16
    MOV AH, 09H
    INT 21H

    LEA DX, TMR17
    MOV AH, 09H
    INT 21H

    LEA DX, LINE1
    MOV AH, 09H
    INT 21H

    LEA DX, TMR18
    MOV AH, 09H
    INT 21H

    LEA DX, TMR19
    MOV AH, 09H
    INT 21H

    LEA DX, TMR20
    MOV AH, 09H
    INT 21H

    LEA DX, TMR21
    MOV AH, 09H
    INT 21H

    RET

TLRM_GUI ENDP
    