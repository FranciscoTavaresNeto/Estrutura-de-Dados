#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct filme
{
    char titulo[20];
    Data lancamento;
    char diretor[20];
    int qualificacao;
    char gemero[20];
} Filme;

void cadastraFilmeTitanic(Filme *cartaz)
{
    strcpy(cartaz->titulo, "Titanic");
    cartaz->lancamento.dia = 03;
    cartaz->lancamento.mes = 05;
    cartaz->lancamento.ano = 1997;
    strcpy(cartaz->diretor, "James Cameron");
    cartaz->qualificacao = 8;
    strcpy(cartaz->gemero, "Ficcao");
}

void cadastraNovoFilme(Filme *cartaz)
{
    printf("\nInforme Título do Filme:");
    scanf("%s", cartaz->titulo);
    printf("Informe o dia de Lancamento:");
    scanf("%d", &cartaz->lancamento.dia);
    printf("Informe o mes de Lancamento:");
    scanf("%d", &cartaz->lancamento.mes);
    printf("Informe o ano de Lancamento:");
    scanf("%d", &cartaz->lancamento.ano);
    printf("\nInforme Diretor do Filme:");
    scanf("%s", cartaz->diretor);
    printf("Informe a qualificacao Filme:");
    scanf("%d", &cartaz->qualificacao);
    printf("\nInforme Genero do Filme:");
    scanf("%s", cartaz->gemero);
}

void mostraFilme(Filme cartaz)
{
    printf("\n Filme %s Diretor %s ", cartaz.titulo, cartaz.diretor);
    printf("\n Lancamento %d/%d/%d", cartaz.lancamento.dia, cartaz.lancamento.mes, cartaz.lancamento.ano);
    printf("\n Genero %s  Qualificacao %d \n", cartaz.gemero, cartaz.qualificacao);
}

int main()
{
    Data avatarData = {02, 04, 2009};
    Filme avatar = {"Avatar", avatarData, "James Cameron", 9, "ficcao"};

    Filme titanic;

    cadastraFilmeTitanic(&titanic);

    // mostraFilme(avatar);
    // mostraFilme(titanic);

    Filme *odisseia = NULL; // declaração ponteiro de filme

    odisseia = (Filme *)malloc(sizeof(Filme));

    cadastraNovoFilme(odisseia);

    mostraFilme(*odisseia);

    free(odisseia);
    odisseia = NULL;

    // O ponteiro odisseia recebe o endereço de avatar
    odisseia = &avatar;
    mostraFilme(*odisseia);

    // Filme filmesFiccao[4];

    // filmesFiccao[0] = avatar;
    // filmesFiccao[1] = titanic;
    // cadastraNovoFilme((filmesFiccao + 2)); // passagem por referência
    // cadastraNovoFilme(&filmesFiccao[3]);   // passagem por referência

    // for (int i = 0; i < 4; i++)
    // {
    //     mostraFilme(*(filmesFiccao + i)); // Passagem por valor
    //     // mostraFilme(filmesFiccao[i]); //Passagem por valor
    // }
}
