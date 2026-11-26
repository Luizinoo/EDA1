/* PC7 EDA1 Aula 19 — ANSI C.
   Comparacoes contam apenas testes entre valores do vetor/chave.
   Movimentacoes contam escritas em v: duas por troca; deslocamentos e
   colocacao da chave no Insertion Sort. Limite: 0 <= n <= 100. */
#include <stdio.h>
#include <stddef.h>

void selectionSort(int v[], int n, int *comparacoes, int *movimentacoes)
{
    int i, j, min_idx, temp;
    *comparacoes = 0;
    *movimentacoes = 0;

    if (n <= 0 || v == NULL) {
        return;
    }

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = v[i];
            v[i] = v[min_idx];
            v[min_idx] = temp;
            (*movimentacoes) += 2; /* Cada troca real equivale a 2 escritas em v */
        }
    }
}

void bubbleSort(int v[], int n, int *comparacoes, int *movimentacoes)
{
    int i, j, trocou, temp;
    *comparacoes = 0;
    *movimentacoes = 0;

    if (n <= 0 || v == NULL) {
        return;
    }

    for (i = 0; i < n - 1; i++) {
        trocou = 0;
        for (j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                (*movimentacoes) += 2; /* Cada troca real equivale a 2 escritas em v */
                trocou = 1;
            }
        }
        if (!trocou) {
            break; /* Otimização: se não houve trocas, o vetor já está ordenado */
        }
    }
}

void insertionSort(int v[], int n, int *comparacoes, int *movimentacoes)
{
    int i, j, chave;
    *comparacoes = 0;
    *movimentacoes = 0;

    if (n <= 0 || v == NULL) {
        return;
    }

    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        /* Enquanto não chegar ao início e o elemento for maior que a chave */
        while (j >= 0) {
            (*comparacoes)++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                (*movimentacoes)++; /* Cada deslocamento conta como 1 escrita em v */
                j--;
            } else {
                break;
            }
        }
        /* Se a condição do while falhou na primeira verificação, conta a comparação correspondente */
        if (j >= 0 && v[j] <= chave) {
            /* Nota: se o loop quebrou no else, a última comparação já foi contabilizada dentro do while */
        }

        /* Insere a chave na posição correta se ela foi movimentada ou reposicionada */
        v[j + 1] = chave;
        (*movimentacoes)++; /* A colocação da chave conta como 1 escrita em v */
    }
}

typedef void (*SortFunction)(int [], int, int *, int *);
typedef struct {
    const char *nome;
    const int *entrada;
    const int *esperado;
    int n;
    int comparacoes[3];
    int movimentacoes[3];
} Caso;

static int executarTeste(const char *nome, SortFunction ordenar,
                         const int entrada[], int n, const int esperado[],
                         int compEsperadas, int movEsperadas)
{
    int v[100], i, comparacoes, movimentacoes, ok;
    for (i = 0; i < n; i++)
        v[i] = entrada[i];
    comparacoes = 9999;
    movimentacoes = 9999;
    if (n == 0)
        ordenar(NULL, 0, &comparacoes, &movimentacoes);
    else
        ordenar(v, n, &comparacoes, &movimentacoes);
    ok = 1;
    for (i = 0; i < n; i++)
        if (v[i] != esperado[i])
            ok = 0;
    if (compEsperadas >= 0 && comparacoes != compEsperadas)
        ok = 0;
    if (movEsperadas >= 0 && movimentacoes != movEsperadas)
        ok = 0;
    printf("%-22s esperado %d/%d | obtido %d/%d | %s\n", nome,
           compEsperadas, movEsperadas, comparacoes, movimentacoes,
           ok ? "OK" : "FALHOU");
    return ok;
}

static int executarSuite(SortFunction ordenar, int indice,
                        const Caso casos[], int quantidade)
{
    int i, passou;
    passou = 0;
    for (i = 0; i < quantidade; i++)
        passou += executarTeste(casos[i].nome, ordenar, casos[i].entrada,
                                casos[i].n, casos[i].esperado,
                                casos[i].comparacoes[indice],
                                casos[i].movimentacoes[indice]);
    return passou;
}
int main(void)
{
    static const int crescente[5] = {1,2,3,4,5};
    static const int reverso[5] = {5,4,3,2,1};
    static const int exemplo[5] = {29,10,14,37,13};
    static const int ordenadoExemplo[5] = {10,13,14,29,37};
    static const int duplicatas[5] = {4,2,4,1,2};
    static const int ordenadoDuplicatas[5] = {1,2,2,4,4};
    static const int negativos[5] = {0,-3,-1,2,-3};
    static const int ordenadoNegativos[5] = {-3,-3,-1,0,2};
    static const int iguais[4] = {5,5,5,5};
    static const int um[1] = {7};
    static const Caso casos[] = {
      {"vazio", NULL, NULL, 0, {0,0,0}, {0,0,0}},
      {"um elemento", um, um, 1, {0,0,0}, {0,0,0}},
      {"ja ordenado", crescente, crescente, 5, {10,4,4}, {0,0,4}},
      {"ordem inversa", reverso, crescente, 5, {10,10,10}, {4,20,14}},
      {"exemplo V", exemplo, ordenadoExemplo, 5, {10,10,8}, {6,10,9}},
      {"valores repetidos", duplicatas, ordenadoDuplicatas, 5, {10,10,8}, {4,12,10}},
      {"valores negativos", negativos, ordenadoNegativos, 5, {10,10,8}, {6,12,9}},
      {"todos iguais", iguais, iguais, 4, {6,3,3}, {0,0,3}}
    };
    SortFunction funcoes[3];
    const char *nomes[3];
    int entrada100[100], esperado100[100];
    int i, k, passou, total, comp100[3], mov100[3];
    funcoes[0] = selectionSort; funcoes[1] = bubbleSort; funcoes[2] = insertionSort;
    nomes[0] = "Selection Sort"; nomes[1] = "Bubble Sort"; nomes[2] = "Insertion Sort";
    passou = 0; total = 0;
    for (k = 0; k < 3; k++) {
        printf("\n%s\n", nomes[k]);
        passou += executarSuite(funcoes[k], k, casos,
                               (int)(sizeof(casos) / sizeof(casos[0])));
        total += (int)(sizeof(casos) / sizeof(casos[0]));
    }
    for (i = 0; i < 100; i++) {
        entrada100[i] = 100 - i;
        esperado100[i] = i + 1;
    }
    comp100[0] = 4950; comp100[1] = 4950; comp100[2] = 4950;
    mov100[0] = 100; mov100[1] = 9900; mov100[2] = 5049;
    for (k = 0; k < 3; k++) {
        passou += executarTeste("100 em ordem inversa", funcoes[k], entrada100,
                                100, esperado100, comp100[k], mov100[k]);
        total++;
    }
    printf("\n%d de %d testes passaram.\n", passou, total);
    return passou == total ? 0 : 1;
}