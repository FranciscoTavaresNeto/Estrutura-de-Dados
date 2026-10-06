#include <stdio.h>
#include <stdlib.h>

// Estrutura para Armazenar os dados da Lista
typedef struct site
{
    char titulo[20];
    char descricao[20];
    char link[20];
    struct site *proximo;
} Site;

// Estrutura para gerenciar a Lista
typedef struct lse
{
    Site *primeiro;
    int qtd;
} LSE;

void inicializaListaLSE(LSE *ls)
{
    ls->primeiro = NULL;
    ls->qtd = 0;
}

int retornaQtdLSE(LSE *ls)
{
    return ls->qtd;
}

Site *cadastraNovoSite()
{
    Site *novo = (Site *)malloc(sizeof(Site));

    printf("\nInforme o Título do Site:");
    if (fgets(novo->titulo, 20, stdin) != NULL)
    {
        // Remove o '\n' (nova linha) do final, se ele existir
        novo->titulo[strcspn(novo->titulo, "\n")] = '\0';
    }
    printf("\nInforme o Descrição do Site:");
    if (fgets(novo->descricao, 20, stdin) != NULL)
    {
        // Remove o '\n' (nova linha) do final, se ele existir
        novo->descricao[strcspn(novo->descricao, "\n")] = '\0';
    }
    printf("\nInforme o Link do Site:");
    if (fgets(novo->link, 20, stdin) != NULL)
    {
        // Remove o '\n' (nova linha) do final, se ele existir
        novo->link[strcspn(novo->link, "\n")] = '\0';
    }
    novo->proximo = NULL;
    return novo;
}
void mostraSite(Site st)
{
    printf("\n ------------------------------------- ");
    printf("\n\t Título do Site: %s ", st.titulo);
    printf("\n\t Descrição do Site: %s ", st.descricao);
    printf("\n\t Link do Site: %s ", st.link);
    printf("\n ------------------------------------- \n");
}
void mostraLista(LSE *lista)
{
    Site *aux = lista->primeiro;
    if (aux == NULL)
    {
        printf("\n =>> LISTA VAZIA <<=");
        return;
    }
    int ct = 0;
    printf("\n => Inicio da Lista <=");
    while (aux != NULL)
    {
        printf("\n E%d ", ct++);
        mostraSite(*aux);
        aux = aux->proximo;
    }
    printf("\n => Fim da Lista <=");
}
void insereInicio(LSE *lista, Site *site)
{
    // insere um elemento no início da lista forma reduzida
    site->proximo = lista->primeiro;
    lista->primeiro = site;
    lista->qtd++;
}

void insereFim(LSE *lista, Site *site)
{
    // lista vazia
    if (lista->primeiro == NULL)
        insereInicio(lista, site);
    else
    {
        // Lista com elementos
        Site *aux = lista->primeiro;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        site->proximo = NULL;
        aux->proximo = site;
        lista->qtd++;
    }
}

void inserePosicao(LSE *lista, Site *site, int posicao)
{
    if (posicao <= 0)
        insereInicio(lista, site);
    else
    {
        if (posicao >= lista->qtd)
            insereFim(lista, site);
        else
        {
            Site *aux = lista->primeiro;
            while (posicao - 1 > 0)
            {
                aux = aux->proximo;
                posicao--;
            }
            site->proximo = aux->proximo;
            aux->proximo = site;
            lista->qtd++;
        }
    }
}

Site *removeInicio(LSE *lista)
{
    Site *removido = lista->primeiro;
    if (lista->primeiro != NULL)
    {
        lista->primeiro = lista->primeiro->proximo;
        lista->qtd--;
        removido->proximo = NULL;
    }
    return removido;
}

Site *removeFim(LSE *lista)
{
    Site *removido;
    if (lista->primeiro == NULL)
        return lista->primeiro;
    else
    {
        if (lista->primeiro->proximo == NULL)
        {
            removido = removeInicio(lista);
        }
        else
        {
            Site *aux = lista->primeiro;
            while (aux->proximo->proximo != NULL)
            {
                aux = aux->proximo;
            }
            removido = aux->proximo;
            aux->proximo = NULL;
            lista->qtd--;
        }
        return removido;
    }
}

Site *removePosicao(LSE *lista, int posicao);

void menu(LSE *lista)
{
    int op = 0, posicao = 0;
    Site *aux = NULL;
    printf("\nMenu de operacoes sobre um LSE:\n");
    printf("\n\t1 - Insere no Inicio:");
    printf("\n\t2 - Insere no Fim:");
    printf("\n\t3 - Insere na Posicao:");
    printf("\n\t4 - Remove no Inicio:");
    printf("\n\t5 - Remove no Fim:");
    printf("\n\t6 - Remove na Posicao:");
    printf("\n\t7 - Mostra Lista:");
    printf("\n\t8 - Mostra Site na Posicao:");
    printf("\n\t9 - Apaga Todos Elementos da Lista:");
    printf("\n\t10 - Localiza um Site pelo Título");
    printf("\n\t0 - Para Sair da Funcao Menu:");
    printf("\n\tInforme a opcao:");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        printf("\n\tFuncao Insere no Inicio!!");
        insereInicio(lista, cadastraNovoSite());
        break;
    case 2:
        printf("\n\tFuncao Insere no Fim!!");
        insereFim(lista, cadastraNovoSite());
        break;
    case 3:
        printf("\n\tFuncao Insere na Posicao!!");
        printf("\n\t\tInforme a posicao nova:");
        scanf("%d", &posicao);
        printf("\n Posicao = %d", posicao);
        inserePosicao(lista, cadastraNovoSite(), posicao);
        break;
    case 4:
        printf("\n\tFuncao Remove no Inicio:");
        aux = removeInicio(lista);
        if (aux != NULL)
        {
            mostraSite(*aux);
            free(aux);
        }
        break;
    case 5:
        printf("\n\tFuncao Remove no Fim:");
        aux = removeFim(lista);
        if (aux != NULL)
        {
            mostraSite(*aux);
            free(aux);
        }
        break;
    // case 6:
    //     printf("\n\tFuncao Remove na Posicao!!");
    //     printf("\n\t\tInforme a posicao:");
    //     scanf("%d", &posicao);
    //     // aux = removePosicao(lista, posicao);
    //     // if (aux != NULL)
    //     // {
    //     //    mostraSite(*aux);
    //     //     free(aux);
    //     // }
    //     break;
    case 7:
        printf("\n\nMostra Lista !!!");
        mostraLista(lista);
        break;
        //     //     case 8:
        //     //         printf("\n\tFuncao Mostra um Aluno na Posicao - Pos!!");
        //     //         printf("\n\t\tInforme a posicao:");
        //     //         break;
        //     //     case 9:
        //     //         printf("\n\tFuncao Apaga todos Elementos da Lista!");
        //     //         break;

    case 0:
        printf("\n\n*** Fim do Programa!!! ***\n");
        break;
    default:
        printf("\n\n*** Opcao Invalida!!! ***\n");
    }
    if (op > 0 && op <= 10)
    {
        menu(lista);
    }
}

int main()
{
    // criei a Lista LSE de Sites Favoritos
    LSE *sitesFavoritos = (LSE *)malloc(sizeof(LSE));

    // Inicializar a Lista LSE
    inicializaListaLSE(sitesFavoritos);

    // Mostrar a quantidade de elementos da Lista
    printf("\n Quantidade de Elementos da LSE = %d\n", retornaQtdLSE(sitesFavoritos));

    menu(sitesFavoritos);
}
