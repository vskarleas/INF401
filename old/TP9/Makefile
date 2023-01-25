all: fact1

fact1: fact1.o multiplication.o essai-fact1.o es.o
	arm-eabi-gcc -g -o fact1 fact1.o multiplication.o essai-fact1.o es.o

multiplication.o: multiplication.s
	arm-eabi-gcc -g -c -o multiplication.o multiplication.s

fact1.o: fact1.s
	arm-eabi-gcc -g -c -o fact1.o fact1.s

es.o: es.s
	arm-eabi-gcc -g -c -o es.o es.s

essai-fact1.o: essai-fact1.s
	arm-eabi-gcc -g -c -o essai-fact1.o essai-fact1.s
