#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// ESTRUTURAS DA PILHA GENÉRICA
// ==========================================

typedef struct elemento
{
    void *dado;
    struct elemento *proximo;
} Elemento;

typedef struct pilha
{
    Elemento *topo;
    int qtd;
} Pilha;

Pilha *criaPilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->qtd = 0;
    return p;
}

void push(Pilha *p, void *dado)
{
    if (dado != NULL)
    {
        Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
        novo->dado = dado;
        novo->proximo = p->topo;
        p->topo = novo;
        p->qtd++;
    }
    else
    {
        printf("\n --- PUSH nao Realizado - Elemento Invalido!!");
    }
}

void *pop(Pilha *p)
{
    if (p->topo == NULL)
    {
        printf("\n -- Nao pode realizar POP - Pilha Vazia\n");
        return NULL;
    }

    Elemento *aux = p->topo;
    void *dado = aux->dado;

    p->topo = p->topo->proximo;
    p->qtd--;
    free(aux);

    return dado;
}

void mostraTopo(Pilha *p, void (*imprime)(void *))
{
    if (p->topo != NULL)
    {
        printf("\n Mostra TOPO - Pilha");
        imprime(p->topo->dado);
    }
    else
    {
        printf("\n TOPO NULO - Pilha Vazia \n");
    }
}

void apagaPilha(Pilha *p, void (*libera)(void *))
{
    while (p->topo != NULL)
    {
        void *dado = pop(p);
        if (libera != NULL)
        {
            libera(dado);
        }
    }
}

void mostraPilha(Pilha *p, void (*imprime)(void *))
{
    Elemento *aux = p->topo;
    if (aux == NULL)
        printf("\n  -- Pilha Vazia!!\n");
    else
        while (aux != NULL)
        {
            imprime(aux->dado);
            aux = aux->proximo;
        }
}

// ==========================================
// FUNÇÕES AUXILIARES PARA TESTE NO MENU
// ==========================================

void *criaDado(int valor)
{
    int *novo = (int *)malloc(sizeof(int));
    *novo = valor;
    return novo;
}

void mostraDado(void *dado)
{
    if (dado != NULL)
    {
        printf("\n\t Valor: %d \n", *(int *)dado);
    }
}

// ==========================================
// MENU E PROGRAMA PRINCIPAL
// ==========================================

void menu(Pilha *p1)
{
    int op, valor;
    void *removido;

    do
    {
        printf("\n\nInforme uma Opcao:");
        printf("\n -- 1 - PUSH - Inserir novo Elemento:");
        printf("\n -- 2 - POP - Remover um Elemento:");
        printf("\n -- 3 - Mostra TOPO:");
        printf("\n -- 4 - Apagar Pilha:");
        printf("\n -- 5 - Mostrar Pilha:");
        printf("\n -- 0 - para Sair do Programa:\n");
        printf("\nInforme sua Opcao:");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\n Funcao PUSH. \n");
            printf("Informe um valor inteiro:");
            scanf("%d", &valor);
            push(p1, criaDado(valor));
            printf("\n Insercao Realizada com Sucesso");
            break;
        case 2:
            printf("\n Funcao POP. \n");
            removido = pop(p1);
            if (removido != NULL)
            {
                mostraDado(removido);
                printf("\n --- Remocao Realizada com Sucesso!!");
                free(removido);
            }
            else
            {
                printf("\n --- ERRO - Remocao invalida!!");
            }
            break;
        case 3:
            printf("Mostra TOPO Pilha P1:");
            mostraTopo(p1, mostraDado);
            break;
        case 4:
            printf("\n Apagar a Pilha !! \n");
            apagaPilha(p1, free);
            break;
        case 5:
            printf("\nMostra Pilha P1:");
            mostraPilha(p1, mostraDado);
            break;
        case 6:
            printf("\n Cria uma Pilha Invertida sem alterar Pilha 1");
            break;
        case 7:
            printf("\n Inverte a Pilha 1");
            break;
        case 8:
            printf("\n Inverte Extremos da Pilha 1");
            break;
        default:
            printf("\nFim do programa!!\n");
        }

    } while (op > 0);
}

int main()
{
    Pilha *p1 = criaPilha();

    push(p1, criaDado(10));
    push(p1, criaDado(20));
    push(p1, criaDado(30));

    menu(p1);

    apagaPilha(p1, free);
    free(p1);

    return 0;
}