all: console test_comp test_term test_bigchars test_readkey

console: main.o libmyTerm.a libmySimpleComputer.a libmyInterface.a libmyBigChars.a libmyReadKey.a
	gcc -o console main.o -L. -l myTerm -l mySimpleComputer -l myInterface -l myBigChars -l myReadKey

test_comp: test_comp.o libmyTerm.a libmySimpleComputer.a libmyInterface.a libmyBigChars.a libmyReadKey.a
	gcc -o test_comp test_comp.o -L. -l myTerm -l mySimpleComputer -l myInterface -l myBigChars -l myReadKey

test_term: test_term.o libmyTerm.a libmySimpleComputer.a libmyInterface.a libmyBigChars.a libmyReadKey.a
	gcc -o test_term test_term.o -L. -l myTerm -l mySimpleComputer -l myInterface -l myBigChars -l myReadKey

test_bigchars: test_bigchars.o libmyTerm.a libmySimpleComputer.a libmyInterface.a libmyBigChars.a libmyReadKey.a
	gcc -o test_bigchars test_bigchars.o -L. -l myTerm -l mySimpleComputer -l myInterface -l myBigChars -l myReadKey

test_readkey: test_readkey.o libmyTerm.a libmySimpleComputer.a libmyInterface.a libmyBigChars.a libmyReadKey.a
	gcc -o test_readkey test_readkey.o -L. -l myTerm -l mySimpleComputer -l myInterface -l myBigChars -l myReadKey



main.o: main.c
	gcc -c main.c

test_comp.o: test_comp.c
	gcc -c test_comp.c

test_term.o: test_term.c
	gcc -c test_term.c

test_bigchars.o: test_bigchars.c
	gcc -c test_bigchars.c

test_readkey.o: test_readkey.c
	gcc -c test_readkey.c



libmyInterface.a: myInterface.o
	ar cr libmyInterface.a myInterface.o

libmyTerm.a: myTerm.o
	ar cr libmyTerm.a myTerm.o

libmySimpleComputer.a: mySimpleComputer.o
	ar cr libmySimpleComputer.a mySimpleComputer.o

libmyBigChars.a: myBigChars.o
	ar cr libmyBigChars.a myBigChars.o

libmyReadKey.a: myReadKey.o
	ar cr libmyReadKey.a myReadKey.o

myInterface.o: myInterface.c myInterface.h
	gcc -c myInterface.c

myTerm.o: myTerm.c myTerm.h
	gcc -c myTerm.c

mySimpleComputer.o: mySimpleComputer.c mySimpleComputer.h
	gcc -c mySimpleComputer.c

myBigChars.o: myBigChars.c myBigChars.h
	gcc -c myBigChars.c

myReadKey.o: myReadKey.c myReadKey.h
	gcc -c myReadKey.c

.PHONY: clean
clean:
	rm -f *.o *.a *.bin console test_comp test_term test_bigchars test_readkey

