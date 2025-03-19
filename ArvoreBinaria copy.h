#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTOS 4
#define MAX_NOME 50
#define TOTAL_CIDADES 10

typedef struct evento {
    char nome[MAX_NOME];
    char horario[MAX_NOME];
    int nota;
} TEvento;

typedef struct cidade {
    int chave;
    char nome[MAX_NOME];
    TEvento eventos[MAX_EVENTOS];
    int distanciaEsq;
    int distanciaDir;
} TCidade;

typedef struct celula {
    TCidade cidade;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
} TCelula;

typedef struct arvore{
    TCelula *raiz;
}TArvore;
// ^ Estrutura básica (precisa mecher em TCidade para ficar como ele pede)

//fuções básicas:

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

// -- INSERIR --
//CriaNo
TCelula* criaNo(TCidade Cidade) {
    TCelula* novo = (TCelula*)malloc(sizeof(TCelula));
    if (novo != NULL) {
        novo->cidade = Cidade;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->pai = NULL;
    }
    return novo;
}

//Inserir
void Inserir(TCelula **x, TCelula *pai, TCidade Cidade){
    if((*x) == NULL){
        (*x) = criaNo(Cidade);
        if(pai != NULL){
            (*x)->pai = pai;
        }
        return;
    }

    if((*x)->cidade.chave > Cidade.chave){
        Inserir(&(*x)->esq, (*x), Cidade);
        return;
    }
    
    if((*x)->cidade.chave <= Cidade.chave){
        Inserir(&(*x)->dir, (*x), Cidade);
    }
}

// -- RETIRAR -- 
//Transplante (trocar nós)
void Transplante(TArvore *Arvore, TCelula **u, TCelula **v){
    if((*u)->pai == NULL){
        Arvore->raiz = (*v);
    } else if((*u) == (*u)->pai->esq){
        (*u)->pai->esq = (*v);
    } else{
        (*u)->pai->dir = (*v);
    }

    if((*v) != NULL){
        (*v)->pai = (*u)->pai;
    }
}

//Retirar
void Retirar(TArvore *Arvore, TCelula **z){
    if(*z == NULL){
        printf("\n>>>>>>AVISO: NO' \"Z\" E' NULO! <<<<<<");
        return;
    }
    if((*z)->esq == NULL){
        Transplante(Arvore, z, &(*z)->dir);
    }else if((*z)->dir == NULL){
        Transplante(Arvore, z, &(*z)->esq);
    } else{
        TCelula *y = Minimo((*z)->dir);
        if(y->pai != (*z)){
            Transplante(Arvore, &y, &y->dir);
            y->dir->pai = y;
        }
        Transplante(Arvore, z, &y);
        y->esq = (*z)->esq;
        y->esq->pai = y;
    }
    free(*z);
    *z = NULL;
}

//FUNÇÕES ALEATÓRIAS

const char *nomesEventos[] = {
    "Festival de Musica", "Feira de Artesanato", "Exposicao de Arte", "Show ao Vivo", "Cinema ao Ar Livre",
    "Teatro Comunitario", "Corrida de Rua", "Palestra Motivacional", "Festival de Gastronomia", "Feira de Livros"
};

const char *nomesCidades[] = {
    "Sao Paulo", "Rio de Janeiro", "Belo Horizonte", "Curitiba", "Porto Alegre",
    "Brasilia", "Salvador", "Recife", "Fortaleza", "Manaus",
    "Belem", "Goiania", "Campinas", "Natal", "Joao Pessoa",
    "Florianopolis", "Sao Luis", "Teresina", "Maceio", "Aracaju"
};

//1. Função para ver se tem evento repetido
int eventoRepetido(TEvento eventos[], int totalEventos, const char *nome) {
    for (int i = 0; i < totalEventos; i++) {
        if (strcmp(eventos[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

//2. Gera os eventos aleatórios, define o horário e a nota deles
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

//3. INSERIR ALEATORIO
TCelula* criaNoAleatorio(TCidade Cidade) {
    TCelula* novo = (TCelula*)malloc(sizeof(TCelula));
    if (novo != NULL) {
        novo->cidade = Cidade;

        gerarEventos(novo->cidade.eventos); // Preencher eventos
        novo->cidade.chave = 0;

        for (int i = 0; i < MAX_EVENTOS; i++) {
            novo->cidade.chave += novo->cidade.eventos[i].nota; //Define o valor da chave
        }

        novo->esq = NULL;
        novo->dir = NULL;
        novo->pai = NULL;
    }
    return novo;
}

void InserirAleatorio(TCelula **x, TCelula *pai, TCidade Cidade) {
    if ((*x) == NULL) {
        (*x) = criaNoAleatorio(Cidade);
        if (pai != NULL) {
            (*x)->pai = pai;
        }
        return;
    }

    if ((*x)->cidade.chave > Cidade.chave) {
        InserirAleatorio(&(*x)->esq, (*x), Cidade);
    } else {
        InserirAleatorio(&(*x)->dir, (*x), Cidade);
    }
}

void preencherArvore(TArvore *arvore) {
    for (int i = 0; i < TOTAL_CIDADES; i++) {
        TCidade cidade;

        strcpy(cidade.nome, nomesCidades[rand() % 20]);

        cidade.distanciaEsq = rand() % 595 + 5; // Distancia entre 5 km e 600 km
        cidade.distanciaDir = rand() % 595 + 5;

        gerarEventos(cidade.eventos); // Atribuir eventos
        cidade.chave = 0;

        for (int j = 0; j < MAX_EVENTOS; j++) {
            cidade.chave += cidade.eventos[j].nota;
        }

        InserirAleatorio(&arvore->raiz, NULL, cidade);
    }
}