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


int SEQUENCIA_BUSCADA[] = {1, 3, 2, 3, 1};
int QT_ELEMENTOS_BUSCADOS = 5;

/* ====================== Minhas funções ==================================== */

void imprime_vetor(int *ptr, int tamanho){
    printf("\n\nImprimindo o vetor: \n\n");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", ptr[i]);
    }
    printf("\n\n");
}

int verifica_igualdade(int vetor[]){
    for (int i = 0; i < 5; i++){
        if (vetor[i] != SEQUENCIA_BUSCADA[i]){
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
    int a = verifica_igualdade(vet_temp);
    return a;
}


int percorre_lista(TipoLista Lista)
{
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

/* ====================== Fim das Minhas funções ============================ */

int main(){
	printf("Digite o nome do arquivo: ");
	char nome_do_arquivo[1000];
	scanf("%s", &nome_do_arquivo[0]);
//    char *nome_do_arquivo = "teste.txt";

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

    //imprime_vetor(ptr, q);


    TipoLista lista;
    TipoItem item;
//    TipoApontador p;
//    int i, j, k, n;
    int i;
    float  tamanho=0;
    FLVazia(&lista);


    /*Insere cada chave na lista */
    for (i = 0; i < q; i++){
        item.Chave = ptr[i];
        Insere(item, &lista);
        tamanho++;
//        printf("Inseriu: %d \n", item.Chave);
    }
//    Imprime(lista);
    if (percorre_lista(lista) == 1){
        printf("Resultado: Padrao encontrado.");
    }
    else{
        printf("Resultado: Padrao nao encontrado.");
    }




    /// Liberar a memória

    return 0;
}
