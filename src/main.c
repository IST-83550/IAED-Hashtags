/*     IAED 2015-2016       */
/*        PROJETO 2         */
/*   PEDRO SANTOS - 83550   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* TADs */
#include "hashtag.h" /* Hashtag */
#include "tree.h"  /* Arvore de pesquisa binaria AVL */
#include "mergesort.h" /* Funcao de mergesort (estavel) */

/*Contadores globais*/
int Ntags = 0, Ntotal = 0; /* Numero de hashtags distintas / numero total */

/* Parsing */
#define MAX_MESSAGE 140  /* Maior tamanho para uma mensagem */
#define NUMSEP 11
static const char separators[] = {' ','\t',',',';','.','?','!','"','\n',':','\0'};

void addHASHTAG(char*, Tree);
void printList(Tree);
void end(Tree);

int main(){

	/* Armazena a mensagem introduzida no comando a */
    char* message = (char*) malloc(sizeof(char)*(MAX_MESSAGE + 1)); /* + NULL */
    char command;  /* Armazena comando */

	Tree hashtags = TREEinit(); /* Inicializa arvore */

	while(1){

		command = getchar();

		switch(command){

			case 'a':
			/*  Processa uma mensagem incrementando para cada hashtag o
			    contador respetivo */

				fgets(message, MAX_MESSAGE, stdin);

				addHASHTAG(message, hashtags);

			break;

			case 's':
			/*  Mostra o numero de hashtags disitintas e o numero total
			    de hashtags */

				printf("%d %d\n", Ntags, Ntotal);

				getchar();
			break;

			case 'm':
			/*  Mostra a hashtag mais popular */

				if(!TREEisempty(hashtags)){
					if (existsHASHTAG(highest))
						printHASHTAG(highest);
				}

				getchar();
			break;

			case 'l':
			/*  Lista todas as hashtags por ordem decrescente de numero
			    de ocorrencias. Em caso de igualdade sao listadas por
			    ordem alfabetica */			

				printList(hashtags);

				getchar();
			break;

			case 'x':
			/*  Termina o programa */

				free(message);

				end(hashtags);

			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

/* Adiciona uma hashtag a arvore de hashtags e atualiza os contadores de
   hashtags e a maior hashtag.
   INPUT: linha de texto(line), arvore de hashtags(hashtags) */
void addHASHTAG(char *line, Tree hashtags){
	int i, j, k;
	char buffer[MAX_MESSAGE+1];
	hashtag aux;

	for (i = 0, k = 0; line[i] != '\0'; i++, k++){
		buffer[k] = tolower(line[i]);
		for(j = 0; j < NUMSEP; j++){
			if(line[i] == separators[j]){
				if(k != 0){
					buffer[k] = '\0';

					if(buffer[0] == '#'){
						Ntotal++;     /* Atualiza contador de hashtags total */

						hashtag c = TREEsearchByKey(hashtags, buffer);

						if(existsHASHTAG(c))
							incHASHTAG(c);      /* Atualiza numero de ocorrencias */

						else{         /* Se nao existir na arvore */
							Ntags++;  /* Atualiza contador de hashtags diferentes */
							aux = newHASHTAG(buffer);
							TREEadd(hashtags, aux);

							if(highest == NULL)    /* Inicializa highest */
								highest = aux;
						}

						highestHASHTAG(c, aux, buffer);     /* Atualiza maior hashtag */	

					}
				}
				k = -1;
			}
		}
	}
}

/* Imprime lista de hashtags
   INPUT: vetor de hashtags(aux)*/
void print_sorted(hashtag* aux){
	int i;
	for (i = 0; i < Ntags; i++)
		printf("%s %d\n", nameHASHTAG(aux[i]), numHASHTAG(aux[i]));
}

/*  Ordena e imprime hashtags
	INPUT: arvore de hashtags(hashtags) */
void printList(Tree hashtags){

    hashtag* aux = (hashtag*) malloc(sizeof(struct hashtag)*Ntags);  /*vetor auxiliar para ordenacao*/

	TREEtraverseCopy(hashtags, aux);

	Sort(aux, 0, Ntags-1);

	print_sorted(aux);

	/* liberta vetor auxiliar */
	free(aux);
}

/* Termina o programa libertando a memoria ocupada
   INPUT: arvore de hashtags(hashtags) */
void end(Tree t){
	TREEfree(t);
}
