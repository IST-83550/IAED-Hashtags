#include <stdio.h>
#include <stdlib.h>

#include "hashtag.h"
#include "tree.h"

/*------GERAIS------*/

/*  Cria um novo no cujo elemento e item, tem como filho da esquerda o no l e
da direita o no r
	INPUT : Item(item), link para filho esquerdo(l), link para filho direito(r)
  OUTPUT : Ponteiro para no(x) */
tnode newTREEnode(Item item, tnode l, tnode r) {

 	tnode x = (tnode) malloc(sizeof(struct TREEnode));

 	x->item = item;
 	x->l = l;
 	x->r = r;
 	x->height = 1;
 	return x;
}

/* Liberta um no, libertando o item e de seguida o ponteiro para o mesmo
   INPUT : link para no(x) */
void freeTREEnode(tnode x){
	free(x->item->name);
	deleteItem(x->item);
	free(x);
}

/* Calcula a altura de um no
   INPUT : link para head(h)
   OUTPUT : altura do no */
int height(tnode h){
    if (h == NULL) return 0;
    return h->height;
}

/* Procura qual o elemento maximo de uma arvore (o mais a direita)
   INPUT : link para head(h)
   OUTPUT : ponteiro para elemento maximo*/
tnode max(tnode h){
	if (h == NULL || h->r == NULL) return h;
	else return max(h->r);
}

/* Procura o elemento minimo de uma arvore (o mais a esquerda)
   INPUT : link para head(h)
   OUTPUT : Ponteiro para elemento minimo */
tnode min(tnode h){
	if (h == NULL || h->l == NULL) return h;
	else return min(h->l);
}

/* Determina o factor de balanco/equilibrio entre dois nos (abs(factor) <= 1 ->
equilibrada)
   INPUT : link para no(h)
   OUTPUT : diferenca de alturas entre os nos */
int Balance(tnode h){
    if (h == NULL) return 0;
    else return height(h->l) - height(h->r);
}

/* Aplica uma rotacao a esquerda a um no, restruturando uma sub-arvore
   INPUT : link para no(h) */
tnode rotL(tnode h){
	int height_l, height_r;
	
	tnode x = h->r;
	h->r = x->l;
	x->l = h;
	
	/* Actualiza ainda os valores das alturas dos nos */
	height_l = height(h->l);
	height_r = height(h->r);
	h->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	height_l = height(x->l);
	height_r = height(x->r);
	x->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	return x;
}

/* Aplica uma rotacao a direita a um no, restruturando uma sub-arvore
   INPUT : Item, link para no(h)*/
tnode rotR(tnode h){
	int height_l, height_r;
	
	tnode x = h->l;
	h->l = x->r;
	x->r = h;

	/* Actualiza ainda os valores das alturas dos nos */	
	height_l = height(h->l);
	height_r = height(h->r);
	h->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	height_l = height(x->l);
	height_r = height(x->r);
	x->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	return x;
}

/* Dupla rotacao a esquerda e a de seguida a direita
   INPUT : Item, link para no(h)
   OUTPUT : resultado da rotacao LR */
tnode rotLR(tnode h){
	if (h == NULL) return h;
	h->l = rotL(h->l);
	return rotR(h);
}

/* Dupla rotacao a direita e de seguida a esquerda
   INPUT : Item, link para no(h)
   OUTPUT : resultado da rotacao RL */
tnode rotRL(tnode h){
	if (h == NULL) return h;
	h->r = rotR(h->r);
	return rotL(h);
}

/* Equilibra a arvore apos a insercao de um elemento
   INPUT : Item, link para head(h) */
tnode AVLbalance(tnode h){
    int balanceFactor;
    
    if (h == NULL) return h; 
    balanceFactor = Balance(h);
    
    if(balanceFactor > 1) {
        if (Balance(h->l) > 0) h = rotR(h);
        else h =rotLR(h);
    }
    else if(balanceFactor < -1) {
        if (Balance(h->r) < 0) h = rotL(h);
        else h = rotRL(h);
    }
    else {
        int height_l = height(h->l);
        int height_r = height(h->r);
        h->height = height_l > height_r ? height_l + 1 : height_r + 1; 
    } 
    return h;
}

/*------CONSTRUTORES------*/

/* Inicializa a arvore
   OUTPUT : ponteiro para arvore */
Tree TREEinit(){
	Tree t = (Tree) malloc(sizeof(struct tree));
	
	t->h = NULL;
	return t;
}

/*------ACESSORIOS------*/

/* Devolve True se a arvore esta vazia
   INPUT : arvore(t)
   OUTPUT : valor logico */
int TREEisempty(Tree t){
    return t->h == NULL;
}

/* Procura um elemento na arvore
   INPUT : link para no(h), Key(k)
   OUTPUT : ponteiro para item */
Item searchR(tnode h, Key k){
    if (h == NULL) return NULL;
    if (less(k, key(h->item)))
      return searchR(h->l, k);
    else if (less(key(h->item), k))
      return searchR(h->r, k);
    else
      return h->item;
}

/* Procura elemento na arvore por Key
   INPUT : Arvore(t), Key (k)
   OUTPUT : ponteiro para item */
Item TREEsearchByKey(Tree t, Key k){
   return searchR(t->h, k);
}

/*------MUTADORES------*/

/* Insere um no na arvore cujo elemento e item
   INPUT : link para head(h), Item(item) */
tnode insertR(tnode h, Item item){
  Item v = item;
  if (h == NULL) return newTREEnode(item, NULL, NULL);

  if (less(key(v), key(h->item)))
    h->l = insertR(h->l, item);
  else
    h->r = insertR(h->r, item);

  h = AVLbalance(h);  

  return h;
}

/* Insere elemento na arvore
   INPUT : arvore(t), Item(item)*/
void TREEadd(Tree t, Item item){
    t->h = insertR(t->h, item);
}

/* Percorre os elementos da arvore (post-order) e liberta os mesmos
   INPUT : link para head(h)*/
void deleteTree(tnode h){
    if (h == NULL) return;
	if (h != NULL) {
			deleteTree(h->l);
			deleteTree(h->r);
			freeTREEnode(h);
	}
}

/* Liberta arvore
   INPUT : arvore(t)*/
void TREEfree(Tree t){
    deleteTree(t->h);
    free(t);
}

/* Percorre arvore e copia elementos para vetor auxiliar (in-order)
   INPUT : numero de iteracoes(*i), link para no(h), vetor auxiliar de Items(aux)*/
void traverseCopy(int *i, tnode h, Item* aux){   /*copia por ordem alfabetica*/
    if (h == NULL) return;
    if(h->l != NULL)
    	traverseCopy(i, h->l, aux);
    aux[*i] = h->item; ++*i;
    if(h->r != NULL)
    	traverseCopy(i, h->r, aux);
}

/* Copia arvore para vetor auxiliar
   INPUT : arvore t, vetor auxiliar de Items(aux)*/
void TREEtraverseCopy(Tree t, Item* aux){
	int i = 0;
	traverseCopy(&i, t->h, aux);
}