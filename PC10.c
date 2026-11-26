
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *esq;
    struct No *dir;
} No;

/* Cria e inicializa um novo nó */
No *criarNo(int chave) {
    No *novo;

    novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return NULL;
    }

    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

/* Insere uma chave mantendo a propriedade da ABB */
No *inserir(No *raiz, int chave) {
    if (raiz == NULL) {
        return criarNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = inserir(raiz->dir, chave);
    }

    /* Se a chave for igual, nao insere duplicata */
    return raiz;
}

/* Busca uma chave na ABB */
No *buscar(No *raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    }

    if (chave == raiz->chave) {
        return raiz;
    }

    if (chave < raiz->chave) {
        return buscar(raiz->esq, chave);
    }

    return buscar(raiz->dir, chave);
}

/* Percurso em ordem: esquerda, raiz, direita */
void emOrdem(No *raiz) {
    if (raiz == NULL) {
        return;
    }

    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
}

/* Libera todos os nos da arvore */
void liberarArvore(No *raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);

    free(raiz);
}

int main(void) {
    No *raiz = NULL;
    No *resultado;
    int chaves[] = {50, 30, 70, 20, 40, 60, 80, 35};
    int i;
    int quantidade;

    quantidade = sizeof(chaves) / sizeof(chaves[0]);

    /* Teste de arvore vazia */
    printf("Teste de arvore vazia:\n");

    if (buscar(raiz, 50) == NULL) {
        printf("Busca em arvore vazia: NULL\n");
    }

    printf("Percurso em arvore vazia: ");
    emOrdem(raiz);
    printf("(nenhuma chave)\n\n");

    /* Insere as chaves do enunciado */
    for (i = 0; i < quantidade; i++) {
        raiz = inserir(raiz, chaves[i]);
    }

    /* Busca presente */
    printf("Teste de busca presente:\n");
    resultado = buscar(raiz, 35);

    if (resultado != NULL) {
        printf("Chave 35 encontrada.\n");
    } else {
        printf("Chave 35 nao encontrada.\n");
    }

    /* Busca ausente */
    printf("\nTeste de busca ausente:\n");
    resultado = buscar(raiz, 65);

    if (resultado == NULL) {
        printf("Chave 65 nao encontrada.\n");
    } else {
        printf("Chave 65 encontrada.\n");
    }

    /* Percurso em ordem */
    printf("\nPercurso em ordem:\n");
    emOrdem(raiz);
    printf("\n");

    /* Teste de chave repetida */
    printf("\nTeste de chave repetida:\n");
    raiz = inserir(raiz, 40);

    printf("Inserindo 40 novamente:\n");
    emOrdem(raiz);
    printf("\n");

    /* Insercao de nova chave */
    printf("\nTeste de insercao de 65:\n");
    raiz = inserir(raiz, 65);

    printf("Percurso apos inserir 65:\n");
    emOrdem(raiz);
    printf("\n");

    /* Libera toda a memoria */
    liberarArvore(raiz);

    return 0;
}
