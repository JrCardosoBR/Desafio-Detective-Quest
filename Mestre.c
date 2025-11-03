#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 7

// BST de pistas
typedef struct Pista {
    char texto[40];
    struct Pista* esq;
    struct Pista* dir;
} Pista;

// Nó da lista encadeada para tabela hash
typedef struct Assoc {
    char pista[40];
    char suspeito[30];
    struct Assoc* prox;
} Assoc;

// Função de espalhamento simples (soma ASCII dos primeiros 3 chars)
int hash(const char* pista) {
    int h = 0;
    for (int i = 0; i < 3 && pista[i] != '\0'; i++) h += pista[i];
    return h % TAM_HASH;
}

Pista* inserirBST(Pista* raiz, const char* texto) {
    if (!raiz) {
        Pista* nova = (Pista*)malloc(sizeof(Pista));
        strcpy(nova->texto, texto);
        nova->esq = nova->dir = NULL;
        return nova;
    }
    if (strcmp(texto, raiz->texto) < 0)
        raiz->esq = inserirBST(raiz->esq, texto);
    else if (strcmp(texto, raiz->texto) > 0)
        raiz->dir = inserirBST(raiz->dir, texto);
    return raiz;
}

void emOrdem(Pista* raiz) {
    if (!raiz) return;
    emOrdem(raiz->esq);
    printf("- %s\n", raiz->texto);
    emOrdem(raiz->dir);
}

void inserirNaHash(Assoc* tabela[], const char* pista, const char* suspeito) {
    int idx = hash(pista);
    Assoc* novo = (Assoc*)malloc(sizeof(Assoc));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[idx];
    tabela[idx] = novo;
}

void listarAssociacoes(Assoc* tabela[]) {
    printf("\nAssociações pista → suspeito:\n");
    for (int i = 0; i < TAM_HASH; i++) {
        Assoc* a = tabela[i];
        while (a) {
            printf("Pista: %s → Suspeito: %s\n", a->pista, a->suspeito);
            a = a->prox;
        }
    }
}

void contarSuspeitos(Assoc* tabela[], char suspeitos[][30], int numSuspeitos, int* contagem) {
    for (int i = 0; i < TAM_HASH; i++) {
        Assoc* a = tabela[i];
        while (a) {
            for (int j = 0; j < numSuspeitos; j++) {
                if (strcmp(a->suspeito, suspeitos[j]) == 0) contagem[j]++;
            }
            a = a->prox;
        }
    }
}

void liberarBST(Pista* raiz) {
    if (!raiz) return;
    liberarBST(raiz->esq);
    liberarBST(raiz->dir);
    free(raiz);
}

void liberarHash(Assoc* tabela[]) {
    for (int i = 0; i < TAM_HASH; i++) {
        Assoc* a = tabela[i];
        while (a) {
            Assoc* temp = a;
            a = a->prox;
            free(temp);
        }
    }
}

int main() {
    // Suspeitos possíveis
    char suspeitos[4][30] = {"Sr. Black", "Sra. White", "Coronel Mustard", "Prof. Plum"};
    int numSuspeitos = 4;
    // Monta a árvore binária de cômodos
    // ...similar ao nível anterior...
    // Para simplificação, pistas e suspeitos são fixos
    const char* pistasSalas[][2] = {
        {"Cozinha", "Pegada de lama"},
        {"Biblioteca", "Livro rasgado"},
        {"Sala de Jantar", "Copo quebrado"},
        {"Escritório", "Envelope misterioso"}
    };
    const char* suspeitosPistas[] = {
        "Sr. Black", "Sra. White", "Coronel Mustard", "Prof. Plum"
    };
    Pista* pistasBST = NULL;
    Assoc* tabelaHash[TAM_HASH] = {0};
    // Insere pistas e associações
    for (int i = 0; i < 4; i++) {
        pistasBST = inserirBST(pistasBST, pistasSalas[i][1]);
        inserirNaHash(tabelaHash, pistasSalas[i][1], suspeitosPistas[i]);
    }
    printf("Pistas encontradas (ordem alfabética):\n");
    emOrdem(pistasBST);
    listarAssociacoes(tabelaHash);
    // Conta suspeitos
    int contagem[4] = {0};
    contarSuspeitos(tabelaHash, suspeitos, numSuspeitos, contagem);
    int max = 0, idxMax = 0;
    for (int i = 0; i < numSuspeitos; i++) {
        if (contagem[i] > max) { max = contagem[i]; idxMax = i; }
    }
    printf("\nSuspeito mais citado: %s (%d pistas)\n", suspeitos[idxMax], max);
    liberarBST(pistasBST);
    liberarHash(tabelaHash);
    return 0;
}