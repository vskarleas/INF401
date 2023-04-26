# TD5 et 6

## 4.1

### 1.

```assembly
@ a dans r4, b dans r5, c dans r6
	CMP r4, r5 @ a-b ??
	BNE sinon
alors:
	mov r6, #0
	B finsi
sinon:
	add r6, r4, r5
finsi:
```

```assembly
@ a dans r4, b dans r5, c dans r6
	CMP r4, r5 @ a-b ??
	BEQ alors
sinon:
	add r6, r4, r5
	B finsi
alors:
	mov r6, #0
finsi:
```

### 2.

Renvoie toujours `a + b`

### 3.

```assembly
@ x dans r7
	mov r8, r7, LSR #1
	mov r9, r8, LSL #1
	cmp r9, r7
	bne sinon
alors:
	mov r7, r8
	b finsi
sinon:
	add r9, r7, r7
	add r7, r7, r9
	add r7, r7, #1
finsi:
```

```assembly
@ x dans r7
	TST r7, #1
	bne sinon
alors:
	mov r7, r8
	b finsi
sinon:
	mul r7, r7, #3
	add r7, r7, #1
finsi:
```



## 4.2

L'adresse d'une case est `debutTAB + 4*i` 

```assembly
	. bss
debutTAB : .skip 5∗4
	. text
	. global main
main :
	ldr r4 ,LD debutTAB
	mov r5 ,#11
	str r5 ,[ r4 ]

	mov r5 , #22
	str r5 , [ r4, #4]
	
	mov r5 , #33
	str r5 , [ r4, #8]
	
	mov r5 , #44
	str r5 , [ r4, #12]
	
	mov r5 , #55
	str r5 , [ r4, #16]

fin : bx lr

LD debutTAB : . word debutTAB
```



## 4.3

```assembly
	mov r7, #11
	mov r6, #0
	mov r4, 
debutboucle:
	ldr r4
```

























































