# Compte rendu TP3-4

##### *SIMON Noan, SKARLEAS Vasilis, TREHIN Gwendal*

## 3.1

1. On peut remarquer que les informations sont représentées en hexadécimale.
2. Sur chaque ligne sont représentés 32 octets.
3. 2 caractères en hexadécimale correspondent au code ascii de la traduction du compilateur.
   Par exemple, le 6c correspond au l qui est bien sa valeur en hexadécimal et 61 correspond au a
***
1fd78 00000000 **6c61**0100 ....**la**..
***
   
4. La chaîne de caractères est codée avec les codes ascii (écrit en hexa “626f 6e6a6f75 72”) et la fin de la chaîne est marquée par le caractère null (de code 00 - NUL) en code ASCII).

On change tous les entiers sur 32 bits et on obtient donnees2:

* Comme on passe de 8 à 32 bits et que tous nos caractères se représentaient sur 16 bits, alors des 0 sont ajoutés au début des caractères pour qu’ils soient représentés sur 32 bits.

## 3.2.1

Les valeurs affichées sont : 0001f440 et 0000010a, la première représente l’adresse de r5 et la deuxième la valeur de r6.

## 3.2.2

```assembly
    .data
D1:    .word  266
D2:    .hword 42
D3:    .byte 12

    .text
    .global main
main:
      LDR r3, LD_D1
      LDR r4, [r3]
      MOV r1, r4
      BL EcrNdecimal32

      LDR r5, LD_D2
      LDRH r6, [r5]
      MOV r1, r6
      BL EcrNdecimal16

      LDR r7, LD_D3
      LDRB r8, [r7]
      MOV r1, r8
      BL EcrNdecimal8

fin:  B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_D1:   .word D1
LD_D2:   .word D2
LD_D3:   .word D3
```



Les valeurs affichées sont 266, 42, 12 comme attendues. Les adresses mémoires où sont rangées les valeurs 266, 42, 12 sont respectivement 0001f474, 0001f478, 0001f47a (affichage en 32 bits). On voit que les adresses changent 4 par 4 car une instruction prend 4 octets.



Pour l’affichage d’adresses le programme est modifié comme ci-dessous:

```assembly
    .data
D1:    .word  266
D2:    .hword 42
D3:    .byte 12

    .text
    .global main
main:
      LDR r3, LD_D1
      LDR r4, [r3]
      MOV r1, r3
      BL EcrHexa32
      MOV r1, r4
      BL EcrNdecimal32

      LDR r5, LD_D2
      LDRH r6, [r5]
      MOV r1, r5
      BL EcrHexa32
      MOV r1, r6
      BL EcrNdecimal16

      LDR r7, LD_D3
      LDRB r8, [r7]
      MOV r1, r7
      BL EcrHexa32
      MOV r1, r8
      BL EcrNdecimal8

fin:  B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_D1:   .word D1
LD_D2:   .word D2
LD_D3:   .word D3
```

## 3.2.3

```assembly
    .data
DW:    .word  0
DH:    .hword 0
DB:    .byte 0

    .text
    .global main
main:
      LDR r0, LD_DH
      LDR r1, [r0]
      BL EcrHexa32 
      BL EcrZdecimal16

      MOV r4, #-10
      LDR r5, LD_DH
      STR r4, [r5]

      LDR r0, LD_DH
      LDR r1, [r0]
      BL EcrHexa32
      BL EcrZdecimal16

fin:  B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_DW:   .word DW
LD_DH:   .word DH
LD_DB:   .word DB
```

On modifie le programme et on utilise la label LD_DH qui correspond en adresse memoire de DH sur la partie .data qui a un profil .hword (16 bits).

## 3.3

### Version 1

```assembly
     .data
cc: @ ne pas modifier cette partie
    .byte 0x42
    .byte 0x4f
    .byte 0x4e
    .byte 0x4a
    .byte 0x4f
    .byte 0x55
    .byte 0x52
    .byte 0x00     @ code de fin de chaine
    @ la suite pourra etr emofifiee
    .word 12
    .word 0x11223344
kk: .asciz "au revoir..."

    .text
    .global main
main:

@ impression de la chaine de caractere d'adresse cc
     ldr r1, LD_cc
     bl EcrChaine

@ impression de la chaine "au revoir..."
     ldr r1, LD_kk
     bl EcrChaine

@ modification de la chaine d'adresse cc
    ldr r2, LD_cc
    ldr r3, [r2]
    add r3, #32
    str r3, [r2]

   InitDeBoucle :
    mov r4,#7

   DebutDeBoucle:
    add r2, #1
    ldrb r3, [r2]
    add r3, #32
    strb r3, [r2]
    subs r4, r4, #1
    bne DebutDeBoucle

@ impression de la chaine cc modifiee
     ldr r1, LD_cc
     bl EcrChaine

fin: B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_cc: .word cc
LD_kk: .word kk
```

#### Explication

Pour afficher la ligne BONJOUR on utilise le label LD_cc pour sauvegarder dans un registre la valeur de l'adresse en mémoire pour cette chaîne des caractères. Ensuite, on l’affiche grâce à une fonction écrite au préalable.Pour afficher “au revoir…” on a ajouté un label dans la partie .data correspondante à: .asciz “au revoir…”. Après on fait que BONJOUR.Pour transformer BONJOUR en minuscule on a décidé d’utiliser une boucle qui dépend de la taille de la mot en commençant par transformer la premiere lettre en minuscule en lui ajoutant la valeure imédiate 32, ensuite on fait de même dans une boucle tout en décrémentant la boucle pour qu’il s'arrête à la fin du mot, mais en incrémentant l'adresse du caractère pour passer au suivant. On utilise ldrb et strb pour prendre seulement un octet en compte.
Puis on affiche le mot bonjour en utilisant la même méthode qu' avant.

### Version 2

```assembly
    .data
cc: @ ne pas modifier cette partie
    .byte 0x42
    .byte 0x6f
    .byte 0x4e
    .byte 0x6a
    .byte 0x4f
    .byte 0x55
    .byte 0x52
    .byte 0x00     @ code de fin de chaine
    @ la suite pourra etr emofifiee
    .word 12
    .word 0x11223344
kk: .asciz "au revoir..."

    .text
    .global main
main:

@ impression de la chaine de caractere d'adresse cc
     ldr r1, LD_cc
     bl EcrChaine

@ impression de la chaine "au revoir..."
        ldr r1, LD_kk
        bl EcrChaine

@ modification de la chaine d'adresse cc
        @ ici le registre r1 correspond à l'adresse de la lettre courante et r3 à la lettre courante
        LDR r1, LD_cc           @ On stocke l'adresse de cc
Boucle: LDRB r3, [r1]           @ On récupère la lettre (un byte uniquement grace à l'option "b") à l'adresse contenue dans r1
        CMP r3, #0x00           @ On compare la lettre au caractère null (qui indique la fin de la chaine)
        BEQ FinBoucle           @ Si il y a egalité, on arrete la boucle
        CMP r3, #97             @ On compare la lettre au "a" (minuscule)
        BHS A                   @ Si elle est de code ascii plus grand ou egal alors elle est deja minuscule donc on passe
        ADD r3, #32             @ Sinon on ajoute 32 au code ascii de la lettre (passe en majuscule)
        STRB r3, [r1]           @ On remets la lettre modifiée dans la chaine de caractères
A:      ADD r1, #1              @ On incrémente l'adresse de la lettre courante (pour passer à la prochaine)
        BAL Boucle              @ On revient au début de la boucle
FinBoucle:

@ impression de la chaine cc modifiee
     ldr r1, LD_cc
     bl EcrChaine

fin: B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_cc: .word cc
LD_kk: .word kk
```

## 3.4.1

Par rapport aux variables déclarés, si on demande l'affichage d’une valeur d’un mot de 32 bits qui n’est pas sur une address de multiple de 4, alors ARM va automatiquement prendre l'adresse de multiple de 4 en dessous de notre address (en soustrayant le nombre qu’il a besoin). Donc, la valeur de notre mot aura une partie des valeurs des mots qui sont déclarés avant. Pour résoudre ce problème, on utilise la fonction *.balign 4* .De même pour *.balign 2* .

## 3.4.2

Pour retrouver les valeurs, on a d’abord converti les valeurs dans la zone data en hexadecimal puis ensuite on les a transformé en little endian Exemple: On a 266 ce qui donne 10A en hexadecimal, donc sur 2 octets cela donne : 0000 010A donc en little endian on a 0A01 0000Donc pour les deux zone data des différents programme on voit que les valeurs se suivent
