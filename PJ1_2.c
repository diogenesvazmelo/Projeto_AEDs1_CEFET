#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/* ================== Implementação Ziviani (não alterar) ================== */
/* ========================================================================= */

typedef int TipoChave;

typedef struct {
  int Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL)
  { printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
    return;
  }
  q = p -> Prox;
  *Item = q -> Item;
  p -> Prox = q -> Prox;
  if (p -> Prox == NULL) Lista -> Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL)
    { printf("%d\n", Aux -> Item.Chave);
      Aux = Aux -> Prox;
    }
}

/* ========================================================================== */
/* ====================== Fim da Implementação Ziviani ====================== */


int SEQUENCIA_BUSCADA[] = {0, 255, 128, 255, 0};
int QT_ELEMENTOS_BUSCADOS = 5;

/* ====================== Minhas funções ==================================== */

void imprime_vetor(int *ptr, int tamanho){
    printf("\n\nImprimindo o vetor: \n\n");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", ptr[i]);
    }
    printf("\n\n");
}

int verifica_igualdade(int vetor[], int vetor_buscado[]){
    for (int i = 0; i < 5; i++){
        if (vetor[i] != vetor_buscado[i]){
            return 0;
        }
    }
    return 1;
}

int procura_sequencia(TipoLista Lista, TipoApontador Aux){
    int i = 0;
    int vet_temp[5];
//    printf("\n\nProcurando a sequencia: \n\n");
    //TipoApontador Aux;
    //Aux = Lista.Primeiro -> Prox;
    while (i < QT_ELEMENTOS_BUSCADOS && Aux != NULL){
//        printf("%d\n", Aux -> Item.Chave);
        vet_temp[i] = Aux -> Item.Chave;
        Aux = Aux -> Prox;
        i++;
    }
//    printf("\n\n--------------\n\n");
    int a = verifica_igualdade(vet_temp, SEQUENCIA_BUSCADA);
    return a;
}


int percorre_lista(TipoLista Lista){
//    printf("\n\nPercorrendo a sequencia: \n\n");
    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL){
//        printf("%d\n", Aux -> Item.Chave);
        if (procura_sequencia(Lista, Aux) == 1){
            return 1;
        }
        Aux = Aux -> Prox;
    }
    return 0;
}

void reduz_lista(TipoLista Lista, TipoLista Lista_Reduzida, int q){
    TipoItem item_redux;

    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;

    item_redux.Chave = Aux -> Item.Chave;
    Insere(item_redux, &Lista_Reduzida);

    int a = item_redux.Chave;
    int b = Aux -> Item.Chave;
    /*Insere cada chave na lista */
    for (int i = 0; i < q-1; i++){
        Aux = Aux -> Prox;
        b = Aux -> Item.Chave;
//        printf("%d \n", b);
        if (a != b){
            item_redux.Chave = Aux -> Item.Chave;
            Insere(item_redux, &Lista_Reduzida);
//            printf("Inseriu: %d \n", item_redux.Chave);
            a = item_redux.Chave;
        }
//        else{
//            printf("Else \n");
//        }
    }
//    printf("\n\n\n\n\n");
}

/* ====================== Fim das Minhas funções ============================ */

int main(){
	printf("Digite o nome do arquivo: ");
	char nome_do_arquivo[1000];
	scanf("%s", &nome_do_arquivo[0]);
//    char *nome_do_arquivo = "t2.txt";

    /// Abre o arquivo e verifica se foi ok
	FILE *arquivo;
 	arquivo = fopen(nome_do_arquivo, "r");
	if (arquivo == NULL){
		printf("Erro na abertura do aqruivo\n");
		exit(1);
	}



    /// Lê o arquivo com as entradas e armazena os valores
    int numero;
    int q = 0;
    int *ptr = (int *) realloc(NULL, 0 * sizeof(int));
    while(!feof(arquivo)){
        fscanf(arquivo, "%d", &numero);
        q++;
        ptr = (int *) realloc(ptr, q * sizeof(int));
        ptr[q-1] = numero;
    }

//    imprime_vetor(ptr, q);


    TipoLista lista;
    TipoItem item;
//    TipoApontador p;
//    int i, j, k, n;
    int i;
    FLVazia(&lista);


    /*Insere cada chave na lista */
    for (i = 0; i < q; i++){
        item.Chave = ptr[i];
        Insere(item, &lista);
//        printf("Inseriu: %d \n", item.Chave);
    }
//    Imprime(lista);

    TipoLista lista_reduzida;
    FLVazia(&lista_reduzida);
    reduz_lista(lista, lista_reduzida, q);
//    Imprime(lista_reduzida);


    if (percorre_lista(lista_reduzida) == 1){
        printf("Resultado: Padrao encontrado.");
    }
    else{
        printf("Resultado: Padrao nao encontrado.");
    }




    /// Liberar a memória

    return 0;
}
