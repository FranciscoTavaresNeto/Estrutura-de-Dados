#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================================
// ESTRUTURAS DE DADOS (BASEADAS NA AULA)
// ==========================================

typedef struct pino
{
    char cor[15];
    char sigla; // 'V', 'A', 'D', 'M' para facilitar a visualizacao na tela
    int idCor;  // 1 = Vermelho, 2 = Azul, 3 = Verde, 4 = Amarelo
    struct pino *proximo;
} Pino;

typedef struct pilha
{
    Pino *topo;
    int qtd;
    int capacidade; // 4 para Pilhas normais (P1..P4) e 1 para Temporarios (Temp1, Temp2)
} Pilha;

// ==========================================
// FUNCOES BASICAS DA PILHA
// ==========================================

Pilha *criaPilha(int capacidade)
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->qtd = 0;
    p->capacidade = capacidade;
    return p;
}

Pino *criaElementoPino(int idCor)
{
    Pino *novo = (Pino *)malloc(sizeof(Pino));
    novo->proximo = NULL;
    novo->idCor = idCor;

    switch (idCor)
    {
    case 1:
        strcpy(novo->cor, "Vermelho");
        novo->sigla = 'V';
        break;
    case 2:
        strcpy(novo->cor, "Azul");
        novo->sigla = 'A';
        break;
    case 3:
        strcpy(novo->cor, "Verde");
        novo->sigla = 'D';
        break;
    case 4:
        strcpy(novo->cor, "Amarelo");
        novo->sigla = 'M';
        break;
    }
    return novo;
}

int push(Pilha *p, Pino *elemento)
{
    if (elemento == NULL)
    {
        printf("\n --- PUSH nao Realizado - Elemento Invalido!!\n");
        return 0;
    }
    if (p->qtd >= p->capacidade)
    {
        printf("\n --- Movimento Invalido: Destino atingiu a capacidade maxima (%d)!\n", p->capacidade);
        return 0;
    }

    elemento->proximo = p->topo;
    p->topo = elemento;
    p->qtd++;
    return 1;
}

Pino *pop(Pilha *p)
{
    Pino *aux = p->topo;
    if (aux == NULL)
    {
        printf("\n --- Nao pode realizar POP - Origem Vazia!\n");
    }
    else
    {
        p->topo = p->topo->proximo;
        p->qtd--;
        aux->proximo = NULL;
    }
    return aux;
}

void apagaPilha(Pilha *p)
{
    while (p->topo != NULL)
    {
        free(pop(p));
    }
}

// ==========================================
// LOGICA E REGRAS DO JOGO
// ==========================================

int moverPino(Pilha *origem, Pilha *destino)
{
    if (origem == destino)
    {
        printf("\n --- A origem e o destino sao iguais!\n");
        return 0;
    }
    if (origem->topo == NULL)
    {
        printf("\n --- Movimento Invalido: A origem esta vazia!\n");
        return 0;
    }
    if (destino->qtd >= destino->capacidade)
    {
        printf("\n --- Movimento Invalido: O destino esta cheio (Max: %d)!\n", destino->capacidade);
        return 0;
    }

    Pino *p = pop(origem);
    push(destino, p);
    return 1;
}

int verificaVitoria(Pilha *p[], Pilha *temp1, Pilha *temp2)
{
    if (temp1->qtd > 0 || temp2->qtd > 0)
        return 0;

    for (int i = 0; i < 4; i++)
    {
        if (p[i]->qtd != 3)
            return 0;

        int corBase = p[i]->topo->idCor;
        Pino *atual = p[i]->topo;
        while (atual != NULL)
        {
            if (atual->idCor != corBase)
                return 0;
            atual = atual->proximo;
        }
    }
    return 1;
}

void inicializaJogoAleatorio(Pilha *p[], Pilha *temp1, Pilha *temp2)
{
    int cores[12] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};

    do
    {
        for (int i = 0; i < 4; i++)
            apagaPilha(p[i]);

        for (int i = 11; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int aux = cores[i];
            cores[i] = cores[j];
            cores[j] = aux;
        }

        int idx = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                push(p[i], criaElementoPino(cores[idx++]));
            }
        }
    } while (verificaVitoria(p, temp1, temp2));
}

// ==========================================
// INTERFACE VISUAL NO TERMINAL
// ==========================================

char obtemSiglaNaAltura(Pilha *p, int altura)
{
    if (altura >= p->qtd)
        return ' ';

    int passos = (p->qtd - 1) - altura;
    Pino *atual = p->topo;
    for (int i = 0; i < passos; i++)
    {
        atual = atual->proximo;
    }
    return atual->sigla;
}

void mostraJogo(Pilha *p[], Pilha *temp1, Pilha *temp2, int nivel, int movimentos, time_t inicio)
{
    int segundos = (int)difftime(time(NULL), inicio);
    char nomeNivel[10];
    char t1, t2;

    if (nivel == 1)
    {
        strcpy(nomeNivel, "Facil");
    }
    else if (nivel == 2)
    {
        strcpy(nomeNivel, "Medio");
    }
    else
    {
        strcpy(nomeNivel, "Dificil");
    }

    printf("\n======================================================\n");
    printf(" NIVEL: %s | MOVIMENTOS: %d | TEMPO: %02d:%02d\n",
           nomeNivel, movimentos, segundos / 60, segundos % 60);
    printf(" Legenda: [V]ermelho | [A]zul | Ver[D]e | A[M]arelo\n");
    printf("======================================================\n\n");

    if (temp1->topo != NULL)
    {
        t1 = temp1->topo->sigla;
    }
    else
    {
        t1 = ' ';
    }

    if (temp2->topo != NULL)
    {
        t2 = temp2->topo->sigla;
    }
    else
    {
        t2 = ' ';
    }

    if (nivel == 1)
        printf(" Temp1: [%c]                                Temp2: [%c]\n\n", t1, t2);
    else if (nivel == 2)
        printf(" Temp1: [%c]                                Temp2: [X] (Bloqueado)\n\n", t1);
    else
        printf(" Temp1: [X] (Bloqueado)                    Temp2: [X] (Bloqueado)\n\n");

    for (int h = 3; h >= 0; h--)
    {
        printf("          ");
        for (int i = 0; i < 4; i++)
        {
            printf("  [%c]  ", obtemSiglaNaAltura(p[i], h));
        }
        printf("\n");
    }
    printf("          ----------------------------\n");
    printf("            P1     P2     P3     P4   \n");
    printf("======================================================\n");
}

// ==========================================
// MENU INTERATIVO E MAIN
// ==========================================

void menuJogo(Pilha *p[], Pilha *temp1, Pilha *temp2, int nivel)
{
    int op, orig, dest, qualTemp;
    int movimentos = 0;
    time_t tempoInicio = time(NULL);

    do
    {
        mostraJogo(p, temp1, temp2, nivel, movimentos, tempoInicio);

        if (verificaVitoria(p, temp1, temp2))
        {
            double tempoTotal = difftime(time(NULL), tempoInicio);
            printf("\n******************************************************\n");
            printf(" PARABENS! Voce venceu o jogo!\n");
            printf(" Desempenho: %d movimentos em %.0f segundos.\n", movimentos, tempoTotal);
            printf("******************************************************\n");
            break;
        }

        printf("\nEscolha sua jogada:");
        printf("\n 1 - Mover entre Pilhas (POP Pilha X -> PUSH Pilha Y)");
        if (nivel <= 2)
        {
            printf("\n 2 - Mover de Pilha para Temporario (POP Pilha X -> PUSH Temp)");
            printf("\n 3 - Mover de Temporario para Pilha (POP Temp -> PUSH Pilha X)");
        }
        printf("\n 0 - Sair do Jogo\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("Informe a Pilha de Origem (1 a 4): ");
            scanf("%d", &orig);
            printf("Informe a Pilha de Destino (1 a 4): ");
            scanf("%d", &dest);

            if (orig >= 1 && orig <= 4 && dest >= 1 && dest <= 4)
            {
                if (moverPino(p[orig - 1], p[dest - 1]))
                    movimentos++;
            }
            else
            {
                printf("\n --- Pilha invalida! Escolha valores entre 1 e 4.\n");
            }
            break;

        case 2:
            if (nivel == 3)
            {
                printf("\n --- Nivel Dificil nao permite uso de temporarios!\n");
                break;
            }
            printf("Informe a Pilha de Origem (1 a 4): ");
            scanf("%d", &orig);
            if (orig < 1 || orig > 4)
            {
                printf("\n --- Pilha invalida!\n");
                break;
            }

            if (nivel == 1)
            {
                printf("Para qual Temporario (1 para Temp1, 2 para Temp2): ");
                scanf("%d", &qualTemp);
            }
            else
            {
                qualTemp = 1;
            }

            if (qualTemp == 1)
            {
                if (moverPino(p[orig - 1], temp1))
                    movimentos++;
            }
            else if (qualTemp == 2 && nivel == 1)
            {
                if (moverPino(p[orig - 1], temp2))
                    movimentos++;
            }
            else
            {
                printf("\n --- Temporario invalido!\n");
            }
            break;

        case 3:
            if (nivel == 3)
            {
                printf("\n --- Nivel Dificil nao permite uso de temporarios!\n");
                break;
            }
            if (nivel == 1)
            {
                printf("De qual Temporario (1 para Temp1, 2 para Temp2): ");
                scanf("%d", &qualTemp);
            }
            else
            {
                qualTemp = 1;
            }

            printf("Informe a Pilha de Destino (1 a 4): ");
            scanf("%d", &dest);
            if (dest < 1 || dest > 4)
            {
                printf("\n --- Pilha invalida!\n");
                break;
            }

            if (qualTemp == 1)
            {
                if (moverPino(temp1, p[dest - 1]))
                    movimentos++;
            }
            else if (qualTemp == 2 && nivel == 1)
            {
                if (moverPino(temp2, p[dest - 1]))
                    movimentos++;
            }
            else
            {
                printf("\n --- Temporario invalido!\n");
            }
            break;

        case 0:
            printf("\nSaindo do jogo...\n");
            break;

        default:
            printf("\n --- Opcao Invalida!\n");
        }

    } while (op != 0);
}

int main()
{
    srand((unsigned int)time(NULL));

    Pilha *p[4];
    for (int i = 0; i < 4; i++)
    {
        p[i] = criaPilha(4);
    }

    Pilha *temp1 = criaPilha(1);
    Pilha *temp2 = criaPilha(1);

    int nivel;
    printf("======================================================\n");
    printf("         JOGO DE LOGICA - PILHAS COLORIDAS            \n");
    printf("======================================================\n");
    printf("Selecione o Nivel de Dificuldade:\n");
    printf(" 1 - Facil   (4 Pilhas + Temp1 e Temp2)\n");
    printf(" 2 - Medio   (4 Pilhas + Apenas Temp1)\n");
    printf(" 3 - Dificil (4 Pilhas, Sem Temporarios)\n");
    printf("Opcao: ");
    scanf("%d", &nivel);

    if (nivel < 1 || nivel > 3)
    {
        printf("Nivel invalido! Ajustando para Nivel 1 (Facil).\n");
        nivel = 1;
    }

    inicializaJogoAleatorio(p, temp1, temp2);
    menuJogo(p, temp1, temp2, nivel);

    for (int i = 0; i < 4; i++)
    {
        apagaPilha(p[i]);
        free(p[i]);
    }
    apagaPilha(temp1);
    free(temp1);
    apagaPilha(temp2);
    free(temp2);

    return 0;
}