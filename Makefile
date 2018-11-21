#CC=gcc
CC=g++
#LIB=-lm
LIB = -pthread  
#CFLAGS=-O2 -I /usr/local/include/eigen3
#CFLAGS= -I /usr/local/include/eigen3
#CFLAGS= -std=c++11 -I /usr/local/include/eigen3 -Wzero-as-null-pointer-constant
CFLAGS= -I /usr/local/include/eigen3 -Wzero-as-null-pointer-constant
NOMSOURCES = fcm.cpp
SOURCES = $(NOMSOURCES) main.c
TSOURCES = $(NOMSOURCES) tests.cpp

#TLIBS = $(LIB) -lgtest
#TLIBS = $(LIB) -lgtest -Wzero-as-null-pointer-constant
TLIBS = $(LIB) -lgtest -I /usr/local/include/eigen3  -Wzero-as-null-pointer-constant
#TLIBS = $(LIB) -lgtest -std=c++11 -I /usr/local/include/eigen3 -Wzero-as-null-pointer-constant

all :  gen fcm

gen : gen.o
	${CC} ${CFLAGS} -o gen gen.o ${LIB}

gen.o : gen.c
	${CC} ${CFLAGS} -c gen.c

a.out : fcm.o
	${CC} ${CFLAGS} -o a.out fcm.o ${LIB}

fcm.o : fcm.cpp
	${CC} ${CFLAGS} -c fcm.cpp

.PHONY: clean test cov covnoclean codecov

test:
	$(CC) ${CFLAGS}  -c $(TSOURCES) 
	$(CC)  -o testapp fcm.o tests.o $(TLIBS)
	./testapp
	$(MAKE) clean

covnoclean:
	$(CC) ${CFLAGS}  -c -fprofile-arcs -ftest-coverage -fPIC fcm.cpp tests.cpp
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
	$(RM) covapp
	$(RM) testapp
	$(RM) *.dat
	$(RM) *.txt
	$(RM) fcm gen
	$(RM) *.o
	$(RM) *~
	$(RM)  gcov.css snow.png ruby.png *.gcov  *.gcda *.gcno index-sort-f.html index-sort-l.html index.html \
				amber.png glass.png updown.png coverage.info emerald.png Users usr v1\
