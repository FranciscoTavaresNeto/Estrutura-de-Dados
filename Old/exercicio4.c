#include <stdio.h>
#include <stdlib.h>

int a = 5,b = 1;

int main() {
    if(&a > &b) {
        printf("O endereço A: %p e maior que o endereco B: %p \n", &a, &b);
    } else {
        printf("O endereço B: %p e maior que o endereco A: %p \n", &b, &a);
    }
}