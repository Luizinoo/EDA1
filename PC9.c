/* PC9 EDA1 Aula 23 — Pilha (LIFO) e Fila (FIFO) com capacidade fixa 8
 * Compilacao: cc -std=c90 -Wall -Wextra -pedantic pc9.c -o pc9
 */
#include <stdio.h>

#define CAPACIDADE 8

/* =========================================================================
 * ESTRUTURAS E FUNCOES DA PILHA (LIFO)
 * ========================================================================= */
typedef struct {
    int dados[CAPACIDADE];
    int topo; /* Indica a próxima posição livre e a quantidade de elementos */
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = 0;
}

int pilhaCheia(const Pilha *p) {
    return p->topo >= CAPACIDADE;
}

int pilhaVazia(const Pilha *p) {
    return p->topo == 0;
}

int empilhar(Pilha *p, int valor) {
    if (pilhaCheia(p)) {
        return 0; /* Falha: pilha cheia */
    }
    p->dados[p->topo] = valor;
    (p->topo)++;
    return 1; /* Sucesso */
}

int desempilhar(Pilha *p, int *saida) {
    if (pilhaVazia(p)) {
        return 0; /* Falha: pilha vazia */
    }
    (p->topo)--;
    *saida = p->dados[p->topo];
    return 1; /* Sucesso */
}

void exibirPilha(const Pilha *p) {
    int i;
    printf("Pilha (topo=%d): [ ", p->topo);
    for (i = 0; i < p->topo; i++) {
        printf("%d ", p->dados[i]);
    }
    printf("]\n");
}

/* =========================================================================
 * ESTRUTURAS E FUNCOES DA FILA (FIFO - Implementação Circular)
 * ========================================================================= */
typedef struct {
    int dados[CAPACIDADE];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

int filaCheia(const Fila *f) {
    return f->tamanho >= CAPACIDADE;
}

int filaVazia(const Fila *f) {
    return f->tamanho == 0;
}

int enfileirar(Fila *f, int valor) {
    if (filaCheia(f)) {
        return 0; /* Falha: fila cheia */
    }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % CAPACIDADE;
    (f->tamanho)++;
    return 1; /* Sucesso */
}

int desenfileirar(Fila *f, int *saida) {
    if (filaVazia(f)) {
        return 0; /* Falha: fila vazia */
    }
    *saida = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % CAPACIDADE;
    (f->tamanho)--;
    return 1; /* Sucesso */
}

void exibirFila(const Fila *f) {
    int i, idx;
    printf("Fila (tamanho=%d): [ ", f->tamanho);
    for (i = 0; i < f->tamanho; i++) {
        idx = (f->inicio + i) % CAPACIDADE;
        printf("%d ", f->dados[idx]);
    }
    printf("]\n");
}

/* =========================================================================
 * FUNCAO PRINCIPAL (TESTES)
 * ========================================================================= */
int main(void) {
    Pilha p;
    Fila f;
    int saida = 0;
    int i;

    printf("===================================================\n");
    printf("          TESTES DA PILHA (LIFO)                   \n");
    printf("===================================================\n");
    
    inicializarPilha(&p);
    exibirPilha(&p);

    /* 1. Teste de estrutura vazia */
    if (!desempilhar(&p, &saida)) {
        printf("-> Sucesso: Tentativa de desempilhar pilha vazia falhou corretamente.\n");
    }

    /* 2. Inserção e Ordem (inserir 4, 9 e 2) */
    empilhar(&p, 4);
    empilhar(&p, 9);
    empilhar(&p, 2);
    exibirPilha(&p);

    /* Removendo da Pilha (LIFO: deve retirar 2, depois 9, depois 4) */
    printf("Remocoes na Pilha (LIFO):\n");
    while (desempilhar(&p, &saida)) {
        printf("  Removido: %d\n", saida);
    }
    exibirPilha(&p);

    /* 3. Teste de Limites (Preencher até a capacidade 8 e tentar inserir o 9º) */
    printf("\nTestando limites da Pilha (capacidade %d):\n", CAPACIDADE);
    for (i = 1; i <= 10; i++) {
        if (empilhar(&p, i * 10)) {
            printf("  Empilhado com sucesso: %d\n", i * 10);
        } else {
            printf("  FALHA AO EMPILHAR %d (Pilha cheia no limite)\n", i * 10);
        }
    }
    exibirPilha(&p);


    printf("\n===================================================\n");
    printf("          TESTES DA FILA (FIFO)                    \n");
    printf("===================================================\n");

    inicializarFila(&f);
    exibirFila(&f);

    /* 1. Teste de estrutura vazia */
    if (!desenfileirar(&f, &saida)) {
        printf("-> Sucesso: Tentativa de desenfileirar fila vazia falhou corretamente.\n");
    }

    /* 2. Inserção e Ordem (inserir 4, 9 e 2) */
    enfileirar(&f, 4);
    enfileirar(&f, 9);
    enfileirar(&f, 2);
    exibirFila(&f);

    /* Removendo da Fila (FIFO: deve retirar 4, depois 9, depois 2) */
    printf("Remocoes na Fila (FIFO):\n");
    while (desenfileirar(&f, &saida)) {
        printf("  Removido: %d\n", saida);
    }
    exibirFila(&f);

    /* 3. Teste de Limites (Preencher até a capacidade 8 e tentar inserir o 9º) */
    printf("\nTestando limites da Fila (capacidade %d):\n", CAPACIDADE);
    for (i = 1; i <= 10; i++) {
        if (enfileirar(&f, i * 100)) {
            printf("  Enfileirado com sucesso: %d\n", i * 100);
        } else {
            printf("  FALHA AO ENFILEIRAR %d (Fila cheia no limite)\n", i * 100);
        }
    }
    exibirFila(&f);

    return 0;
}