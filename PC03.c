#include <stdio.h>

typedef struct {
    int codigo;
    int quantidade;
} Registro;

int salvarRegistros(char nome[], Registro v[], int n){
    int i;
    FILE *arq;
        arq = fopen(nome, "w");
    if (arq == NULL){
        return 0;
    }
    for ( i = 0; i < n; i++){
        fprintf(arq, "%d %d\n", v[i].codigo, v[i].quantidade);
    }
    fclose(arq);
    return 1;
}

int carregarRegistros(char nome[], Registro v[], int max){
    int n = 0;
    FILE *arq;

    arq = fopen(nome, "r");
    
    if (arq == NULL){
        return -1;
    }
    
    while (n < max && fscanf(arq, "%d %d", &v[n].codigo, &v[n].quantidade) == 2){
        n++;
    }

    fclose(arq);
    return n;
}

int main(void){
    int i;
    Registro origem[3] = {
        {10, 4},
        {20, 9},
        {30, 2}
    };

    Registro destino[3];
    int n;

    salvarRegistros("teste.txt", origem, 3);
    n = carregarRegistros("teste.txt", destino, 3);

    if (n > 0) {
        printf("Lidos %d registros do arquivo:\n", n);
        for (i = 0; i < n; i++) {
            printf("Codigo: %d | Quantidade: %d\n", destino[i].codigo, destino[i].quantidade);
        }
    } else {
        printf("Erro ao carregar o arquivo.\n");
    }

    return 0;
}