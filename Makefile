CC=gcc
LIB=-lm
CFLAGS=-O2

all : gen fcm

gen : gen.o
	${CC} ${CFLAGS} -o gen gen.o ${LIB}

gen.o : gen.c
	${CC} ${CFLAGS} -c gen.c

fcm : fcm.o
	${CC} ${CFLAGS} -o fcm fcm.o ${LIB}

fcm.o : fcm.c
	${CC} ${CFLAGS} -c fcm.c

clean:
	rm -f fcm gen
	rm -f *.o
	rm -f *~
