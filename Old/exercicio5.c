#include <stdio.h>
#include <stdlib.h>

int num1, num2, *p1, *pnum2;

num1 = 5;
num2 = 7;


void soma(int *p1, int *p2) {
    int temp;
    temp = *p1 + *p2;
    printf("A soma e: %d \n", temp);    
}

void dif(int *p1, int *p2) {
    int temp;
    temp = *p1 - *p2;
    printf("A dif e: %d \n", temp);
}

void produto(int *p1, int *p2) {
    int temp;
    temp = *p1 * *p2;
    printf("O produto e: %d\n", temp);
}
int main() {
    printf("Num1: %d \n Num2: %d\n", num1, num2);
    soma(&num1, &num2);
    dif(&num1, &num2);
    produto(&num1, &num2);
}