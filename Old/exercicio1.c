#include <stdio.h>
#include <stdlib.h>

float a = 1.1;
double b = 7.8;
char c = 'a';
short int d = 8;
int e = 9;
long int f = 19;
double g = 52.3;
long double h = 77.33;

int main() {
    printf("O float %f ocupa na memória %zu Bytes \n",a, sizeof(a));
    printf("O double %f ocupa na memória %zu Bytes \n",b,sizeof(b));
    printf("O char %c ocupa na memória %zu Bytes \n",c, sizeof(c));
    printf("O short int %d ocupa na memória %zu Bytes \n",d, sizeof(d));
    printf("O int %d ocupa na memória %zu Bytes \n",e, sizeof(e));    
    printf("O long int %ld ocupa na memória %zu Bytes \n",f, sizeof(f));
    printf("O double %f ocupa na memória %zu Bytes \n",g, sizeof(g));
    printf("O long double %Lf ocupa na memória %zu Bytes \n",h, sizeof(h));
    printf("\n________________________________________________\n");
    printf("\nO float está armazenado em: %p \n", &a);
    printf("O double está armazenado em: %p \n", &b);
    printf("O char está armazenado em: %p \n", &c);
    printf("O short int está armazenado em: %p \n", &d);
    printf("O int está armazenado em: %p \n", &e);
    printf("O long int está armazenado em: %p \n", &f);
    printf("O double está armazenado em: %p \n", &g);
    printf("O long double está armazenado em: %p \n", &h);
}
