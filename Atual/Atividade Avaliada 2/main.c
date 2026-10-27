#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct no {
int valor;
struct no *proximo;
} No;


typedef struct lse {
No *primeiro;
int qtd;
} LSE;


void inicializaListaLSE(LSE *ls) {
ls->primeiro = NULL;
ls->qtd = 0;
}

void inserirOrdenado(LSE *lista, int valor) {
No *novo = (No *)malloc(sizeof(No));
if (novo == NULL) {
printf("Erro de alocacao de memoria!\n");
return;
}
novo->valor = valor;
novo->proximo = NULL;

if (lista->primeiro == NULL || lista->primeiro->valor >= valor) {
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
} else {
    No *atual = lista->primeiro;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}
lista->qtd++;


}

void exibirMatriz(LSE *lista) {
No *aux = lista->primeiro;
int contador = 0;

printf("\n=== Matriz de Elementos (50x20) ===\n");
while (aux != NULL) {
    printf("%4d ", aux->valor);
    contador++;

    if (contador % 20 == 0) {
        printf("\n");
    }
    aux = aux->proximo;
}
printf("===================================\n");


}

void calcularEstatisticas(LSE *lista) {
if (lista->primeiro == NULL) {
printf("Lista vazia. Sem dados para analise.\n");
return;
}

int menor = lista->primeiro->valor;
int maior = lista->primeiro->valor;
double soma = 0;
int duplicados = 0;

No *atual = lista->primeiro;


while (atual != NULL) {
    if (atual->valor > maior) {
        maior = atual->valor;
    }
    soma += atual->valor;

    if (atual->proximo != NULL && atual->valor == atual->proximo->valor) {
        duplicados++;
    }

    atual = atual->proximo;
}

double media = soma / lista->qtd;

double soma_quadrados = 0;
atual = lista->primeiro;
while(atual != NULL) {
    soma_quadrados += pow(atual->valor - media, 2);
    atual = atual->proximo;
}
double desvio_padrao = sqrt(soma_quadrados / lista->qtd);

printf("\n--- Analise Estatistica ---\n");
printf("Quantidade total: %d elementos\n", lista->qtd);
printf("Menor valor armazenado: %d\n", menor);
printf("Maior valor armazenado: %d\n", maior);
printf("Media aritmetica: %.2lf\n", media);
printf("Desvio padrao: %.2lf\n", desvio_padrao);
printf("Quantidade de repetidos (duplicados): %d\n", duplicados);


}

void liberarLista(LSE *lista) {
No *atual = lista->primeiro;
No *proximo_no;

while (atual != NULL) {
    proximo_no = atual->proximo;
    free(atual);
    atual = proximo_no;
}
lista->primeiro = NULL;
lista->qtd = 0;


}

int main() {
LSE *listaNumeros = (LSE *)malloc(sizeof(LSE));
inicializaListaLSE(listaNumeros);

srand(time(NULL));

for (int i = 0; i < 1000; i++) {
    int numero = rand() % 1001;
    inserirOrdenado(listaNumeros, numero);
}

exibirMatriz(listaNumeros);

calcularEstatisticas(listaNumeros);

liberarLista(listaNumeros);
free(listaNumeros);

printf("\nMemoria liberada com sucesso!\n*** Fim do Programa ***\n");

return 0;


}