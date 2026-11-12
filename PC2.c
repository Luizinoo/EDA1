#include <stdio.h>

void trocar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void extremos(int v[], int n, int *menor, int *maior) {
    int i;
    *menor = v[0];
    *maior = v[0];
    for (i = 0; i < n; i++) {
        if (*maior < v[i]) {
            *maior = v[i];
        }
        if (*menor > v[i]) {
            *menor = v[i];
        }
    }
    
}

int main(void){
    int x = 4, y = 9;
    int v[] = {7, 2, 9, 4, 1};
    int maior, menor;
    
    trocar(&x, &y);
    extremos(v, 5, &menor, &maior);

    printf("X = %d X = %d\n", x, y);
    printf("Menor = %d Maior = %d\n", menor, maior);

    return 0;
}