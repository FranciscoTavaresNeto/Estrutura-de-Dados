#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar alunos
typedef struct aluno
{
    char nome[100];
    int idade;
    int matricula;
    struct aluno *proximo;
} Aluno;

// Estrutura para gerenciar a lista
typedef struct lse
{
    Aluno *primeiro;
    int n_elementos;
    char nome[50];
} LSE;

void inicializaLista(LSE *lista, char nome[])
{
    // recebe a estrutura de lista e preenche os parâmetros
    lista->primeiro = NULL;
    lista->n_elementos = 0;
    strcpy(lista->nome, nome);
}

void insereInicio(LSE *lista, Aluno *novo)
{
    // insere um elemento no início da lista (primeiro)
    if (lista->primeiro == NULL)
        // Lista Vazia
        novo->proximo = NULL;
    else
        // Lista com elementos
        novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->n_elementos++;
}

void insereInicioReduzida(LSE *lista, Aluno *novo)
{
    // insere um elemento no início da lista forma reduzida
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->n_elementos++;
}

void insereFim(LSE *lista, Aluno *novo)
{
    // insere um novo elemento no fim da lista (último)
    novo->proximo = NULL;
    if (lista->primeiro == NULL)
        // Lista Vazia
        lista->primeiro = novo;
    else
    {
        // Lista com elementos
        Aluno *aux = lista->primeiro;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    lista->n_elementos++;
}

void inserePosicao(LSE *lista, Aluno *novo, int posicao);

Aluno *removeInicio(LSE *lista)
{
    // remove o primeiro elemento da lista
    Aluno *removido = lista->primeiro;
    if (removido != NULL)
    {
        // lista com um ou mais elementos//
        lista->primeiro = lista->primeiro->proximo;
        lista->n_elementos--;
        removido->proximo = NULL;
    }
    else
    {
        printf("\n\t\t  **** Lista Vazia! ****\n");
    }
    return removido;
}

Aluno *removeFim(LSE *lista);

Aluno *removePosicao(LSE *lista, int posicao);

void cadastraAluno(Aluno *aluno, char nome[], int idade, int matricula)
{
    // recebe um ponteiro de aluno e atribui os valores aos membros
    strcpy(aluno->nome, nome);
    aluno->idade = idade;
    aluno->matricula = matricula;
    aluno->proximo = NULL;
}

Aluno *informaNovoAluno()
{
    // aloca dinamicamente um novo aluno, preenche os dados e retorna o endereço
    Aluno *novo = (Aluno *)(malloc(sizeof(Aluno)));
    printf("\nInforme o nome do Aluno:");
    scanf("%s", novo->nome);
    printf("Informe a idade do Aluno:");
    scanf("%d", &novo->idade);
    printf("Informe a matricula do Aluno:");
    scanf("%d", &novo->matricula);
    return novo;
}

void mostraAluno(Aluno novo)
{
    // mostra os dados de um elemento Aluno
    printf("\t\tAluno - Nome: %s Idade %d Matricula %d\n", novo.nome, novo.idade, novo.matricula);
}

void mostraAlunoCT(Aluno novo, int n)
{
    // mostra os dados de um elemento Aluno
    printf("\t\tAluno %d - Nome: %s Idade %d Matricula %d\n", n, novo.nome, novo.idade, novo.matricula);
}

void mostraLista(LSE lista)
{
    // mostra todos elementos da lista
    int ct = 0;
    printf("\nMostra LSE de %s; \n", lista.nome);
    printf("\tInício da Lista!\n");
    Aluno *removido; // ponteiro auxiliar
    removido = lista.primeiro;
    while (removido != NULL)
    {
        mostraAlunoCT(*removido, ct++);
        removido = removido->proximo;
    }
    printf("\tFim da Lista!\n");
    printf("\nTotal de alunos na Lista de %s = %d \n", lista.nome, lista.n_elementos);
}

void mostraLista2(Aluno *aluno)
{
    // mostra todos elementos da lista com o uso de recursão na função
    if (aluno != NULL)
    {
        mostraAluno(*aluno);
        mostraLista2(aluno->proximo);
    }
}

void menuTesteLista(LSE *lista)
{
    int op = 0, posicao = 0;
    Aluno *aux = NULL;
    printf("\nMenu de operacoes sobre um LSE:\n");
    printf("\n\t1 - Insere no Inicio:");
    printf("\n\t2 - Insere no Fim:");
    printf("\n\t3 - Insere na Posicao:");
    printf("\n\t4 - Remove no Inicio:");
    printf("\n\t5 - Remove no Fim:");
    printf("\n\t6 - Remove na Posicao:");
    printf("\n\t7 - Mostra Lista:");
    printf("\n\t8 - Mostra Aluno na Posicao:");
    printf("\n\t9 - Apaga Lista:");
    printf("\n\t10 - Localiza um Aluno pelo Nome");
    printf("\n\t0 - Para Sair da Funcao Menu:");
    printf("\n\tInforme a opcao:");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        printf("\n\tFuncao Insere no Inicio!!");
        insereInicio(lista, informaNovoAluno());
        break;
    case 2:
        printf("\n\tFuncao Insere no Fim!!");
        insereFim(lista, informaNovoAluno());
        break;
    case 3:
        printf("\n\tFuncao Insere na Posicao!!");
        printf("\n\t\tInforme a posicao nova:");
        scanf("%d", &posicao);
        printf("\n Posicao = %d", posicao);
        // inserePosicao(lista, informaNovoAluno(), posicao);
        break;
    case 4:
        printf("\n\tFuncao Remove no Inicio:");
        aux = removeInicio(lista);
        if (aux != NULL)
        {
            mostraAluno(*aux);
            free(aux);
        }
        break;
    case 5:
        printf("\n\tFuncao Remove no Fim:");
        // aux = removeFim(lista);
        // if (aux != NULL)
        // {
        //     mostraAluno(*aux);
        //     free(aux);
        // }
        break;
    case 6:
        printf("\n\tFuncao Remove na Posicao!!");
        printf("\n\t\tInforme a posicao:");
        scanf("%d", &posicao);
        // aux = removePosicao(lista, posicao);
        // if (aux != NULL)
        // {
        //     mostraAluno(*aux);
        //     free(aux);
        // }
        break;
    case 7:
        // printf("\n\nMostra Lista de %s!!!", lista->nome);
        mostraLista(*lista);
        break;
        //     case 8:
        //         printf("\n\tFuncao Mostra um Aluno na Posicao - Pos!!");
        //         printf("\n\t\tInforme a posicao:");
        //         break;
        //     case 9:
        //         printf("\n\tFuncao Apaga toda Lista!");
        //         break;

    case 0:
        printf("\n\n*** Fim do Programa!!! ***\n");
        break;
    default:
        printf("\n\n*** Opcao Invalida!!! ***\n");
    }
    if (op > 0 && op <= 10)
    {
        menuTesteLista(lista);
    }
}

int main()
{

    printf("Exemplo - Lista Simplesmente Encadeada - Lista de Alunos\n");

    // Declaração de ponteiro de Lista
    LSE matematica;

    // Inicialização da Lista
    inicializaLista(&matematica, "Matematica");

    // Executa funções de lista
    menuTesteLista(&matematica);

    exit(0);
}
