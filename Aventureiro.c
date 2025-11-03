#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de nó da árvore binária de cômodos
typedef struct Sala {
    char nome[40];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura de nó da BST de pistas
typedef struct Pista {
    char texto[40];
    struct Pista* esq;
    struct Pista* dir;
} Pista;

// Cria uma sala (nó) da árvore
typedef struct {
    Sala* sala;
    const char* pista; // NULL se não há pista
} SalaComPista;

Sala* criarSala(const char* nome, Sala* esq, Sala* dir) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (!nova) { printf("Erro de alocação!\n"); exit(1); }
    strcpy(nova->nome, nome);
    nova->esquerda = esq;
    nova->direita = dir;
    return nova;
}

Pista* inserir(Pista* raiz, const char* texto) {
    if (!raiz) {
        Pista* nova = (Pista*)malloc(sizeof(Pista));
        strcpy(nova->texto, texto);
        nova->esq = nova->dir = NULL;
        return nova;
    }
    if (strcmp(texto, raiz->texto) < 0)
        raiz->esq = inserir(raiz->esq, texto);
    else if (strcmp(texto, raiz->texto) > 0)
        raiz->dir = inserir(raiz->dir, texto);
    return raiz;
}

void emOrdem(Pista* raiz) {
    if (!raiz) return;
    emOrdem(raiz->esq);
    printf("- %s\n", raiz->texto);
    emOrdem(raiz->dir);
}

void explorarSalas(Sala* atual, Pista** pistas) {
    char escolha;
    while (atual) {
        printf("\nVocê está em: %s\n", atual->nome);
        // Ao visitar certas salas, adiciona pistas
        if (strcmp(atual->nome, "Cozinha") == 0) {
            printf("Você encontrou uma pista: 'Pegada de lama'\n");
            *pistas = inserir(*pistas, "Pegada de lama");
        } else if (strcmp(atual->nome, "Biblioteca") == 0) {
            printf("Você encontrou uma pista: 'Livro rasgado'\n");
            *pistas = inserir(*pistas, "Livro rasgado");
        } else if (strcmp(atual->nome, "Sala de Jantar") == 0) {
            printf("Você encontrou uma pista: 'Copo quebrado'\n");
            *pistas = inserir(*pistas, "Copo quebrado");
        } else if (strcmp(atual->nome, "Escritório") == 0) {
            printf("Você encontrou uma pista: 'Envelope misterioso'\n");
            *pistas = inserir(*pistas, "Envelope misterioso");
        }
        if (!atual->esquerda && !atual->direita) {
            printf("Fim do caminho! Sala final.\n");
            break;
        }
        printf("Escolha: (e) esquerda, (d) direita, (p) listar pistas, (s) sair: ");
        scanf(" %c", &escolha);
        if (escolha == 'e' && atual->esquerda) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita) {
            atual = atual->direita;
        } else if (escolha == 'p') {
            printf("\nPistas encontradas (ordem alfabética):\n");
            emOrdem(*pistas);
        } else if (escolha == 's') {
            printf("Saindo da exploração.\n");
            break;
        } else {
            printf("Opção inválida ou caminho inexistente!\n");
        }
    }
}

void liberarPistas(Pista* raiz) {
    if (!raiz) return;
    liberarPistas(raiz->esq);
    liberarPistas(raiz->dir);
    free(raiz);
}

int main() {
    // Monta a árvore binária estaticamente
    Sala* cozinha = criarSala("Cozinha", NULL, NULL);
    Sala* biblioteca = criarSala("Biblioteca", NULL, NULL);
    Sala* salaJantar = criarSala("Sala de Jantar", NULL, NULL);
    Sala* escritorio = criarSala("Escritório", NULL, NULL);
    Sala* salaEstar = criarSala("Sala de Estar", cozinha, biblioteca);
    Sala* corredor = criarSala("Corredor", salaJantar, escritorio);
    Sala* hallEntrada = criarSala("Hall de Entrada", salaEstar, corredor);

    Pista* pistas = NULL;
    printf("Bem-vindo à Mansão!\n");
    explorarSalas(hallEntrada, &pistas);

    liberarPistas(pistas);
    free(cozinha);
    free(biblioteca);
    free(salaJantar);
    free(escritorio);
    free(salaEstar);
    free(corredor);
    free(hallEntrada);
    return 0;
}