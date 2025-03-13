#include <stdio.h>
#include <stdlib.h>

typedef struct cidade{
    int chave;
}TCidade;

typedef struct celula{
    TCidade cidade;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
}TCelula;

typedef struct arvore{
    TCelula *raiz;
}TArvore;
