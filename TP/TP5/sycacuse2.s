.text
.global main
@Version optimisé sans utiliser r2
main:
    mov r1, #15 @U0 initialisé à 15
BoucleLogic:
    cmp r1, #1
    beq fin
Boucle:
    tst r1, #1 @Test pour pair ou impair
    beq sinon @Si c'est pair alors tu fait le "sinon", else tu fait le "alors"
alors:
    mov r8, r1
    lsl r1,#1    @x * 2
    add r1,r1,r8
    add r1,r1,#1     @(x*3)+1
    b finsi
sinon:
   lsr r1,#1    @x div 2
finsi:
    b BoucleLogic
fin:
