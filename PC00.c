#include <stdio.h>

int maior(int a, int b)

{
    if (a > b)
        return a;
    return b;
}

int main(void){

    int x, y;
    
    printf("digite dois numeros separados por espaco\n");
    scanf("%d %d", &x, &y);
    printf("maior = %d\n", maior(x, y));
    return 0;
}