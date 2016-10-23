#ifndef TREE_H
#define TREE_H

#include "hashtag.h"

/* Struct TREEnode - Um no de arvore que armazena um Item, o valor da altura(height)
	usado para AVL e dois ponteiros para os filhos (esquerdo e direito) */
typedef struct TREEnode {
    Item item;
    int height;
    struct TREEnode *l, *r;
} *tnode;

/* Struct tree - Um ponteiro para um TREEnode, em particular, a raiz da
   instancia da arvore */
typedef struct tree {
    struct TREEnode *h;
} *Tree;

/* Construtores*/
Tree TREEinit();  /* Inicializa a arvore */

/* Testes */
int TREEisempty();

/* Mutadores */
void TREEadd(Tree, Item);
void TREEfree(Tree); /* Liberta uma arvore e todos os seus elementos */

/* Acessorios */
Item TREEsearchByKey(Tree, Key); /* Procura por Key */
void TREEtraverseCopy(Tree, Item*); /* Copia in-order para vetor auxiliar */

#endif
