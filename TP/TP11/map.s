@ procedure map
@ parametres :
@ algorithme :

@ allocation des registres :

         .text
         .global  map
map: 
     push {lr}
     mov r6, r3
     mov r8, r0
init_boucle : mov r5, #0
tq : cmp r5, r1
     beq fintq
     ldrb r3, [r8, r5] @t1[i] -> valeur
     blx r6
     strb r4, [r2, r5] @t2[i] 
     add r5, r5, #1
     b tq
fintq : 
    pop {lr}
    bx lr

     