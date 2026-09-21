#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct apartamento
{
    char condominio[20];
    int numAp;
    int andarAp;
    int qtdComodosAp;
    int numBoxAp;
    double v_aluguelAP;
    double v_condominioAP;
} Apartamento;

int main()
{

    Apartamento ap101 = {"Braganca", 101, 1, 5, 23, 800.00, 230.00};
    Apartamento ap201; // Declarar dois apartamentos

    strcpy(ap201.condominio, "Brangaca");
    ap201.numAp = 201;
    ap201.andarAp = 2;
    ap201.qtdComodosAp = 5;
    ap201.numBoxAp = 32;
    ap201.v_aluguelAP = 1000;
    ap201.v_condominioAP = 230.00;
}