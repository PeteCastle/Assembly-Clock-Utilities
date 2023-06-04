.DATA
	 TTTMR DB 13,10,13,10,"                     :7Y!         .JJ.         !Y7:                         ", "$"                
     TTMR2 DB 13,10,"                   .!YJ~. ::      .YY.      :: .~JY!.                       ", "$"             
     TTMR3 DB 13,10,"                  :JY!  ~JY7   :~!7YY7!~:   7YJ~  !YJ:                      ", "$"            
     TTMR4 DB 13,10,"                 :JY^ .?Y7: :!JJ?!~~~~!?JJ!: :7Y?. ^YJ:                     ", "$"  
     TTMR5 DB 13,10,"                .?Y~ .?Y!  !YJ~.        .~JY!  !Y?. ~Y?.                    ", "$" 
     TTMR6 DB 13,10,"                !Y?  7Y7  7Y7              7Y7  7Y7  ?Y!                    ", "$" 
     TTMR7 DB 13,10,"                ?Y~ .JJ: ^Y?.              .?Y^ :JJ. ~Y?                    ", "$" 
     TTMR8 DB 13,10,"                !?: .77. ~J7                7J~ .77. :?!                    ", "$" 
     TTMR9 DB 13,10,"                         ~J7                7J~                             ", "$" 
    TTMR10 DB 13,10,"                         ~J7                7J~                             ", "$" 
    TTMR11 DB 13,10,"                         ~J7                7J~                             ", "$" 
    TTMR12 DB 13,10,"                         !J!                !J!                             ", "$" 
    TTMR13 DB 13,10,"                        .?J^                ^J?                             ", "$" 
    TTMR14 DB 13,10,"                       !J7                  7J!                             ", "$" 
    TTMR15 DB 13,10,"                      !?7.                  .7?!                            ", "$" 
    TTMR16 DB 13,10,"                    ^7??^:^^^^^:::^^:::^^^^^:^??7^                          ", "$"
    TTMR17 DB 13,10,"                   .!!!!!!!!!!!7??!!??7!!!!!!!!!!!.                         ", "$" 
    TTMR18 DB 13,10,"                               ^?7..7?^                                     ", "$"
    TTMR19 DB 13,10,"                                ^7??7^                                      ", "$"
    TTMR20 DB 13,10,13,10,"                _____ ___ __  __ ___ _ ___   _   _ ___ _ _                  ", "$"
    TTMR21 DB 13,10,"               |_   _|_ _|  \/  | __( / __| | | | | _ | | |                 ", "$"
    TTMR22 DB 13,10,"                 | |  | || |\/| | _||/\__ \ | |_| |  _|_|_|                 ", "$"
    TTMR23 DB 13,10,"                 |_| |___|_|  |_|___| |___/  \___/|_| (_(_)                 ", "$"



.code

    CALL RST_CRSR
    CALL CLRSCR
    CALL COLOR
    CALL TTMR_GUI




    TTMR_GUI PROC ;Timer Gui
    LEA DX, TTMR1
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR2
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR3
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR4
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR5
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR6
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR7
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR8
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR9
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR10
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR11
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR12
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR13
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR14
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR15
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR16
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR17
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR18
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR19
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR20
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR21
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR22
    MOV AH, 09H
    INT 21H

    LEA DX, TTMR23
    MOV AH, 09H
    INT 21H

    RET

TTMR_GUI ENDP
    