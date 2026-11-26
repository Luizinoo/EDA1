#include <stdio.h>

/*
 * PC1 - Operacoes sobre vetores
 * Complete as funcoes abaixo.
 */

void imprimeVetor(int v[], int n){
    int i = 0;
    for (i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
}

int somaVetor(int v[], int n){
    int i, soma = 0; 
    for (i = 0; i < n; i++){
        soma += v[i];        
    }
    return soma;
}

int indiceMaior(int v[], int n){
    int i, ind = 0;
    for ( i = 0; i < n; i++){
        if (v[i]>v[ind]){
            ind = i;
        }
    }
    return ind;
}

int contaOcorrencias(int v[], int n, int valor){
    int i, cont = 0;
    for (i = 0; i < n; i++){
        if (v[i] == valor){
            cont ++;
        }
    }
    
    return cont;
}

int buscaLinear(int v[], int n, int valor){
    int i , pos = -1;
    for (i = 0; i < n; i++){
        if (v[i] == valor){
            pos = i;
        }
    }
        return pos;
}

int main(void){
    int v1[6] = {4, 1, 7, 3, 2, 5};
    int v2[4] = {8, 8, 1, 0};

    printf("v1: ");
    imprimeVetor(v1, 6);
    printf("\n");

    printf("soma v1 = %d\n", somaVetor(v1, 6));
    printf("indice maior v1 = %d\n", indiceMaior(v1, 6));
    printf("ocorrencias de 3 em v1 = %d\n", contaOcorrencias(v1, 6, 3));
    printf("busca 2 em v1 = %d\n", buscaLinear(v1, 6, 2));
    printf("busca 9 em v1 = %d\n", buscaLinear(v1, 6, 9));

    printf("v2: ");
    imprimeVetor(v2, 4);
    printf("\n");

    printf("soma v2 = %d\n", somaVetor(v2, 4));
    printf("indice maior v2 = %d\n", indiceMaior(v2, 4));

    return 0;
}
