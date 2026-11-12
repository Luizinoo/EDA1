#include <stdio.h>
#include <stdlib.h>

/* Definição do tipo de dado */
typedef struct {
    int codigo;
    int quantidade;
} Registro;

/* Assinaturas das funções obrigatórias */
Registro* criarRegistros(int n);
int totalQuantidades(Registro v[], int n);

int main(void) {
    Registro *v = NULL;
    int total = 0;

    /* =========================================================================
     * TESTE 1: Três registros
     * Esperado: 4 + 9 + 2 = 15
     * ========================================================================= */
    printf("--- Teste 1: Tres registros ---\n");
    v = criarRegistros(3);
    if (v != NULL) {
        v[0].codigo = 10;
        v[0].quantidade = 4;
        
        v[1].codigo = 20;
        v[1].quantidade = 9;
        
        v[2].codigo = 30;
        v[2].quantidade = 2;

        total = totalQuantidades(v, 3);
        printf("Resultado obtido: %d | Esperado: 15\n\n", total);

        free(v);
        v = NULL;
    } else {
        printf("Falha na alocacao de memoria para o Teste 1.\n\n");
    }

    /* =========================================================================
     * TESTE 2: Um unico registro com quantidade 7
     * Esperado: 7
     * ========================================================================= */
    printf("--- Teste 2: Um registro ---\n");
    v = criarRegistros(1);
    if (v != NULL) {
        v[0].codigo = 100;
        v[0].quantidade = 7;

        total = totalQuantidades(v, 1);
        printf("Resultado obtido: %d | Esperado: 7\n\n", total);

        free(v);
        v = NULL;
    } else {
        printf("Falha na alocacao de memoria para o Teste 2.\n\n");
    }

    /* =========================================================================
     * TESTE 3: Inicializacao padrao do calloc (zeros)
     * Esperado: 0
     * ========================================================================= */
    printf("--- Teste 3: Inicializacao calloc (dois registros zerados) ---\n");
    v = criarRegistros(2);
    if (v != NULL) {
        /* Não altera a quantidade para validar o comportamento do calloc */
        total = totalQuantidades(v, 2);
        printf("Resultado obtido: %d | Esperado: 0\n\n", total);

        free(v);
        v = NULL;
    } else {
        printf("Falha na alocacao de memoria para o Teste 3.\n\n");
    }

    /* =========================================================================
     * TESTE 4 (Proprio): Cinco registros com valores sequenciais
     * Esperado: 1 + 2 + 3 + 4 + 5 = 15
     * ========================================================================= */
    printf("--- Teste 4 (Proprio): Cinco registros ---\n");
    v = criarRegistros(5);
    if (v != NULL) {
        int i;
        for (i = 0; i < 5; i++) {
            v[i].codigo = (i + 1) * 100;
            v[i].quantidade = i + 1;
        }

        total = totalQuantidades(v, 5);
        printf("Resultado obtido: %d | Esperado: 15\n\n", total);

        free(v);
        v = NULL;
    } else {
        printf("Falha na alocacao de memoria para o Teste 4.\n\n");
    }

    return 0;
}

/* 
 * Função: criarRegistros
 * Aloca dinamicamente um vetor de n Registros usando calloc.
 * Retorna o ponteiro para o bloco de memória ou NULL se a alocação falhar.
 * Nota de correção da assinatura do documento: o retorno DEVE ser um ponteiro (Registro*).
 */
Registro* criarRegistros(int n) {
    if (n <= 0) {
        return NULL;
    }
    return (Registro*) calloc(n, sizeof(Registro));
}

/* 
 * Função: totalQuantidades
 * Percorre o vetor de n registros e soma as quantidades.
 * Não altera a estrutura da memória.
 */
int totalQuantidades(Registro v[], int n) {
    int i;
    int soma = 0;
    
    if (v == NULL || n <= 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        soma += v[i].quantidade;
    }

    return soma;
}