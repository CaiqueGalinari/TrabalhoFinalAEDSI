#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTOS 4
#define MAX_NOME 50
#define TOTAL_CIDADES 10

// Estrutura para representar um evento
typedef struct evento {
    char nome[MAX_NOME];
    char horario[MAX_NOME];
    int nota;
} TEvento;

// Estrutura para representar uma cidade (no da árvore)
typedef struct cidade {
    int chave;
    char nome[MAX_NOME];
    TEvento eventos[MAX_EVENTOS];
    int distanciaEsq;
    int distanciaDir;
} TCidade;

// Estrutura para representar um no da árvore
typedef struct celula {
    TCidade cidade;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
} TCelula;

// Estrutura para representar a arvore
typedef struct arvore {
    TCelula *raiz;
} TArvore;

// Lista de eventos possiveis
const char *nomesEventos[] = {
    "Festival de Musica", "Feira de Artesanato", "Exposicao de Arte", "Show ao Vivo", "Cinema ao Ar Livre",
    "Teatro Comunitario", "Corrida de Rua", "Palestra Motivacional", "Festival de Gastronomia", "Feira de Livros"
};

// Lista de nomes de cidades
const char *nomesCidades[] = {
    "Sao Paulo", "Rio de Janeiro", "Belo Horizonte", "Curitiba", "Porto Alegre",
    "Brasilia", "Salvador", "Recife", "Fortaleza", "Manaus",
    "Belem", "Goiania", "Campinas", "Natal", "Joao Pessoa",
    "Florianopolis", "Sao Luis", "Teresina", "Maceio", "Aracaju"
};

// Funcao para verificar se um evento ja foi adicionado
int eventoRepetido(TEvento eventos[], int totalEventos, const char *nome) {
    for (int i = 0; i < totalEventos; i++) {
        if (strcmp(eventos[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

// Funcao para gerar eventos aleatorios sem repeticao
void gerarEventos(TEvento eventos[]) {
    int totalEventos = 0;
    while (totalEventos < MAX_EVENTOS) {
        int indice = rand() % 10;
        if (!eventoRepetido(eventos, totalEventos, nomesEventos[indice])) {
            strcpy(eventos[totalEventos].nome, nomesEventos[indice]);
            sprintf(eventos[totalEventos].horario, "%02d:%02d", rand() % 24, rand() % 60);
            eventos[totalEventos].nota = rand() % 11; // Nota de 0 a 10
            totalEventos++;
        }
    }
}

// -- INSERIR --
TCelula* criaNo(TCidade Cidade) {
    TCelula* novo = (TCelula*)malloc(sizeof(TCelula));
    if (novo != NULL) {
        novo->cidade = Cidade;
        gerarEventos(novo->cidade.eventos); // Preencher eventos
        novo->cidade.chave = 0;
        for (int i = 0; i < MAX_EVENTOS; i++) {
            novo->cidade.chave += novo->cidade.eventos[i].nota;
        }
        novo->esq = NULL;
        novo->dir = NULL;
        novo->pai = NULL;
    }
    return novo;
}

void Inserir(TCelula **x, TCelula *pai, TCidade Cidade) {
    if ((*x) == NULL) {
        (*x) = criaNo(Cidade);
        if (pai != NULL) {
            (*x)->pai = pai;
        }
        return;
    }

    if ((*x)->cidade.chave > Cidade.chave) {
        Inserir(&(*x)->esq, (*x), Cidade);
    } else {
        Inserir(&(*x)->dir, (*x), Cidade);
    }
}

// Funcao para preencher automaticamente a arvore com 10 cidades
void preencherArvore(TArvore *arvore) {
    for (int i = 0; i < TOTAL_CIDADES; i++) {
        TCidade cidade;
        strcpy(cidade.nome, nomesCidades[rand() % 20]);
        cidade.distanciaEsq = rand() % 500 + 100; // Distancia entre 100 km e 600 km
        cidade.distanciaDir = rand() % 500 + 100;
        gerarEventos(cidade.eventos); // Atribuir eventos
        cidade.chave = 0;
        for (int j = 0; j < MAX_EVENTOS; j++) {
            cidade.chave += cidade.eventos[j].nota;
        }
        Inserir(&arvore->raiz, NULL, cidade);
    }
}

int main() {
    srand(time(NULL));

    TArvore arvore = {NULL};

    preencherArvore(&arvore);

    return 0;
}
