#include <stdio.h>

/* Assinaturas das funções obrigatórias */
int somaVetor(int v[], int n);
int contarValor(int v[], int n, int x);

int main(void) {
    /* Definição dos vetores de teste */
    int v1[] = {7};
    int v2[] = {4, -1, 2, 4};
    int v3[] = {0, 0, 0};
    int v4[] = {-3, -1, -3};
    int v5[] = {10, -5, 20, -5, 30}; /* Vetor para o teste próprio */

    int s_obtida, c_obtida;

    printf("=================================================================\n");
    printf("                  EXECUCAO DOS CASOS DE TESTE                    \n");
    printf("=================================================================\n\n");

    /* Teste 1: NULL, n = 0, x = 2 */
    /* Esperado: Soma = 0, Ocorrências = 0 */
    s_obtida = somaVetor(NULL, 0);
    c_obtida = contarValor(NULL, 0, 2);
    printf("Teste 1 (NULL, n=0):\n");
    printf("  Soma        -> Obtido: %d | Esperado: 0\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 0\n\n", c_obtida);

    /* Teste 2: {7}, n = 1, x = 7 */
    /* Esperado: Soma = 7, Ocorrências = 1 */
    s_obtida = somaVetor(v1, 1);
    c_obtida = contarValor(v1, 1, 7);
    printf("Teste 2 ({7}, n=1, x=7):\n");
    printf("  Soma        -> Obtido: %d | Esperado: 7\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 1\n\n", c_obtida);

    /* Teste 3: {7}, n = 1, x = 2 */
    /* Esperado: Soma = 7, Ocorrências = 0 */
    s_obtida = somaVetor(v1, 1);
    c_obtida = contarValor(v1, 1, 2);
    printf("Teste 3 ({7}, n=1, x=2):\n");
    printf("  Soma        -> Obtido: %d | Esperado: 7\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 0\n\n", c_obtida);

    /* Teste 4: {4, -1, 2, 4}, n = 4, x = 4 */
    /* Esperado: Soma = 9, Ocorrências = 2 */
    s_obtida = somaVetor(v2, 4);
    c_obtida = contarValor(v2, 4, 4);
    printf("Teste 4 ({4, -1, 2, 4}, n=4, x=4):\n");
    printf("  Soma        -> Obtido: %d | Esperado: 9\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 2\n\n", c_obtida);

    /* Teste 5: {0, 0, 0}, n = 3, x = 0 */
    /* Esperado: Soma = 0, Ocorrências = 3 */
    s_obtida = somaVetor(v3, 3);
    c_obtida = contarValor(v3, 3, 0);
    printf("Teste 5 ({0, 0, 0}, n=3, x=0):\n");
    printf("  Soma        -> Obtido: %d | Esperado: 0\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 3\n\n", c_obtida);

    /* Teste 6: {-3, -1, -3}, n = 3, x = -3 */
    /* Esperado: Soma = -7, Ocorrências = 2 */
    s_obtida = somaVetor(v4, 3);
    c_obtida = contarValor(v4, 3, -3);
    printf("Teste 6 ({-3, -1, -3}, n=3, x=-3):\n");
    printf("  Soma        -> Obtido: %d | Esperado: -7\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 2\n\n", c_obtida);

    /* Teste 7: {4, -1, 2, 4}, n = 2, x = 4 (Prefixos limitados a n=2) */
    /* Esperado: Soma = 3, Ocorrências = 1 */
    s_obtida = somaVetor(v2, 2);
    c_obtida = contarValor(v2, 2, 4);
    printf("Teste 7 ({4, -1, 2, 4}, n=2, x=4 - prefixo):\n");
    printf("  Soma        -> Obtido: %d | Esperado: 3\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 1\n\n", c_obtida);

    /* =========================================================================
     * TESTE 8 (Próprio): Validação com valores mistos e negativos
     * Vetor: {10, -5, 20, -5, 30}, n = 5, x = -5
     * Justificativa: Testa o comportamento da recursão em um vetor maior,
     * validando se múltiplos elementos negativos e positivos são processados
     * corretamente sem extrapolar o prefixo de tamanho n.
     * Esperado: Soma = 50, Ocorrências = 2
     * ========================================================================= */
    s_obtida = somaVetor(v5, 5);
    c_obtida = contarValor(v5, 5, -5);
    printf("--- Teste 8 (Proprio): {10, -5, 20, -5, 30}, n=5, x=-5 ---\n");
    printf("  Soma        -> Obtido: %d | Esperado: 50\n", s_obtida);
    printf("  Ocorrencias -> Obtido: %d | Esperado: 2\n\n", c_obtida);

    return 0;
}

/* 
 * Função recursiva: somaVetor
 * Soma os primeiros n elementos de um vetor usando recursão decrescente.
 */
int somaVetor(int v[], int n) {
    /* Caso-base: se n for 0, o prefixo é vazio (retorna 0) */
    if (n <= 0) {
        return 0;
    }
    
    /* Redução: soma o último elemento do prefixo atual com a soma do restante (n - 1) */
    return v[n - 1] + somaVetor(v, n - 1);
}

/* 
 * Função recursiva: contarValor
 * Conta quantas vezes o valor x aparece nos primeiros n elementos do vetor.
 */
int contarValor(int v[], int n, int x) {
    int ocorrencia_atual;

    /* Caso-base: se n for 0, o prefixo é vazio (retorna 0) */
    if (n <= 0) {
        return 0;
    }

    /* Verifica se o elemento atual é igual a x (1 se verdadeiro, 0 se falso) */
    ocorrencia_atual = (v[n - 1] == x) ? 1 : 0;

    /* Redução: soma a ocorrência do elemento atual com o resultado da chamada para n - 1 */
    return ocorrencia_atual + contarValor(v, n - 1, x);
}