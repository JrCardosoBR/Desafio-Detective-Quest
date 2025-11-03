#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de nó da árvore binária
typedef struct Sala {
    char nome[40];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Cria uma sala (nó) da árvore
Sala* criarSala(const char* nome, Sala* esq, Sala* dir) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (!nova) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = esq;
    nova->direita = dir;
    return nova;
}

// Explora as salas interativamente
void explorarSalas(Sala* atual) {
    char escolha;
    while (atual) {
        printf("\nVocê está em: %s\n", atual->nome);
        if (!atual->esquerda && !atual->direita) {
            printf("Fim do caminho! Sala final.\n");
            break;
        }
        printf("Escolha: (e) esquerda, (d) direita, (s) sair: ");
        scanf(" %c", &escolha);
        if (escolha == 'e' && atual->esquerda) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("Saindo da exploração.\n");
            break;
        } else {
            printf("Opção inválida ou caminho inexistente!\n");
        }
    }
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

    printf("Bem-vindo à Mansão!\n");
    explorarSalas(hallEntrada);

    // Libera memória
    free(cozinha);
    free(biblioteca);
    free(salaJantar);
    free(escritorio);
    free(salaEstar);
    free(corredor);
    free(hallEntrada);
    return 0;
}