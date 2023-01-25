@ essai-fact1rec.s
         .data
n:       .word    0              @ donnee
facn:    .word    0              @ resultat
invite:  .asciz   "Saisir un entier >= 0 :"

         .text
         .global  main
@ procedure principale
main:
         @ saisir n
         ldr      r1, adr_invite
         bl       EcrChaine
         ldr      r1, adr_n
         bl       Lire32

         @ appel de la procedure fact1rec(n, facn)
         @@@@@@@@@@@@@
         @ A COMPLETER
         @@@@@@@@@@@@@

         @ afficher n!
         ldr      r1, [r1]
         bl       EcrNdecimal32

         @ fin de la procedure principale
         bal      exit

@ adresses pour l'acces en zone data
adr_n:
         .word    n
adr_facn:
         .word    facn
adr_invite:
         .word    invite
