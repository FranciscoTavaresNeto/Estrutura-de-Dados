#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Estrutura do Nó (cada elemento da lista)
typedef struct no {
int valor;
struct no *proximo;
} No;

// Estrutura de Controle da LSE
typedef struct lse {
No *primeiro;
int qtd;
} LSE;

// Inicializa a lista
void inicializaListaLSE(LSE *ls) {
ls->primeiro = NULL;
ls->qtd = 0;
}

// Insere ordenado mantendo ordem crescente
void inserirOrdenado(LSE *lista, int valor) {
No *novo = (No *)malloc(sizeof(No));
if (novo == NULL) {
printf("Erro de alocacao de memoria!\n");
return;
}
novo->valor = valor;
novo->proximo = NULL;

// Se a lista estiver vazia ou o valor for menor que o primeiro
if (lista->primeiro == NULL || lista->primeiro->valor >= valor) {
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
} else {
    // Percorre para encontrar a posição correta
    No *atual = lista->primeiro;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}
lista->qtd++;


}

// Exibe a lista no formato 50 linhas x 20 colunas
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

// Analisa e exibe os dados estatisticos
void calcularEstatisticas(LSE *lista) {
if (lista->primeiro == NULL) {
printf("Lista vazia. Sem dados para analise.\n");
return;
}

int menor = lista->primeiro->valor; // Como esta ordenada, o primeiro e o menor
int maior = lista->primeiro->valor;
double soma = 0;
int duplicados = 0;

No *atual = lista->primeiro;

// Primeira passagem: soma, acha o maior e conta duplicados
while (atual != NULL) {
    if (atual->valor > maior) {
        maior = atual->valor; // Alternativamente, poderiamos so pegar o ultimo no
    }
    soma += atual->valor;

    // Se o proximo no for igual ao atual, temos uma duplicata
    if (atual->proximo != NULL && atual->valor == atual->proximo->valor) {
        duplicados++;
    }

    atual = atual->proximo;
}

double media = soma / lista->qtd;

// Segunda passagem: calcular desvio padrao
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

// Libera toda a memoria alocada para os nos da lista
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
// 1. Criar e inicializar a Lista LSE
LSE *listaNumeros = (LSE *)malloc(sizeof(LSE));
inicializaListaLSE(listaNumeros);

// Inicializar semente aleatoria
srand(time(NULL));

// 2. Gerar e inserir 1000 numeros aleatorios ordenados
for (int i = 0; i < 1000; i++) {
    int numero = rand() % 1001; // Valores entre 0 e 1000
    inserirOrdenado(listaNumeros, numero);
}

// 3. Exibir a lista formatada (50x20)
exibirMatriz(listaNumeros);

// 4. Analise Estatistica
calcularEstatisticas(listaNumeros);

// 5. Liberar Memoria da Heap
liberarLista(listaNumeros);
free(listaNumeros); // Libera o controle da LSE

printf("\nMemoria liberada com sucesso!\n*** Fim do Programa ***\n");

return 0;


}