SOURCES_COMPUTE = sprint_bin.c  global.c string_to_int.c bit_bit.c handle_args.cadd_sub.c display.c

OBJECTS_COMPUTE  = sprint_bin.o  global.o string_to_int.o bit_bit.o handle_args.o add_sub.o display.o

LINKS =	add addsc sub subsc subc2 subc2sc not and or xor lsr asr lsl ror rol msk1 msk2

CC = gcc
LD = gcc

CCOPTS = -c -Wall

# INSTALLDIR = ../../bin
INSTALLDIR = bin

COPY_COMMAND = ln -s   # use cp instead for non-unix file systems (Windows/CYGWIN)
COPY_COMMAND = ln

all:	computebin links

clean:
	/bin/rm -f  ${OBJECTS_COMPUTE} computebin.o computebin ${LINKS}  >& /dev/null

install: all
#	/bin/cp -f ${LINKS} computebin ${INSTALLDIR}
	/bin/mv -f ${LINKS} computebin ${INSTALLDIR}

installopt: all
#	/bin/cp -f ${LINKS} computebin /opt/gnu/bin
	/bin/mv -f ${LINKS} computebin /opt/gnu/bin
	for i in ${LINKS}; do chgrp dlst-ens /opt/gnu/bin/$$i; done

%.o: %.c %.h global.h
	${CC} ${CCOPTS} $<


computebin:	${OBJECTS_COMPUTE} computebin.o

computebin.o:	handle_args.h sprint_bin.h

display.o:	sprint_bin.h

string_to_int:	sprint_bin.h handle_args.h

handle_args.o:	bit_bit.h add_sub.h string_to_int.h sprint_bin.h display.h





links:		${LINKS}

add:		computebin
		/bin/rm -f add > /dev/null; ${COPY_COMMAND} computebin add

addsc	:	computebin
		/bin/rm -f addsc > /dev/null; ${COPY_COMMAND} computebin addsc

sub:		computebin
		/bin/rm -f sub > /dev/null; ${COPY_COMMAND} computebin sub

subsc:		computebin
		/bin/rm -f subsc > /dev/null; ${COPY_COMMAND} computebin subsc

subc2:		computebin
		/bin/rm -f subc2 > /dev/null; ${COPY_COMMAND} computebin subc2

subc2sc:	computebin
		/bin/rm -f subc2sc > /dev/null; ${COPY_COMMAND} computebin subc2sc

not:		computebin
		/bin/rm -f not > /dev/null; ${COPY_COMMAND} computebin not

and:		computebin
		/bin/rm -f and > /dev/null; ${COPY_COMMAND} computebin and

or:		computebin
		/bin/rm -f or > /dev/null; ${COPY_COMMAND} computebin or

xor:		computebin
		/bin/rm -f xor > /dev/null; ${COPY_COMMAND} computebin xor

lsr:		computebin
		/bin/rm -f lsr > /dev/null; ${COPY_COMMAND} computebin lsr

asr:		computebin
		/bin/rm -f asr > /dev/null; ${COPY_COMMAND} computebin asr

lsl:		computebin
		/bin/rm -f lsl > /dev/null; ${COPY_COMMAND} computebin lsl

ror:		computebin
		/bin/rm -f ror > /dev/null; ${COPY_COMMAND} computebin ror

rol:		computebin
		/bin/rm -f rol >& /dev/null ; ${COPY_COMMAND} computebin rol

msk1:		computebin
		/bin/rm -f msk1 >& /dev/null ; ${COPY_COMMAND} computebin msk1

msk2:		computebin
		/bin/rm -f msk2 >& /dev/null ; ${COPY_COMMAND} computebin msk2
