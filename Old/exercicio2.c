#include <stdio.h>
#include <stdlib.h>

int x = 6;
float y = 6.66;
char z = 'g';

int main() {
    printf("Valor de x: %d \n Endereco de x: %p \n", x, &x);
    printf("Valor de y: %f \n Endereco de y: %p \n", y, &y);
    printf("Valor de z: %c \n Endereco de z: %p \n", z, &z);
}