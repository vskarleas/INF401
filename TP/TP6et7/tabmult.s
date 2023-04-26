@ Programme tabmult : Affiche les tables de multiplication de de 1 a 10
N_MAX= 10
   .data
barre :  .byte '|'
         .byte 0
espace : .byte ' '
         .byte 0
tirets : .asciz "---"

debutTab:    .skip N_MAX*N_MAX*4   @ adresse du debut du tableau

   .text
   .global main
main: push {lr}

    @ remplissage du tableau
        @ a completer...

    @ affichage du tableau
        @ a completer...

fin: pop {lr}
     bx lr

ptr_debutTab : .word debutTab
adr_barre :    .word barre
adr_espace :   .word espace
adr_tirets :   .word tirets

        cmp r2, #N_MAX
        bgt finremplissage2
        mul r7, r0, r2
        strb r7,[r3]
        add r3, r3, #4
        add r2, r2, #1
        b remplissage2


    finremplissage2:
        add r0, r0, #1
        b remplissage1


    

    @ affichage du tableau
    affichage:
        mov r0, #0
    boucle1: 
        cmp r0, #N_MAX
        bge finboucle1
        mov r2, #0
        bl boucle2
        add r0,r0,#1
        b boucle1
    finboucle1: 
        b fin

    boucle2:
        cmp r2, #N_MAX
        bge finboucle2
        ldr r1, adr_barre
        ldrb r1,[r1]
        bl EcrCar
        ldr r3, ptr_debutTab
        mov r10, #4
        mul r8, r0, r10
        mov r7, #10
        mul r4, r8, r7 
        add r3, r3, r4
        mul r4, r2, r10
        add r3, r3, r4
        ldrb r4, [r3] @r4 c'est le registre pour mult
    si1:
        cmp r4, #100
        bge finsi
        ldr r1, adr_espace
        ldrb r1,[r1]
        bl EcrCar
    si2:
        cmp r4, #10
        bge finsi
        ldr r1, adr_espace
        ldrb r1,[r1]
        bl EcrCar
    finsi:
        mov r1, r4
        bl EcrNdecim32
        add r2, r2, #1
        b boucle2
    finboucle2:
        ldr r1, adr_barre
        ldrb r1,[r1]
        bl EcrCar
        bl AlaLigne
        mov r5, #0
    pour:
        cmp r5, #N_MAX
        beq finpour
        ldr r1, adr_barre
        ldrb r1,[r1]
        bl EcrCar
        ldr r1, adr_tirets
        bl EcrChn
        add r5, r5, #1
        b pour
    finpour:
        ldr r1, adr_barre
        ldrb r1,[r1]
        bl EcrCar
        bl AlaLigne
        add r0, r0, #1
        b boucle1

fin: pop {lr}
     bx lr

ptr_debutTab : .word debutTab
adr_barre :    .word barre
adr_espace :   .word espace
adr_tirets :   .word tirets
