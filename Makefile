#CC=gcc
CC=g++
#LIB=-lm
LIB = 
CFLAGS=-O2
NOMSOURCES = fcm.c 
SOURCES = $(NOMSOURCES) main.c
TSOURCES = $(NOMSOURCES) tests.cpp

TLIBS = $(LIB) -lgtest

all :  gen fcm

gen : gen.o
	${CC} ${CFLAGS} -o gen gen.o ${LIB}

gen.o : gen.c
	${CC} ${CFLAGS} -c gen.c

a.out : fcm.o
	${CC} ${CFLAGS} -o a.out fcm.o ${LIB}

fcm.o : fcm.c
	${CC} ${CFLAGS} -c fcm.c

.PHONY: clean test cov covnoclean codecov

test:
	$(CC) ${CFLAGS}  -c $(TSOURCES) 
	$(CC)  -o testapp fcm.o tests.o $(TLIBS)
	./testapp
	$(MAKE) clean

covnoclean:
	$(CC) -c -fprofile-arcs -ftest-coverage -fPIC fcm.c tests.cpp
	$(CC) -o covapp  -fprofile-arcs -ftest-coverage fcm.o tests.o $(TLIBS) 
	./covapp
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	lcov --list coverage.info

cov:
	$(MAKE) covnoclean
	$(MAKE) clean

codecov:
	$(MAKE) covnoclean
	curl -s https://codecov.io/bash > codecovpush.sh
	chmod +x codecovpush.sh
	./codecovpush.sh
	rm codecovpush.sh
	$(MAKE) clean

clean:
	-rm -f *.dat
	-rm -f *.txt
	-rm -f fcm gen
	-rm -f *.o
	-rm -f *~
	-rm -Rf gcov.css snow.png ruby.png *.gcov  *.gcda *.gcno index-sort-f.html index-sort-l.html index.html \
				amber.png glass.png updown.png coverage.info emerald.png Users usr v1\
