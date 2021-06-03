CC = g++
CFLAGS = -Wall -g -std=c++17

main: main.o Jobs.o Parsetab.o
	${CC} ${CFLAGS} -o $@ $^

main.o: main.cc Parsetab.h Jobs.h
	${CC} ${CFLAGS} -c $<

Parsetab.o: Parsetab.cc Parsetab.h Jobs.h
	${CC} ${CFLAGS} -c $<

Jobs.o: Jobs.cc Jobs.h 
	${CC} ${CFLAGS} -c $<

