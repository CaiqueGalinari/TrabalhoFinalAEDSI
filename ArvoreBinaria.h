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
// ^ Estrutura básica (precisa mecher em TCidade para ficar como ele pede)

//Vou escrever as fuções básicas:

// -- CAMINHAMENTOS --
//Permitem imprimir todas as chaves em uma sequência ordenada
//Caminhamento central ou caminhamento in-ordem
void Central(TCelula *x){
    if(x != NULL){
        Central(x->esq);
        printf("%d ", x->cidade.chave); //Modificar aqui quando modificar a TCidade
        Central(x->dir);
    }
}

//Caminhamento em pré-ordem.
void PreOrdem(TCelula *x){
    if(x != NULL){
        printf("%d ", x->cidade.chave); //Modificar aqui quando modificar a TCidade
        PreOrdem(x->esq);
        PreOrdem(x->dir);
    }
}

//Caminhamento em pós-ordem.
void PosOrdem(TCelula *x){
    if(x != NULL){
        PosOrdem(x->esq);
        PosOrdem(x->dir);
        printf("%d ", x->cidade.chave); //Modificar aqui quando modificar a TCidade
    }
}


// -- BUSCA --
TCelula* Pesquisar(TCelula *x, TCidade Cidade){
    if((x == NULL)||(x->cidade.chave == Cidade.chave)){
        return x;
    }
    if(Cidade.chave < x->cidade.chave){
        return Pesquisar(x->esq, Cidade);
    } else if(Cidade.chave > x->cidade.chave){
        return Pesquisar(x->dir, Cidade);
    }
}


// -- MÍNIMO E MÁXIMO --
//Máximo
TCelula* Maximo(TCelula *x){
    if(x == NULL){
        return NULL;
    }
    while(x->dir != NULL){
        x = x->dir;
    }
    return x;
}

//Mínimo
TCelula* Minimo(TCelula *x){
    if(x == NULL){
        return NULL;
    }
    while(x->esq != NULL){
        x = x->esq;
    }
    return x;
}


// -- SUCESSOR E PREDECESSOR --
//Sucessor
TCelula* Sucessor(TCelula *x){
    if(x == NULL){
        return NULL;
    }
    if(x->dir != NULL){
        return Minimo(x->dir);
    }

    TCelula *y = x->pai;
    while (y != NULL && x == y->dir){
        x = y;
        y = y->pai;
    }
    return y;
}

//Predecessor
TCelula* Predecessor(TCelula *x){
    if(x == NULL){
        return NULL;
    }
    if(x->esq != NULL){
        return Maximo(x->esq);
    }

    TCelula *y = x->pai;
    while (y != NULL && x == y->esq){
        x = y;
        y = y->pai;
    }
    return y;
}
