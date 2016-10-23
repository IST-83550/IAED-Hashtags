#ifndef HASHTAG_H
#define HASHTAG_H

#include <string.h>

/* Macros para o ADT Tree */
typedef char* Key;
#define Item hashtag
#define key(A) (A != NULL ? A->name : "")
#define key_highest(A) A->num
#define less(A, B) (strcmp(A,B) < 0)
#define deleteItem free

/* Estrutura hashtag - Representa uma hashtag de id (name) e o
   numero de ocorrencias(num) */
typedef struct hashtag{
	char* name;
	int num;
} *hashtag;

hashtag highest; /* Armazena a maior hashtag */

/* Macros para o ADT MergeSort */
#define ItemToSort hashtag*
#define KeyToSort(A) A->num
#define less_sort(A, B) ( KeyToSort(A) >= KeyToSort(B) )

/* Construtor */
hashtag newHASHTAG(char*); /*Cria nova hashtag com nome = message */

/* Acessorios */
void highestHASHTAG(hashtag, hashtag, char*); /* atualiza maior hashtag */
int numHASHTAG(hashtag); /* acede ao numero de ocorrencias de uma hashtag */
char* nameHASHTAG(hashtag); /* acede ao nome da hashtag */

/* Mutadores */
void incHASHTAG(hashtag); /* incrementa ocorrencias da hashtag */

/* Testes */
int existsHASHTAG(hashtag); /* Verifica a existencia da hashtag */

/* Prints */
void printHASHTAG(hashtag); /* Imprime o nome e o numero de ocorrencias de uma hashtag */

#endif
