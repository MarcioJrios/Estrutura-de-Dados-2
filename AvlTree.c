#include<stdio.h>
#include<stdlib.h>

int Cont;
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
	int NDir;
	int NEsq;
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
			NDir = 0;
			NEsq = 0;
	}else	if(key == arvore->raiz->chave){
			printf("Chave ja existente!");
			return;
		}else if(key > arvore->raiz->chave ){
			if(arvore->raiz->dir != NULL){
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
				arvore->raiz = arvore->raiz->dir;
				if(arvore.NDir < arvore->raiz->nivel)
					arvore.NDir = arvore->raiz->nivel;
				}
			}else {//key < raiz.chave
				if(arvore->raiz->esq != NULL){
					arvore->raiz = arvore->raiz->esq;
					inserir(key, arvore);
				}else{
					TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
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
					arvore->raiz->esq = nodo;
					arvore->raiz = arvore->raiz->esq;
					if(arvore.NEsq < arvore->raiz->nivel)
						arvore.NEsq = arvore->raiz->nivel;
			}
		}
}

void *balancearDir(TpArvore arvore){

}

void *balancearEsq(TpArvore arvore){
	if(arvore->raiz->esq == NULL && arvore->raiz->dir == NULL){//Se estiver em uma folha finaliza
		return;
	}else if(arvore->raiz->esq != NULL){//Verifica se os filhos sao nulos para fazer a comparação de altura
		if(arvore-raiz->dir == NULL)
			arvore->raiz->esq->altdireita = 0;
		else
			arvore->raiz->esq->altdireita = arvore->raiz->dir->altura;
		if(arvore->raiz->esq->alt > arvore->raiz->esq->altdireita){//se a altura do filho esquerdo for maior que o direito
			int calcB = arvore->raiz->esq->alt - arvore->raiz->esq->altdireita;
			if(calcB <= -2 || calcB >= 2){//Caso do right right
				arvore->raiz = arvore->raiz->esq;
				TpNodo *aux = arvore->raiz;
				arvore->raiz->pai = arvore->raiz->pai->pai;
				arvore->raiz->pai->esq = arvore->raiz;
				arvore->raiz->dir = aux->pai;
				arvore->raiz->dir->pai = arvore->raiz;
				if(aux->pai->altdireita == 0){
					arvore->raiz->dir->dir = NULL;
					arvore->raiz->dir->esq = NULL;
				}else
					arvore->raiz->dir->esq = NULL;
				//avança para o proximo no com maior altura e executa novamente a verificação
				arvore->raiz = arvore->raiz->esq;
				Cont++
				balancearEsq(arvore);
				return;
			}else{
				//Se esse nó nao esta balanceado, move para o proximo e execura novamente a verificação
				arvore->raiz = arvore->raiz->esq;
				Cont++;
				balancearEsq(arvore);
				return;
				}
		}else if(arvore->raiz->esq->alt < arvore->raiz->esq->altdireita{//Caso do joelho
			int calcB = arvore->raiz->esq->alt - arvore->raiz->esq->altdireita;
			if(calcB <= -2 || calcB >= 2){
				arvore->raiz = arvore->raiz->dir;
				TpNodo *aux = arvore->raiz;
				arvore->raiz->pai = arvore->raiz->pai->pai;
				arvore->raiz->esq = aux->pai;
				arvore->raiz->pai->esq = arvore->raiz;
				arvore->raiz->esq->pai = arvore->raiz;
				if(aux->pai->esq == NULL){
					arvore->raiz->esq->dir = NULL;
					arvore->raiz->esq->esq = NULL;
				}else
					arvore->raiz->esq->dir = NULL;
				arvore->raiz = arvore->raiz->dir;
				Cont++;
				balancearEsq(arvore);
				return
			}else{
				arvore->raiz = arvore->raiz->dir;
				Cont++;
				balancearEsq(arvore);
				return;
			}


	}else{ //{(arvore->raiz->esq->alt = arvore->raiz->esq->altdireita)}
				arvore->raiz = arvore->raiz->esq;
				Cont = 1;
				balancearEsq(arvore);
				while(Cont != 0){
					arvore->raiz = arvore->raiz->pai;
				}

			}

		}else{//arvore->raiz->esq == NULL (e o direito NAO e nulo)
			arvore->raiz->dir->altesquerda == 0;
			int calcB = arvore->raiz->dir - arvore->raiz->dir->altesquerda;
			if(calcB <= -2 || calcB >= 2){
				arvore->raiz = arvore->raiz->dir;
				TpNodo *aux = arvore->raiz;
				arvore->raiz->pai = arvore->raiz->pai->pai;
				arvore->raiz->esq = aux->pai;
				arvore->raiz->pai->esq = arvore->raiz;
				arvore->raiz->esq->pai = arvore->raiz;
				arvore->raiz->esq->dir = NULL;
				arvore->raiz->esq->esq = NULL;
				arvore->raiz = arvore->raiz->dir;
				balancearEsq(arvore);
				return
			}else{
				arvore->raiz = arvore->raiz->dir;
				balancearEsq(arvore);
				return;
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
				while(arvore->raiz->pai != NULL){
					if(arvore->raiz->pai->altura == arvore->raiz->altura){
						TpNodo prev = (TpNodo*)malloc(sizeof(TpNodo));
						prev = arvore->raiz;
						arvore->raiz = arvore->raiz->pai;
						arvore->raiz->altura = prev->altura + 1;
					} else{
						arvore->raiz = arvore->raiz->pai;
					}
				}
				break;
			case 2:
				break;
			default:
				printf("opção invalida!");
				break;
			}
	}while(n!=0);


}
