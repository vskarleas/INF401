@ essai-fact0rec.s
         .data
n:       .word    0              @ donnee
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

         @ appel de la fonction fact0rec(n)
         @@@@@@@@@@@@@
         @ A COMPLETER
         @@@@@@@@@@@@@

         @ afficher n!
         bl       EcrNdecimal32

         @ fin de la procedure principale
         bal      exit

@ adresses pour l'acces en zone data
adr_n:
         .word    n
adr_invite:
         .word    invite
