BIBNAME = pilha
#diretorio do .h para a biblioteca pilha
INCLUDE_PILHA = /home/nilton/Documents/pilha/include
#diretorio do .c para a biblioteca pilha
SRC_PILHA = /home/nilton/Documents/pilha/fonte
#diretorio onde sera gerado o arquivo objeto (.o) da biblioteca pilha
OBJ_PILHA = /home/nilton/Documents/pilha/obj

all: pilha
	gcc -I ${INCLUDE_PILHA} ${OBJ_PILHA} usa_pilha.c -o usa_pilha

pilha: ${INCLUDE_PILHA}/${BIBNAME}.h ${SRC_PILHA}/${BIBNAME}.c
	gcc -c -I ${INCLUDE_PILHA} ${SRC_PILHA}/${BIBNAME}.c -o ${OBJ_PILHA}/${BIBNAME}.o

