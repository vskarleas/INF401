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
     
     push {r0}
     push {r1}
     push {r2}
     push {r3}
     push {r4}
     push {r5}
     push {r6}
     push {r7}

     ldr r0, [fp, #20] @tab1
     ldr r1, [fp, #16] @NMAX
     ldr r2, [fp, #12] @tab2
     ldr r6, [fp, #8] @fonction f
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
     pop {r7}
     pop {r6}
     pop {r5}
     pop {r4}
     pop {r3}
     pop {r2}
     pop {r1}
     pop {r0}
     
     pop {fp}
     pop {lr}
     bx lr

     