include ../Make.defines

PROGS =	hello

all:	${PROGS}

hello:	hello.o
		${CC} ${CFLAGS} -o $@ hello.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
