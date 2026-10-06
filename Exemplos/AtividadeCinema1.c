#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao das Estruturas
typedef struct poltrona
{
    int num;
    char fileira;
    int flag_livre; // 1 = Livre, 0 = Ocupada
} Poltrona;

typedef struct sala
{
    Poltrona poltronas[15];
    int num_sala;
} Sala;

typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct sessao
{
    char nomeFilme[30];
    Data dataFilme;
    int horaFilme;
    Sala salaReservada;
} Sessao;

// PROTÓTIPOS DAS FUNÇÕES

// Passagem por REFERÊNCIA (Modificam os dados)
void cadastrarPoltrona(Poltrona *p, int num, char fileira);
void inicializarSala(Sala *s, int numSala);
void cadastrarData(Data *d, int dia, int mes, int ano);
void cadastrarSessao(Sessao *s, char *filme, Data d, int hora, Sala sala);
void comprarPoltrona(Sessao *s, int posPoltrona);
void cancelarCompra(Sessao *s, int posPoltrona);

// Passagem por VALOR (Apenas exibição)
void mostrarPoltrona(Poltrona p);
void mostrarMapaSala(Sala s);
void mostrarData(Data d);
void mostrarSessao(Sessao s);
int mostrarMenu()
{
    int opcao;
    printf("\n========================================\n");
    printf("     SISTEMA DE CONTROLE DE CINEMA      \n");
    printf("========================================\n");
    printf("1. Listar todas as sessoes\n");
    printf("2. Comprar poltrona (Opcao 7.a)\n");
    printf("3. Cancelar compra de poltrona (Opcao 7.b)\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}
// Implemente o main() montando o menu interativo com switch-case

int main()
{
    int opcao;
    // 1. Reserva do vetor de 4 sessões no cinema
    Sessao sessoes[4];

    do
    {
        opcao = mostrarMenu();
    } while (opcao != 4);
}