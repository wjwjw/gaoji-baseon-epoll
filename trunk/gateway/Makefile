include ../Make.defines

PROGS =	server

all:	${PROGS}

server:	mgeeg.o global_gateway_server.o
		${CC} ${CFLAGS} -o $@ mgeeg.o global_gateway_server.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
