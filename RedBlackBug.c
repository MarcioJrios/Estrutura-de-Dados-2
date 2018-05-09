#include<stdio.h>
#include<stdlib.h>

typedef struct _nodo{
  int chave;
  int nivel;
  int cor;
  struct _nodo *esq;
  struct _nodo *dir;
  struct _nodo *pai;
} TpNodo;
typedef struct _arvore{
  TpNodo *raiz;
  TpNodo *sentinela;
  int BlackHeight;
  int nivelMax;
} TpArvore;

TpArvore *inicializa(){//aloca memoria para inicializar a arvore
  TpArvore *arvore=(TpArvore *)malloc(sizeof(TpArvore));
  TpNodo *sentinela=(TpNodo *)malloc(sizeof(TpNodo));
  arvore->raiz= NULL;
  arvore->nivelMax = 0;
  arvore->BlackHeight = 0;
  arvore->sentinela = sentinela;
  arvore->sentinela->chave = -1;
  arvore->sentinela->cor = 1;
  arvore->sentinela->pai = NULL;
  arvore->sentinela->esq = NULL;
  arvore->sentinela->dir = NULL;
  return arvore;
}

void inserir(int key, TpArvore *arvore){
  if(arvore->raiz == NULL){
    TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
    nodo->chave = key;
    nodo->cor = 1;
    nodo->nivel = 0;
    nodo->esq = NULL;
    nodo->dir = NULL;
    nodo->pai = NULL;
    arvore->raiz = nodo;
    arvore->BlackHeight = 1;
  }else if(key == arvore->raiz->chave){
        printf("Chave ja existente!");
        return;
  }else if(key > arvore->raiz->chave){
    if(arvore->raiz->dir != NULL){
      arvore->raiz = arvore->raiz->dir;
      inserir(key, arvore);
      return;
    }else{
      TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
      nodo->chave = key;
      nodo->cor = 0;
      nodo->pai = arvore->raiz;
      nodo->esq = NULL;
      nodo->dir = NULL;
      nodo->nivel = arvore->raiz->nivel + 1;
      arvore->raiz->dir = nodo;
      arvore->raiz = arvore->raiz->dir;
    }
    }else {//key < raiz.chave
      if(arvore->raiz->esq != NULL){
        arvore->raiz = arvore->raiz->esq;
        inserir(key, arvore);
        return;
      }else{
        TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
        nodo->chave = key;
        nodo->cor = 0;
        nodo->pai = arvore->raiz;
        nodo->esq = NULL;
        nodo->dir = NULL;
        nodo->nivel = arvore->raiz->nivel + 1;
        arvore->raiz->esq = nodo;
        arvore->raiz = arvore->raiz->esq;
      }
    }
  }

int BlackH(TpArvore *arvore){
  int b = 1;
  TpNodo *a = (TpNodo *)malloc(sizeof(TpNodo));
  a = arvore->raiz;
  while(arvore->raiz->pai != NULL){
    if(arvore->raiz->pai->cor == 1){
      b++;
      arvore->raiz = arvore->raiz->pai;
    }else{
      arvore->raiz = arvore->raiz->pai;
    }
  }
  arvore->raiz = a;
  return b;
}

void Rcase1(TpArvore *arvore){
  arvore->raiz->pai->pai->cor = 0;
  arvore->raiz->pai->pai->dir->cor = 1;
  arvore->raiz->pai->pai->esq->cor = 1;
  arvore->raiz = arvore->raiz->pai;
}

void Rcase3(TpArvore *arvore){
  TpNodo *nodo = (TpNodo*)malloc(sizeof(TpNodo));
  TpNodo *aux = (TpNodo*)malloc(sizeof(TpNodo));
  TpNodo *aux2 = (TpNodo*)malloc(sizeof(TpNodo));
  aux = arvore->raiz;
  arvore->raiz = arvore->raiz->pai;
  nodo = arvore->raiz;
  if(arvore->raiz->pai->esq != NULL && arvore->raiz->pai->esq == arvore->raiz){
    if(arvore->raiz->pai->pai != NULL){
      aux2 = arvore->raiz->pai->pai;
      aux = arvore->raiz->dir;
      nodo = arvore->raiz->pai;
      arvore->raiz->dir = nodo;
      arvore->raiz->dir->dir = NULL;
      printf("C\n");
      arvore->raiz->dir->esq = aux;
      arvore->raiz->dir->pai = arvore->raiz;
      arvore->raiz->pai = aux2;
      printf("%d\n", arvore->raiz->pai->chave);
      if(arvore->raiz->pai->pai == NULL)
        printf("NULL\n");
      else{}
      if(arvore->raiz->chave < arvore->raiz->pai->chave)
        arvore->raiz->pai->esq = arvore->raiz;
      else
        arvore->raiz->pai->dir = arvore->raiz;

      arvore->raiz->cor = 1;
      arvore->raiz->dir->cor = 0;
      arvore->raiz = arvore->raiz->esq;
    }else{
      aux = arvore->raiz->dir;
      nodo = arvore->raiz->pai;
      arvore->raiz->pai = NULL;
      arvore->raiz->dir = nodo;
      arvore->raiz->dir->dir = NULL;
      arvore->raiz->dir->esq = aux;
      arvore->raiz->dir->pai = arvore->raiz;
      arvore->raiz->cor = 1;
      arvore->raiz->dir->cor = 0;
      arvore->raiz = arvore->raiz->esq;
  }
  }else if(arvore->raiz->pai->dir != NULL && arvore->raiz->pai->dir == arvore->raiz){
    if(arvore->raiz->pai->pai != NULL){
      aux = arvore->raiz->esq;
      nodo = arvore->raiz->pai;
      arvore->raiz->pai = arvore->raiz->pai->pai;
      if(arvore->raiz->chave > arvore->raiz->pai->chave)
        arvore->raiz->pai->dir = arvore->raiz;
      else
        arvore->raiz->pai->esq = arvore->raiz;
      arvore->raiz->esq = nodo;
      arvore->raiz->esq->esq = NULL;
      arvore->raiz->esq->dir = aux;
      arvore->raiz->esq->pai = arvore->raiz;
      arvore->raiz->cor = 1;
      arvore->raiz->esq->cor = 0;
      arvore->raiz = arvore->raiz->dir;

    }else{
      aux = arvore->raiz->dir;
      nodo = arvore->raiz->pai;
      arvore->raiz->pai = NULL;
      arvore->raiz->esq = nodo;
      arvore->raiz->esq->esq = NULL;
      arvore->raiz->esq->dir = aux;
      arvore->raiz->esq->pai = arvore->raiz;
      arvore->raiz->cor = 1;
      arvore->raiz->esq->cor = 0;
      arvore->raiz = arvore->raiz->dir;
    }
  }
}

void Rcase2(TpArvore *arvore){
  TpNodo *aux = (TpNodo*)malloc(sizeof(TpNodo));
  TpNodo *aux2 = (TpNodo*)malloc(sizeof(TpNodo));
  aux = arvore->raiz->pai;
  if(arvore->raiz->pai->pai->chave > arvore->raiz->chave){
      arvore->raiz->pai = arvore->raiz->pai->pai;
      if(arvore->raiz->chave < arvore->raiz->pai->chave)
        arvore->raiz->pai->esq = arvore->raiz;
      else
        arvore->raiz->pai->dir = arvore->raiz;
      arvore->raiz->esq = aux;
      arvore->raiz->esq->pai = arvore->raiz;
      arvore->raiz->esq->dir = NULL;
      printf("%d\n", arvore->raiz->pai->pai->chave);
      arvore->raiz = arvore->raiz->esq;
      /*arvore->raiz->esq = arvore->raiz->pai;
      arvore->raiz->pai = arvore->raiz->pai->pai;
      arvore->raiz->esq->pai = arvore->raiz;
      arvore->raiz->esq->dir = NULL;
      arvore->raiz->pai->esq = arvore->raiz;*/
      printf("D\n");
      Rcase3(arvore);
      printf("A\n");
    }else{
      arvore->raiz->pai->pai = arvore->raiz;
      arvore->raiz->pai->esq = NULL;
      arvore->raiz->dir = arvore->raiz->pai;
      arvore->raiz->pai = aux->pai;
      arvore->raiz->pai->dir = arvore->raiz;
      arvore->raiz = arvore->raiz->dir;
      printf("E\n");
      Rcase3(arvore);
  }

}

void imprimir(TpNodo *nodo){
  if(nodo->dir != NULL && nodo->esq != NULL ){
    imprimir(nodo->dir);
    imprimir(nodo->esq);
    printf("\nNodo : %d \n",nodo->chave);
    printf("Cor : %d \n", nodo->cor);
    if(nodo->pai == NULL){
      printf("Esquerda : %d \n",nodo->esq->chave);
      printf("Cor : %d \n", nodo->esq->cor);
      printf("Direita : %d \n",nodo->dir->chave);
      printf("Cor : %d \n", nodo->dir->cor);
      return;
    }else{
      printf("Pai : %d \n",nodo->pai->chave);
      printf("Cor : %d \n", nodo->pai->cor);
      printf("Esquerda : %d \n",nodo->esq->chave);
      printf("Cor : %d \n", nodo->esq->cor);
      printf("Direita : %d \n",nodo->dir->chave);
      printf("Cor : %d \n", nodo->dir->cor);
      return;
    }

  }else if(nodo->dir != NULL && nodo->esq == NULL){
    imprimir(nodo->dir);
    printf("\nNodo : %d \n",nodo->chave);
    printf("Cor : %d \n", nodo->cor);
    if(nodo->pai == NULL){
      printf("Direita : %d \n",nodo->dir->chave);
      printf("Cor : %d \n", nodo->dir->cor);
      return;
    }else{
      printf("Pai : %d \n",nodo->pai->chave);
      printf("Cor : %d \n", nodo->pai->cor);
      printf("Direita : %d \n",nodo->dir->chave);
      printf("Cor : %d \n", nodo->dir->cor);
      return;
    }
    return;
  }else if(nodo->dir == NULL && nodo->esq != NULL){
    imprimir(nodo->esq);
    printf("\nNodo : %d \n",nodo->chave);
    printf("Cor : %d \n", nodo->cor);
    if(nodo->pai == NULL){
      printf("Esquerda : %d \n",nodo->esq->chave);
      printf("Cor : %d \n", nodo->esq->cor);
      return;
    }else{
      printf("Pai : %d \n",nodo->pai->chave);
      printf("Cor : %d \n", nodo->pai->cor);
      printf("Esquerda : %d \n",nodo->esq->chave);
      printf("Cor : %d \n", nodo->esq->cor);
      return;
    }
  }else if(nodo->dir == NULL && nodo->esq == NULL){
    printf("\nNodo : %d \n",nodo->chave);
    printf("Cor : %d \n", nodo->cor);
    if(nodo->pai != NULL){
      printf("Pai : %d \n",nodo->pai->chave);
      printf("Cor : %d \n", nodo->pai->cor);
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
          printf("U\n");
          if(arvore->raiz->pai->cor == 0 && arvore->raiz->cor == 0){
            printf("U2\n" );
            if(arvore->raiz->chave < arvore->raiz->pai->chave){//verifica se esta a esquerda do pai
              printf("U3\n" );
              if(arvore->raiz->pai->chave < arvore->raiz->pai->pai->chave){//arvore->raiz->pai->pai->esq == arvore->raiz->pai){//verifica se o pai esta a esquerda de seu pai(joelho)
                printf("U4\n" );
                if(arvore->raiz->pai->pai->dir != NULL && arvore->raiz->pai->pai->dir->cor == 0)//verifica a cor do tio
                  Rcase1(arvore);
                else
                  Rcase3(arvore);
                }else if(arvore->raiz->pai->pai->esq != NULL && arvore->raiz->pai->pai->esq->cor == 0)
                  Rcase1(arvore);
                else
                  Rcase2(arvore);
              }else if(arvore->raiz->pai->chave < arvore->raiz->pai->pai->chave){
                if(arvore->raiz->pai->pai->dir != NULL && arvore->raiz->pai->pai->dir->cor == 0)
                  Rcase1(arvore);
                else
                  Rcase2(arvore);
              }else if(arvore->raiz->pai->pai->esq !=NULL && arvore->raiz->pai->pai->esq->cor == 0)
                Rcase1(arvore);
              else
                Rcase3(arvore);
            }
            printf("Certo\n");
            arvore->raiz = arvore->raiz->pai;
            printf("Certo2\n");
        }
        arvore->raiz->cor = 1;
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
