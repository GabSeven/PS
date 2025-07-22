DIR_PILHA_LIB=.
DIR_INCLUDE=${DIR_PILHA_LIB}/include
DIR_OBJ=${DIR_PILHA_LIB}/obj

PILHA_C=${DIR_PILHA_LIB}/src/pilha.c

OBJ_PILHA=${DIR_OBJ}/pilha.o

pilha.o: ${DIR_INCLUDE}/pilha.h ${PILHA_C}
	mkdir -p obj
	gcc -c -I${DIR_INCLUDE} -o ${OBJ_PILHA} ${PILHA_C}

clean:
	rm ${DIR_OBJ}/*
	rmdir ${DIR_OBJ}