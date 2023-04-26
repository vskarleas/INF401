                                                                                      
@  Importation des,constantes symboliques WIDTH, HEIGHT, BYTES, BYTES_PER_LINE        
#include "image_bits_include.h"                                                       
										      
                                                                                      
                 .text                                                                
                                                                                      
@ r0 : parametre octet                                                                
                                                                                      
#ifndef C_NEG_OCTET                                                                   
                 .global neg_octet                                                    
                                                                                      
neg_octet:                                                                            
    mvn r5, r4  
    b continue                                                                         
#endif // C_NEG_OCTET                                                                 
                                                                                      
#ifndef C_NEG_IMAGE                                                               
                 .global neg_image                                                    
@ r0 : parametre reçu image                                                           

           
                                                                                      
                                                                                      
neg_image:
    mov r1, #0
boucle: 
    cmp r1, #HEIGHT
    bgt finboucle
    mov r2, #0
    b boucle2
finboucle:
    b fin
boucle2:
    cmp r2, #BYTES_PER_LINE
    bgt finboucle2
    ldrb r4,[r0]
    b neg_octet
continue:
    strb r5,[r0]
    add r0, r0, #1
    add r2, r2, #1
    b boucle2
finboucle2:
    add r1, r1, #1
    b boucle
fin:   
    mov  pc,lr                                                      
                                                                                      
adr_bytes:	.word BYTES                                                           
#endif // C_NEG_IMAGE                                                                 
