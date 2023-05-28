;Deklarasi Model Program yang Digunakan
.MODEL SMALL

;Inisialisasi Stack yang akan digunakan
.STACK 100H

.DATA
;Segment Data
    ;DEKLARASI JUDUL
    
    TIT1 db 13,10, 13, 10, 13,10 , 13,10, 13, 10, 13, 10, 13, 10,      '              ___   _____  _   _       ______ _'                             , 13, 10, '$'                  
    TIT2 db                                                            '             / _ \ /  ___|| | | |      | ___ (_)'                            , '$'
    TIT3 db 13,10,                                                     '            / /_\ \\ `--. | | | |_ __  | |_/ /_  __ _ _ __   ___'            , '$'                   
    TIT4 db 13,10,                                                     '            |  _  | `--. \| | | |  __| |  __/| |/ _  |  _ \ / _ \'           , '$'                     
    TIT5 db 13,10,                                                     '            | | | |/\__/ /\ \_/ / |    | |   | | (_| | | | | (_) |'          , '$'                   
    TIT6 db 13,10,                                                     '            \_| |_/\____/  \___/|_|    \_|   |_|\__,_|_| |_|\___/'           , '$'                     
    TIT7 db 13,10,13, 10, 13, 10,                                      '                     Virtual Piano ASCII BASED Graphic            '           , '$'                     
    TIT8 db 13,10,13, 10, 13, 10,                                      '                       Press any Key to continue....            '            , '$'                     
     
    ;MAIN INTERFACE 
    
    PIN1 db 13,10, 13, 10, 13,10 , 13,10, 13, 10, 13, 10,              '           _________________________________________________________'                             , 13, 10, '$'                  
    PIN2 db                                                            '           X+++++++++++++++++++++++++++++++++++++++++++++++++++++++X'                            , '$'
    PIN3 db 13,10,                                                     '           X       |  | | | |  |  | | | | | |  |  | | | |  |       X'            , '$'                   
    PIN4 db 13,10,                                                     '           X       |  | | | |  |  | | | | | |  |  | | | |  |       X'           , '$'                     
    PIN5 db 13,10,                                                     '           X       |  |2| |3|  |  |5| |6| |7|  |  |9| |0|  |       X'          , '$'                   
    PIN6 db 13,10,                                                     '           X       |  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |       X'           , '$'                     
    PIN7 db 13,10,                                                     '           X       |   |   |   |   |   |   |   |   |   |   |       X'           , '$'                     
    PIN8 db 13,10,                                                     '           X       | q | w | e | r | t | y | u | i | o | p |       X'            , '$'
    PIN9 db 13,10,                                                     '           X       |___|___|___|___|___|___|___|___|___|___|       X'           , '$'                     
    PIN0 db 13,10,                                                     '           X                                                       X'           , '$'                     
    PINA db 13,10,                                                     '           XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'            , '$'
    PINB db 13,10,13,10,13,10,                                         '                                Press v to EXIT'                              , '$'                                                                                       
   
    ;EXIT INTERFACE
    
    EXT1 db 13,10, 13, 10, 13,10 , 13,10, 13, 10,                      '                              ENVERIESAGE STUDIOS'                             , 13, 10, '$'                  
    EXT2 db 13,10,                                                     '                                     @2019'                            , '$'
    EXT3 db 13,10,                                                     '                        __________________________________'            , '$'                   
    EXT4 db 13,10,                                                     '                       /    o   oooo ooo oooo   o o o    /\       '           , '$'                     
    EXT5 db 13,10,                                                     '                      /    oo  ooo  oo  oooo   o o o    / /       '          , '$'                   
    EXT6 db 13,10,                                                     '                     /    _________________________    / /         '           , '$'                     
    EXT7 db 13,10,                                                     '                    / // / // /// // /// // /// / /   / /       '           , '$'                     
    EXT8 db 13,10,                                                     '                   /___ //////////////////////////___/ /       '            , '$'
    EXT9 db 13,10,                                                     '                   \____\________________________\___\/       '           , '$'                     
    EXTB db 13,10,13,10,13,10,                                         '                        Press any Key to continue....'                              , '$'                                                                                       
    
    ;Input Variable                                        
    INPUT   DB 128 (?)                                                
    PETUN   DB 'A = DO; S = MI; D = SOL; >> 0 UNTUK KELUAR' ,13,10, '$'
    STOR    DW 0        ;MEMORY                   
                                                      
    
.CODE

.STARTUP 
    mov al, 1
	mov bh, 0
	mov bl, 00111011b
	mov cx, msg1end - offset msg1 ; calculate message size. 
	mov dl, 10
	mov dh, 7
	push cs
	pop es
	mov bp, offset msg1
	mov ah, 13h
	int 10h
	jmp msg1end
	msg1 db " hello, world! "
	msg1end:
   .EXIT
END