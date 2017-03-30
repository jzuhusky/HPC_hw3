
CC=mpicc
flags=-O3
EXEC=int_ring.run

METHODS=int_ring

all:${METHODS}

int_ring: int_ring.c
	${CC} ${FLAGS} -o ${EXEC} ${ompFlag} $^

clean:
	rm -f *.run
