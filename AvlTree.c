#include<stdio.h>
#include<stdlib.h>

typedef struct _nodo{
	int chave;
	int altura, nivel;
	int altdireita,altesquerda;
	struct _nodo *esq;
	struct _nodo *dir;
	struct _nodo *pai;
} TpNodo;

typedef struct _arvore{
	TpNodo *raiz;
} TpArvore;

TpArvore *inicializa(){//aloca memoria para inicializar a arvore
	TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
	arvore->raiz=NULL;
	return arvore;
}

void *inserir(int key, TpArvore *arvore){
 if(arvore->raiz == NULL ){
			TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
			nodo->chave = key;
			nodo->altura = 0;
			nodo->nivel = 0;
			nodo->altdireita = 0;
			nodo->altesquerda = 0;
			nodo->esq = NULL;
			nodo->dir = NULL;
			nodo->pai = NULL;
			printf("d");
			arvore->raiz = nodo;
	}else	if(key == arvore->raiz->chave){
			printf("Chave ja existente!");
			return;
		}else if(key > arvore->raiz->chave ){
			if(arvore->raiz->dir != NULL){
				arvore->raiz = arvore->raiz->dir;
				inserir(key, arvore);
			}else{
				TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
				nodo->chave = key;
				nodo->pai = arvore->raiz;
				nodo->esq = NULL;
				nodo->dir = NULL;
				nodo->altura = 0;
				nodo->nivel = arvore->raiz->nivel + 1;
				if(arvore->raiz->esq == NULL)
					nodo->altesquerda = 0;
				else{
					nodo->altesquerda = arvore->raiz->esq->altura;
					}
				nodo->altdireita = 0;
				arvore->raiz->dir = nodo;
				}
			}else {//key < raiz.chave
				if(arvore->raiz->esq != NULL){
					arvore->raiz = arvore->raiz->esq;
					inserir(key, arvore);
				}else{
					TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
					arvore->raiz->esq = nodo;
					nodo->chave = key;
					nodo->pai = arvore->raiz;
					nodo->esq = NULL;
					nodo->dir = NULL;
					nodo->altura = 0;
					nodo->nivel = arvore->raiz->nivel + 1;
					if(arvore->raiz->dir == NULL)
						nodo->altdireita = 0;
					else
						nodo->altdireita = arvore->raiz->dir->altura;
					nodo->altesquerda = 0;
			}
		}


}

int main(){
	TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
	arvore=inicializa();
	int n, key;
	do{
		printf("\tMENU\n");
		printf("Digite a opção desejada:\n");
		printf("1: Inserir\n");
		printf("2: Exibir\n");
		printf("0: Sair\n");
		scanf("%d", &n);
		switch(n){
			case 1:
				scanf("%d", &key);
				inserir(key, arvore);
				break;
			case 2:
				break;
			default:
				printf("opção invalida!");
				break;
			}
	}while(n!=0);


}
