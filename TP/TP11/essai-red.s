         .set     NMAX, 10       @ nombre d'elements

         .data
invite1: .asciz   "Saisir une sequence de "
invite2: .asciz   " entiers :"
afftab:  .asciz   "Sequence donnee S :"
affres1: .asciz   "red(S, somme) = "
affres2: .asciz   "red(S, produit) = "
tab :    .skip    NMAX           @ tableau de NMAX octets
var_somme:   .word    0

         .text
         .global  main
@ procedure principale
main:
         push {lr}               @ sauvegarde adresse de retour
         @ saisir la sequence donnee
         ldr      r1, LD_invite1
         bl       EcrChn
         mov      r1, #NMAX
         bl       EcrNdecim32
         ldr      r1, LD_invite2
         bl       EcrChaine
         ldr      r0, LD_tab
         mov      r1, #NMAX
         bl       saisir_tab

         @ afficher la sequence donnee
         bl       AlaLigne
         ldr      r1, LD_afftab
         bl       EcrChaine
         mov      r1, #NMAX
         bl       afficher_tab

         @ appel de la fonction red(tab, NMAX, 0, somme)
         ldr r0, LD_tab
         mov r1, #NMAX
         mov r2, #0
         ldr r3, LD_somme

         bl red


         @ afficher le resultat
         bl       AlaLigne
         ldr      r1, LD_affres1
         bl       EcrChn

         mov r1, r4
         bl EcrZdecimal32

         @ appel de la fonction red(tab, NMAX, 1, produit)
         ldr r0, LD_tab
         mov r1, #NMAX
         mov r2, #1
         ldr r3, LD_produit

         bl red

         @ afficher le resultat (produit)
         bl       AlaLigne
         ldr      r1, LD_affres2
         bl       EcrChn

         mov r1, r4
         bl EcrZdecimal32

         @ fin du programme principal
         pop      {lr}           @ restauration adresse de retour
         bx       lr             @ retour a l'appelant

@ relais vers la zone data
LD_invite1:
         .word    invite1
LD_invite2:
         .word    invite2
LD_afftab:
         .word    afftab
LD_affres1:
         .word    affres1
LD_affres2:
         .word    affres2
LD_tab:
         .word    tab
LD_var_somme:
         .word    var_somme

@ relais vers la zone text
LD_somme:
	 .word    somme

LD_produit: 
     .word    produit
