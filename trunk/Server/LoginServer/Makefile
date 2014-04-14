include ../Make.defines

OBJS = login_main.o server_manager.o thread_manager.o server_thread.o

# OBJS = ../event/*.o
#STRUCTURES = ../structures/*.o

PROGS =	LoginServer

all:	${PROGS}

LoginServer:	${OBJS}
		${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}
		#${CC} ${CFLAGS} -o $@ ${OBJS} ${STRUCTURES} ${LIBS}

clean:
		rm -f ${OBJS}
