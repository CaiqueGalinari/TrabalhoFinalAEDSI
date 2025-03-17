#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTOS 10
#define MAX_NOME 50

// Estrutura para representar um evento
typedef struct {
    char nome[MAX_NOME];
    float avaliacao;
} Evento;

// Estrutura para representar uma cidade (nó da árvore)
typedef struct Cidade {
    char nome[MAX_NOME];
    Evento eventos[MAX_EVENTOS];
    int numEventos;
    struct Cidade *esquerda;
    struct Cidade *direita;
} Cidade;

// Função para criar uma nova cidade
Cidade* criarCidade(char *nome) {
    Cidade *novaCidade = (Cidade *)malloc(sizeof(Cidade));
    strcpy(novaCidade->nome, nome);
    novaCidade->numEventos = 0;
    novaCidade->esquerda = NULL;
    novaCidade->direita = NULL;
    return novaCidade;
}

// Função para inserir uma cidade na árvore
Cidade* inserirCidade(Cidade *raiz, char *nome) {
    if (raiz == NULL) {
        return criarCidade(nome);
    }

    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = inserirCidade(raiz->esquerda, nome);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->direita = inserirCidade(raiz->direita, nome);
    }

    return raiz;
}

// Função para percurso in-order
void percursoInOrder(Cidade *raiz) {
    if (raiz != NULL) {
        percursoInOrder(raiz->esquerda);
        printf("%s\n", raiz->nome);
        percursoInOrder(raiz->direita);
    }
}

// Função para percurso pre-order
void percursoPreOrder(Cidade *raiz) {
    if (raiz != NULL) {
        printf("%s\n", raiz->nome);
        percursoPreOrder(raiz->esquerda);
        percursoPreOrder(raiz->direita);
    }
}

// Função para percurso post-order
void percursoPostOrder(Cidade *raiz) {
    if (raiz != NULL) {
        percursoPostOrder(raiz->esquerda);
        percursoPostOrder(raiz->direita);
        printf("%s\n", raiz->nome);
    }
}

int main() {
    Cidade *raiz = NULL;

    // Inserindo algumas cidades para teste
    raiz = inserirCidade(raiz, "Cidade B");
    raiz = inserirCidade(raiz, "Cidade A");
    raiz = inserirCidade(raiz, "Cidade C");

    printf("\nPercurso In-Order:\n");
    percursoInOrder(raiz);

    printf("\nPercurso Pre-Order:\n");
    percursoPreOrder(raiz);

    printf("\nPercurso Post-Order:\n");
    percursoPostOrder(raiz);

    return 0;
}
