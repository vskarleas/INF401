CC=/opt/gnu/arm/bin/arm-eabi-gcc
AS=/opt/gnu/arm/bin/arm-eabi-gcc

CFLAGS=-Wall -gdwarf-2 

# Object files created from .S source code
OBJS = es.o essai-map.o map.o multiplication.o fg.o gestion_tab.o 

OBJS2 = es.o essai-map2.o map2.o multiplication.o fg.o gestion_tab.o 

OBJS2v1 = es.o essai-map2v1.o map2v1.o multiplication.o fg.o gestion_tab.o 

OBJS_RED = red.o essai-red.o es.o multiplication.o fg.o gestion_tab.o 

all:	essai-map essai-red essai-map2 essai-map2v1

clean:
	/bin/rm -rf *.o 

%.o : %.s
	${CC} ${CFLAGS} -c $< -o $@
	
essai-map:	${OBJS}
	${CC} ${OBJS} -o $@

essai-map2:	${OBJS2}
	${CC} ${OBJS2} -o $@

essai-map2v1:	${OBJS2v1}
	${CC} ${OBJS2v1} -o $@

essai-red:	${OBJS_RED}
	${CC} ${OBJS_RED} -o $@
