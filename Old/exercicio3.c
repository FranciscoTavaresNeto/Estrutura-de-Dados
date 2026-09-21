#include <stdio.h>
#include <stdlib.h>

int a = 15, *pa = &a;

int main() {
    printf("Valor de a: %d \n", a);
    *pa = 50;
    printf("Valor de a: %d \n", a);
}