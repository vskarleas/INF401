@ procedure map
@ parametres :
@ algorithme :

@ allocation des registres :

         .text
         .global  map
map: 
     push {lr}
     push {fp}
     mov fp, sp
     
     push {r0, r1, r2, r3, r4, r5, r6, r7}

     ldr r0, [fp, #8] @tab1
     ldr r1, [fp, #12] @NMAX
     ldr r2, [fp, #16] @tab2
     ldr r6, [fp, #20] @fonction f
init_boucle : 
     mov r7, #0
tq : 
     cmp r7, r1
     beq fintq
     ldrb r3, [r0, r7] @t1[i] -> valeur
     blx r6
     strb r4, [r2, r7] @t2[i] 
     add r7, r7, #1
     b tq
fintq : 
     pop {r7, r6, r5, r4, r3, r2, r1, r0}
     
     pop {fp}
     pop {lr}
     bx lr

     