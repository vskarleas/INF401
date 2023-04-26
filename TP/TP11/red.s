@ fonction red
@ parametres : A COMPLETER
@ algorithme : A COMPLETER
@ allocation des registres : A COMPLETER

         .text
         .global  red
red:
    push {lr}
    mov r5, #0
    mov r4, r2 @acc <- vi (valeur initiale)

cond:
    cmp r5, r1
    beq fincond
    push {r0}
    push {r1}
    push {r2}

    ldrb r1, [r0, r5]
    mov r0, r4
    blx r3

    mov r4, r2
    pop {r2}
    pop {r1}
    pop {r0}
    add r5, r5, #1
    b cond
    

fincond:

    pop {lr}
    bx lr
