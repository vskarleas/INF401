                                                                                        
@  Importation des,constantes symboliques WIDTH, HEIGHT, BYTES, BYTES_PER_LINE          
#include "image_bits_include.h"                                                       
                                                                                        
                 .global symetrie_octet                                                 
                 .global permuter_cols                                                  
                 .global symetrie_axe_v                                                 
                 .global permuter_ligne                                                 
                 .global symetrie_axe_h                                                 
                 .global symetrie_axe_h                                                 
                 .global permuter_lignes                                                
                 .global symetrie_axe_v                                                 
                                                                                        
                 .text                                                                  
                                                                                        
@ r0 : parametre reçu adresse                                                           
@ r1 : variable locale octet                                                            
                                                                                        
#ifndef C_SYMETRIE_OCTET                                                                
#ifndef SYMTAB                                                                          
                                                                                        
@  Version avec opérations bit à bit                                                    
                                                                                        
symetrie_octet:  
    ldrb r1, [r0]
    mov r3, r1
    and r1, r1, #0xF0
    mov r1, r1, lsr #4
    and r2, r3, #0x0F
    mov r2, r2, lsl #4
    orr r1, r1, r2

    mov r3, r1
    and r1, r1, #0xCC
    mov r1, r1, lsr #2
    and r2, r3, #0x33
    mov r2, r2, lsl #2
    orr r1, r1, r2

    mov r3, r1
    and r1, r1, #0xAA
    mov r1, r1, lsr #1
    and r2, r3, #0x55
    mov r2, r2, lsl #1
    orr r1, r1, r2

    strb r1, [r0]

    bx lr
                                                                           
                                                                                        
#else  // SYMTAB                                                                        
                                                                                        
@ Version tabulée                                                                       
symetrie_octet:   
    ldrb r1, [r0]
    ldr r2, addr_tableau
    ldrb r1, [r2]
    @to be continued


    bx lr


#endif  // SYMTAB                                                                       
#endif  // C_SYMETRIE_OCTET                                                             
@ r0 : parametre tab                                                                    
@ r1 : parametre col                                                                    
                                                                                        
#ifndef C_PERMUTER_COLS                                                                 
 
permuter_cols:  
    ldr r2, adr_butes_per_ligne
    sub r2, r2, #1
    sub r2, r2, r1
    add r5, r2, r0
    ldrb r3, [r5]
    
    add r4, r1, r0
    ldrb r6, [r4]

    strb r6, [r2]
    strb r3, [r4]

    bx lr
#endif // C_PERMUTER_COLS                                                               
                                                                                        
@ r0 : parametre image                                                                    
@ r1 : position
@ r2: ligne
@ r3: colonne
@ r4: addresse    
@ r5: BYTES
@ r6: BYTES_PER_LIGNE
@ r7 : HEIGHT                                                                
                                                                                        
#ifndef C_SYMETRIE_AXE_V                                                                
symetrie_axe_v: 
    mov r8, r0

    ldr r5, adr_bytes
    ldr r6, adr_butes_per_ligne
    ldr r7, adr_height
    mov r1, #0              
for:
    cmp r1, r5
    bge endfor
    add r0, r8, r1

    mov r0, r1
    bl symetrie_octet

    add r1, r1, #1
    b for
endfor:
    mov r2, #0
for2:
    cmp r2, r7
    bge endfor2

    mul r10, r2, r6
    add r4, r10, r8

    mov r3, #0
    mov r9, r6, lsr #2
boucle:
    cmp r3, r9
    bge finboucle

    push {r0}
    push {r1}

    mov r0, r4
    mov r1, r3


    bl permuter_cols

    pop {r1}
    pop {r0}

    add r3, r3, #1
    b boucle

finboucle:

    add r2, r2, #1
    b for2
endfor2:
    bx lr


                                                                                        
#endif // C_SYMETRIE_AXE_V                                                              
@ r0 : tab                                                                              
@ r1 : li                                                                               
                                                                                        
#ifndef C_PERMUTER_LIGNES                                                               
permuter_lignes: 
                                                                          
                                                                                        
#endif // C_PERMUTER_LIGNES                                                             
                                                                                        
@ r0 : paramètre image                                                                  
                                                                                        
#ifndef  C_SYMETRIE_AXE_H                                                               
symetrie_axe_h:                                                                         
                                                                                        
#endif   // C_SYMETRIE_AXE_H                                                            

addr_tableau : .word tabsym_octet
adr_butes_per_ligne: .word BYTES_PER_LINE
adr_bytes: .word BYTES
adr_height: .word HEIGHT