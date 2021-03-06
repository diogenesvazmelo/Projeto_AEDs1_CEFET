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
    { printf("%d ", Aux -> Item.Chave);
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

    while (i < QT_ELEMENTOS_BUSCADOS && Aux != NULL){
        vet_temp[i] = Aux -> Item.Chave;
        Aux = Aux -> Prox;
        i++;
    }
    int a = verifica_igualdade(vet_temp, SEQUENCIA_BUSCADA);
    return a;
}


int percorre_lista(TipoLista Lista){
    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL){
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
        if (a != b){
            item_redux.Chave = Aux -> Item.Chave;
            Insere(item_redux, &Lista_Reduzida);
            a = item_redux.Chave;
        }
    }
}

/* ====================== Minhas funções parte 2 ============================ */

double p_medio(TipoLista Lista){

    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;

    int num;
    int contador = -2;

    int save[2] = {-1, -1};
    int save2[5] = {-1, -1, -1, -1, -1};

    while (Aux != NULL){
        contador++;
        num =  Aux -> Item.Chave;


        if (save2[0] == 0 && save2[1] == 255 && save2[2] == 128 && save2[3] == 255 && save2[4] == 0){
//            printf("\nNivel 5 (entrou) - num: %d", num);
            if (num != 0){
                return (save[0] + save[1])/2;
            }
            else{
                //save[1] = contador;
            }
        }

        if (save2[0] == 0 && save2[1] == 255 && save2[2] == 128 && save2[3] == 255){
//            printf("\nNivel 5 (entrou) - num: %d", num);
            if (num == 0){
                //save[1] = contador;
                save2[4] = 0;
                //return posicao_buscada;
            }
            else if (num == 255){
            }
            else{
                save2[0] = -1;
                save2[1] = -1;
                save2[2] = -1;
                save2[3] = -1;
            }
        }

        else if (save2[0] == 0 && save2[1] == 255 && save2[2] == 128){
            if (num == 255){
//                printf("\nNivel 4 - %d", num);
                save2[3] = num;

//                printf("\n\nsave2[0] - %d", save2[0]);
//                printf("\nsave2[1] - %d", save2[1]);
//                printf("\nsave2[2] - %d", save2[2]);
//                printf("\nsave2[3] - %d", save2[3]);
//                printf("\nsave2[4] - %d\n\n", save2[4]);
            }
            else if (num == 128){
                save[1] = contador;
            }
            else{
                save2[0] = -1;
                save2[1] = -1;
                save2[2] = -1;
            }
        }

        else if (save2[0] == 0 && save2[1] == 255){
            if (num == 128){
//                printf("\nNivel 3 - %d", num);
                save2[2] = num;
                save[0] = contador;
            }
            else if (num == 255){
            }
            else{
                save2[0] = -1;
                save2[1] = -1;
            }
        }

        else if (save2[0] == 0){
            if (num == 255){
//                printf("\nNivel 2 - %d", num);
                save2[1] = num;
            }
            else if (num == 0){
            }
            else{
                save2[0] = -1;
            }
        }

        else if (num == 0){
            //save[0] = contador;
//            printf("\nNivel 1 - %d", num);
            save2[0] = num;
            //menor_contador_possivel = contador + 1;
        }
        else{
            save2[0] = -1;
        }

        Aux = Aux -> Prox;
    }
    return (save[0] + save[1])/2;
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



    int n = -1;
    fscanf(arquivo, "%d", &n);
    if (n <= 0){
        return 0;
    }

    int n_cont = 0;

    double vetor_pontos_medios[n];

    while (n_cont < n){

        /// Lê o arquivo com as entradas e armazena os valores na lista

        TipoLista lista;
        TipoItem item;

        /*Inicia a lista, vazia */
        FLVazia(&lista);

        int l = 0;
        fscanf(arquivo, "%d", &l);

        int numero;
        int q = 0;
        //while(!feof(arquivo)){
        while(q < l){
            fscanf(arquivo, "%d", &numero);
            q++;
            /*Insere cada chave na lista */
            item.Chave = numero;
            //printf("%d\n", numero);
            Insere(item, &lista);
        }
        Imprime(lista);

        /// Cria uma versão reduzida da lista anterior, na qual são
        /// excluídos os valores contíguos repetidos

        TipoLista lista_reduzida;
        FLVazia(&lista_reduzida);
        reduz_lista(lista, lista_reduzida, q);
    //    Imprime(lista_reduzida);

        bool se_encontrado = false;
        if (percorre_lista(lista_reduzida) == 1){
            printf("Resultado: Padrao encontrado.");
            se_encontrado = true;
        }
        else{
            printf("Resultado: Padrao nao encontrado.");
        }


        /// Se o padrão for encontrado
        if (se_encontrado == true){
            double ponto_medio = p_medio(lista);
            vetor_pontos_medios[n_cont] = ponto_medio;
            printf("\nPonto Medio: %0.lf", ponto_medio);
            printf("\nPonto Medio: %0.lf", vetor_pontos_medios[n_cont]);

            printf("\n\n\n");
            //Imprime(lista);
        }
        else{
            vetor_pontos_medios[n_cont] = -1;
        }

        /// Liberar a memória
//        free(lista);
//        free(item);
//


        n_cont++;

    }

    printf("\n\n\n");

    for (int i = 0; i < n; i++){
        printf("%0.lf\n", vetor_pontos_medios[i]);
    }


    /// Liberar a memória

    //TODO

    return 0;
}
