include ../Make.defines

PROGS =	gameserver

all:	${PROGS}

gameserver:	gameserver.o
		${CC} ${CFLAGS} -o $@ gameserver.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
