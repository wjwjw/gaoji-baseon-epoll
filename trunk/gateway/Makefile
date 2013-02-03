include ../Make.defines

PROGS =	server01

all:	${PROGS}

server01:	mgeeg.o global_gateway_server.o
		${CC} ${CFLAGS} -o $@ mgeeg.o global_gateway_server.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
