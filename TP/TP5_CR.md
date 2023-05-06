# TP5

##### Gwendal Trehin, Noan Simon, Vasileios Skarleas

## 4.1


|itération|valeur de r0|contenu de tab|
| :- | :- | :- |
|1|74492|11 0 0 0 0|
|2|74496|11 22 0 0 0|
|3|74500|11 22 33 0 0 |
|4|74504|11 22 33 44 0|
|5|74508|11 22 33 44 55|

adresse decut debutTab : 0x122fc

adresse de in : 0x1230c

## 4.2

### Question 2 et 3


|itération|valeur de r0|valeur de r2|
| :- | :- | :- |
|0 (avant le debut)|74476|0|
|1|74476|1|
|2|74480|2|
|3|74484|3|
|4|74488|4|
|5 (dernier test : sortie)|74492|5|

### Question 4

À la fin de l’iteration le valeur de r2 est 5. La raison pour laquelle pendant la comparaison en ligne 11, il y avait un branchement vers l'étiquette fintq.

### Question 5

Les lignes modifiées sont :

```assembly
11: cmp r2,  #4

12: bhi fintq
```

### Question 6

|itération|valeur de r0|valeur de r2|
| :- | :- | :- |
|0 (avant le debut)|74476|0|
|1|74476|1|
|2|74478|2|
|3|74480|3|
|4|74482|4|
|5 (dernier test : sortie)|74484|5|

Les lignes modifiées sont :

```assembly
2: debuTAB: .skip 5\*2

15: add r0, r0, r2, LSL #1

16: strh r3, [r0] 
```

### Question 7


|itération|valeur de r0|valeur de r2|
| :- | :- | :- |
|0 (avant le debut)|74476|0|
|1|74476|1|
|2|74477|2|
|3|74478|3|
|4|74479|4|
|5 (dernier test : sortie)|74480|5|

Les lignes modifiées sont :

```assembly
2: debuTAB: .skip 5\*1

15: add r0, r0, r2

16: strb r3, [r0] 
```

## 4.3

```assembly
.text
.global main

main:
	mov r1, #15 @U0 initialisé à 15
BoucleLogic:
	cmp r1, #1
	beq fintq
Boucle:
	tst r1, #1 @Test pour pair ou impair
	beq sinon @Si c'est pair alors tu fait le "sinon", else tu fait le "alors"
alors:
	mov r0, r1
	lsl r1, #1
	add r1,r1,r0
	add r1,r1,#1 	@(x*3)+1
	b finsi
sinon:
   lsr r1,#1	@x div 2
finsi:
	b BoucleLogic
fintq:
```

Les valeurs sont celles attendues.





