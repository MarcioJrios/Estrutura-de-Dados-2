#include<stdio.h>
#include<stdlib.h>

int Cont;
typedef struct _nodo{
	int chave;
	int alt, nivel;
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
			nodo->alt = 0;
			nodo->nivel = 0;
			nodo->altdireita = 0;
			nodo->altesquerda = 0;
			nodo->esq = NULL;
			nodo->dir = NULL;
			nodo->pai = NULL;
			arvore->raiz = nodo;
			arvore->NDir = 0;
			arvore->NEsq = 0;
	}else	if(key == arvore->raiz->chave){
			printf("Chave ja existente!");
			return 0;
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
				nodo->alt = 0;
				nodo->nivel = arvore->raiz->nivel + 1;
				arvore->raiz->dir = nodo;
				arvore->raiz = arvore->raiz->dir;
				if(arvore->NDir < arvore->raiz->nivel)
					arvore->NDir = arvore->raiz->nivel;
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
					nodo->alt = 0;
					nodo->nivel = arvore->raiz->nivel + 1;
					arvore->raiz->esq = nodo;
					arvore->raiz = arvore->raiz->esq;
					if(arvore->NEsq < arvore->raiz->nivel)
						arvore->NEsq = arvore->raiz->nivel;
			}
		}
}

void balancearDir(TpArvore *arvore){
		if(arvore->raiz->esq == NULL && arvore->raiz->dir == NULL){//Se estiver em uma folha finaliza
			return 0;
		}else if(arvore->raiz->esq != NULL){//Verifica se os filhos sao nulos para fazer a comparação de altura
			if(arvore->raiz->dir == NULL)
				arvore->raiz->esq->altdireita = 0;
			else
				arvore->raiz->esq->altdireita = arvore->raiz->dir->alt;
			if(arvore->raiz->esq->alt > arvore->raiz->esq->altdireita){//se a altura do filho esquerdo for maior que o direito
				int calcB = arvore->raiz->esq->alt - arvore->raiz->esq->altdireita;
				if(calcB <= -2 || calcB >= 2){//Caso do joelho
					arvore->raiz = arvore->raiz->esq;
					TpNodo *aux = arvore->raiz;
					arvore->raiz->pai = arvore->raiz->pai->pai;
					arvore->raiz->pai->dir = arvore->raiz;
					arvore->raiz->dir = aux->pai;
					arvore->raiz->dir->pai = arvore->raiz;
					if(aux->pai->dir == NULL){
						arvore->raiz->dir->dir = NULL;
						arvore->raiz->dir->esq = NULL;
					}else
						arvore->raiz->dir->esq = NULL;
					//avança para o proximo no com maior altura e executa novamente a verificação
					arvore->raiz = arvore->raiz->esq;
					Cont++;
					balancearEsq(arvore);
					return 0;
				}else{
					//Se esse nó esta balanceado, move para o proximo e executa novamente a verificação
					arvore->raiz = arvore->raiz->esq;
					Cont++;
					balancearEsq(arvore);
					return 0;
					}
			}else if(arvore->raiz->esq->alt < arvore->raiz->esq->altdireita){//Caso do left left
				int calcB = arvore->raiz->esq->alt - arvore->raiz->esq->altdireita;
				if(calcB <= -2 || calcB >= 2){
					arvore->raiz = arvore->raiz->dir;
					TpNodo *aux = arvore->raiz;
					arvore->raiz->pai = arvore->raiz->pai->pai;
					arvore->raiz->esq = aux->pai;
					arvore->raiz->pai->dir = arvore->raiz;
					arvore->raiz->esq->pai = arvore->raiz;
					if(aux->pai->esq == NULL){
						arvore->raiz->esq->dir = NULL;
						arvore->raiz->esq->esq = NULL;
					}else
						arvore->raiz->esq->dir = NULL;
					arvore->raiz = arvore->raiz->dir;
					Cont++;
					balancearEsq(arvore);
					return 0;
				}else{
					arvore->raiz = arvore->raiz->dir;
					Cont++;
					balancearEsq(arvore);
					return 0;
				}
		}else{ //{(arvore->raiz->esq->alt == arvore->raiz->esq->altdireita)}
					arvore->raiz = arvore->raiz->esq;
					Cont = 1;
					balancearEsq(arvore);
					while(Cont != 0){
						arvore->raiz = arvore->raiz->pai;
					}
					Cont = 1;
					balancearDir(arvore);
					while(Cont != 0){
						arvore->raiz = arvore->raiz->pai;
					}
					return 0;
				}
			}else{//arvore->raiz->esq == NULL (e o direito NAO e nulo)
				arvore->raiz->dir->altesquerda == 0;
				int calcB = arvore->raiz->dir->alt - arvore->raiz->dir->altesquerda;
				if(calcB <= -2 || calcB >= 2){
					arvore->raiz = arvore->raiz->dir;
					TpNodo *aux = arvore->raiz;
					arvore->raiz->pai = arvore->raiz->pai->pai;
					arvore->raiz->esq = aux->pai;
					arvore->raiz->pai->dir = arvore->raiz;
					arvore->raiz->esq->pai = arvore->raiz;
					arvore->raiz->esq->dir = NULL;
					arvore->raiz->esq->esq = NULL;
					arvore->raiz = arvore->raiz->dir;
					Cont++;
					balancearEsq(arvore);
					return 0;
				}else{
					arvore->raiz = arvore->raiz->dir;
					Cont++;
					balancearEsq(arvore);
					return 0;
				}
			}
	}
void balancearEsq(TpArvore *arvore){
	if(arvore->raiz->esq == NULL && arvore->raiz->dir == NULL){//Se estiver em uma folha finaliza
		return 0;
	}else if(arvore->raiz->esq != NULL){//Verifica se os filhos sao nulos para fazer a comparação de altura
		if(arvore->raiz->dir == NULL)
			arvore->raiz->esq->altdireita = 0;
		else
			arvore->raiz->esq->altdireita = arvore->raiz->dir->alt;
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
				Cont++;
				balancearEsq(arvore);
				return 0;
			}else{
				//Se esse nó nao esta balanceado, move para o proximo e execura novamente a verificação
				arvore->raiz = arvore->raiz->esq;
				Cont++;
				balancearEsq(arvore);
				return 0;
				}
		}else if(arvore->raiz->esq->alt < arvore->raiz->esq->altdireita){//Caso do joelho
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
				return 0;
			}else{
				arvore->raiz = arvore->raiz->dir;
				Cont++;
				balancearEsq(arvore);
				return 0;
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
			int calcB = arvore->raiz->dir->alt - arvore->raiz->dir->altesquerda;
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
				Cont++;
				balancearDir(arvore);
				return 0;
			}else{
				arvore->raiz = arvore->raiz->dir;
				Cont++;
				balancearDir(arvore);
				return 0;
				}
			}
	}
void *balancear(TpArvore *arvore){
		if(arvore->raiz->esq->alt - arvore->raiz->dir->alt <=2){
			arvore->raiz = arvore->raiz->dir;
			TpNodo *aux = arvore->raiz;
			arvore->raiz->nivel = 0;
			arvore->raiz->esq = arvore->raiz->pai;
			arvore->raiz->pai = NULL;
			arvore->raiz->esq->dir = aux->esq;
			return 0;
		}else if(arvore->raiz->esq->alt - arvore->raiz->dir->alt >=2){
			arvore->raiz = arvore->raiz->esq;
			TpNodo *aux = arvore->raiz;
			arvore->raiz->nivel = 0;
			arvore->raiz->dir = arvore->raiz->pai;
			arvore->raiz->pai = NULL;
			arvore->raiz->dir->esq = aux->esq;
			return 0;
		}else{
			return 0;
		}
}

void imprimir(TpNodo *x){
  if(x->dir != NULL && x->esq != NULL ){
    imprimir(x->dir);
    imprimir(x->esq);
    printf("\nNodo : %d \n",x->chave);
    if(x->pai == NULL){
      printf("Esquerda : %d \n",x->esq->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Esquerda : %d \n",x->esq->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }

  }else if(x->dir != NULL && x->esq == NULL){
    imprimir(x->dir);
    printf("\nNodo : %d \n",x->chave);
    if(x->pai == NULL){
      printf("Direita : %d \n",x->dir->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }
    return;
  }else if(x->dir == NULL && x->esq != NULL){
    imprimir(x->esq);
    printf("\nNodo : %d \n",x->chave);
    if(x->pai == NULL){
      printf("Esquerda : %d \n",x->esq->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Esquerda : %d \n",x->esq->chave);
      return;
    }
  }else if(x->dir == NULL && x->esq == NULL){
    printf("\nNodo : %d \n",x->chave);
    if(x->pai != NULL){
      printf("Pai : %d \n",x->pai->chave);
    }
      return;
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
					if(arvore->raiz->pai->alt == arvore->raiz->alt){
						TpNodo *prev = (TpNodo*)malloc(sizeof(TpNodo));
						prev = arvore->raiz;
						arvore->raiz = arvore->raiz->pai;
						arvore->raiz->alt = prev->alt + 1;
					} else{
						arvore->raiz = arvore->raiz->pai;
					}
				}
				do{
					balancear(arvore);
					balancearEsq(arvore);
					balancearDir(arvore);
				}while(arvore->raiz->esq->alt - arvore->raiz->dir->alt <=2 || arvore->raiz->esq->alt - arvore->raiz->dir->alt >=2);

				system("clear");
				printf("\nChave inserida com sucesso!\n\n");
				break;
			case 2:
				system("clear");
				imprimir(arvore->raiz);
				break;
			case 0:
				break;
			default:
				printf("opção invalida!");
				break;
			}
	}while(n!=0);


}
