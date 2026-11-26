/* PC8 EDA1 Aula 21 — Listas encadeadas II
 * Complete as quatro operacoes indicadas. Compilacao: cc -std=c90 -Wall -Wextra -pedantic
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

void imprimir(const No *inicio)
{
    const No *atual = inicio;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

No *buscar(No *inicio, int valor)
{
    No *atual = inicio;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

No *inserirFim(No *inicio, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        /* Falha de malloc: mantém a lista original intacta */
        return inicio;
    }
    novo->valor = valor;
    novo->prox = NULL;

    if (inicio == NULL) {
        return novo;
    }

    {
        No *atual = inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    return inicio;
}

No *removerPrimeiro(No *inicio, int valor)
{
    if (inicio == NULL) {
        return NULL;
    }

    /* Caso o valor esteja no primeiro nó (cabeça) */
    if (inicio->valor == valor) {
        No *remover = inicio;
        inicio = inicio->prox;
        free(remover);
        return inicio;
    }

    {
        No *atual = inicio;
        while (atual->prox != NULL && atual->prox->valor != valor) {
            atual = atual->prox;
        }

        /* Se encontrou o valor nos nós posteriores */
        if (atual->prox != NULL) {
            No *remover = atual->prox;
            atual->prox = remover->prox;
            free(remover);
        }
    }

    return inicio;
}

void liberarLista(No *inicio)
{
    No *proximo;
    while (inicio != NULL) {
        proximo = inicio->prox;
        free(inicio);
        inicio = proximo;
    }
}

int main(void)
{
    No *inicio;
    No *resultado;
    inicio = NULL;
    inicio = inserirFim(inicio, 12);
    inicio = inserirFim(inicio, 7);
    inicio = inserirFim(inicio, 19);
    imprimir(inicio);
    resultado = buscar(inicio, 7);
    if (resultado != NULL) printf("Encontrado: %d\n", resultado->valor);
    inicio = removerPrimeiro(inicio, 12);
    imprimir(inicio);
    liberarLista(inicio);
    return 0;
}