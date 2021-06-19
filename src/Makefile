CC = g++
CFLAGS = -Wall -g -std=c++17

main: main.o Jobs.o Parsetab.o Utils.o Remote.o Local.o
	${CC} ${CFLAGS} -o $@ $^

main.o: main.cc Parsetab.h Jobs.h Remote.h Local.h
	${CC} ${CFLAGS} -c $<

Parsetab.o: Parsetab.cc Parsetab.h Jobs.h Utils.h
	${CC} ${CFLAGS} -c $<

Jobs.o: Jobs.cc Jobs.h 
	${CC} ${CFLAGS} -c $<

Utils.o: Utils.cc Utils.h
	${CC} ${CFLAGS} -c $<

Remote.o: Remote.cc Remote.h
	${CC} ${CFLAGS} -c $<

Local.o: Local.cc Local.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o *~ main
