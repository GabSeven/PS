DIR_FILA_LIB=.
DIR_INCLUDE=${DIR_FILA_LIB}/include
DIR_OBJ=${DIR_FILA_LIB}/obj

FILA_C=${DIR_FILA_LIB}/src/fila.c

OBJ_FILA=${DIR_OBJ}/fila.o

fila.o: ${DIR_INCLUDE}/fila.h ${FILA_C}
	mkdir -p obj
	gcc -c -I${DIR_INCLUDE} -o ${OBJ_FILA} ${FILA_C}

clean:
	rm ${DIR_OBJ}/*
	rmdir ${DIR_OBJ}