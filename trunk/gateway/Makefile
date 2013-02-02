include ../Make.defines

PROGS =	gameServer

all:	${PROGS}

gameServer:	gameServer.o
		${CC} ${CFLAGS} -o $@ gameServer.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
