#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTOS 4
#define MAX_NOME 50
#define TOTAL_CIDADES 10

// -- BEM VINDO À BIBLIOTECA ArvoreBinaria.h --
//Estaremos utilizando a árvore como forma de armazenar e buscar, mas também como forma de "desenho", ou seja, o desenho da árvore vai definir a disposição das cidades
//Comentários para entendimento interno e do professor

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

// *** FUNÇÕES BÁSICAS (slides):

// -- CAMINHAMENTOS --
//Permitem imprimir todas as chaves em uma sequência ordenada
//>>Se for usado na interface, lembrar de imprimir os evendos também (com a nota deles)
//Ex.: 
//São Paulo:
//Feira de Arte - (10)

//Caminhamento central ou caminhamento in-ordem
void Central(TCelula *x){
    if(x != NULL){
        Central(x->esq);
        printf("%d ", x->cidade.chave);
        Central(x->dir);
    }
}

//Caminhamento em pré-ordem.
void PreOrdem(TCelula *x){
    if(x != NULL){
        printf("%d ", x->cidade.chave);
        PreOrdem(x->esq);
        PreOrdem(x->dir);
    }
}

//Caminhamento em pós-ordem.
void PosOrdem(TCelula *x){
    if(x != NULL){
        PosOrdem(x->esq);
        PosOrdem(x->dir);
        printf("%d ", x->cidade.chave);
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
//Será usado na ordenação, uma vez que a árvore será gerada aleatoriamente
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

// *** FUNÇÕES ALEATÓRIAS

//Bancos de nomes para escolher aleatoriamente
const char *nomesEventos[] = {
    "Festival de Musica", "Feira de Artesanato", "Exposicao de Arte", "Show ao Vivo", "Cinema ao Ar Livre",
    "Teatro Comunitario", "Corrida de Rua", "Palestra Motivacional", "Festival de Gastronomia", "Feira de Livros"
};

//Baseados em nomes de cidades reais, modifiquei pq n faz sentido "Rio de Janeiro" estar a 20km de "Fortaleza"
const char *nomesCidades[] = {
    "Sao Vicente", "Rio de Março", "Lindo Horizonte", "Coolritiba", "Porto da Felicidade",
    "Brasilica", "Salvador Dali", "Corais", "Castelo", "Mananeus",
    "Betem", "Goiasia", "Campinhos", "Natalnael", "Joao Humano",
    "Flor e Ópolis", "Dom Luis", "Teresinha", "Marceló", "Plantacaju"
};

//Evento repetido
int eventoRepetido(TEvento eventos[], int totalEventos, const char *nome) {
    for (int i = 0; i < totalEventos; i++) {
        if (strcmp(eventos[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

//Eventos aleatórios, com horário e nota
void gerarEventos(TEvento eventos[]) {
    int totalEventos = 0;
    while (totalEventos < MAX_EVENTOS) {
        int indice = rand() % 10;
        if (!eventoRepetido(eventos, totalEventos, nomesEventos[indice])) {
            strcpy(eventos[totalEventos].nome, nomesEventos[indice]);

            sprintf(eventos[totalEventos].horario, "%02d:%02d", rand() % 24, rand() % 60);

            eventos[totalEventos].nota = rand() % 11;
        }
    }
}

//-- INSERIR ALEATORIO --
//Mesma coisa do insrir normal, só adiciona a parte da aleatoriedade

//criaNo, mas dessa vez define:
//Eventos aleatorios ao criar o no
//Número da chave baseada na nota do evento
TCelula* criaNoAleatorio(TCidade Cidade) {
    TCelula* novo = (TCelula*)malloc(sizeof(TCelula));
    if (novo != NULL) {
        novo->cidade = Cidade;

        gerarEventos(novo->cidade.eventos);
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

//Mesma ideia do criaNoaleatorio
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

// -- PRÉ GERAR A ÁRVORE --
// Não vamos dar opção de fazer isso sem ser aleatório por falta de tempo
void preencherArvore(TArvore *arvore) {
    for (int i = 0; i < TOTAL_CIDADES; i++) {
        TCidade cidade;

        strcpy(cidade.nome, nomesCidades[rand() % 20]);

        cidade.distanciaEsq = rand() % 80 + 20;
        cidade.distanciaDir = rand() % 80 + 20;

        gerarEventos(cidade.eventos);
        cidade.chave = 0;
        for (int j = 0; j < MAX_EVENTOS; j++) {
            cidade.chave += cidade.eventos[j].nota;
        }

        InserirAleatorio(&arvore->raiz, NULL, cidade);
    }
}

// -- FUNÇÕES DE ORDENAÇÃO --


// -- FUNÇÕES DE BUSCA --

// Função para encontrar a melhor rota considerando nota e distância
//PROVISÓRIA, PRECISO DELA PARA FAZER O SISTEMA DE CAIXEIRO VIAJANTE
void encontrarMelhorRota(TCelula *raiz, char eventosEscolhidos[][MAX_NOME], int totalEventos) {
    TCelula *cidadesEscolhidas[MAX_EVENTOS];
    int horarios[MAX_EVENTOS];

    for (int i = 0; i < totalEventos; i++) {
        cidadesEscolhidas[i] = buscarEvento(raiz, eventosEscolhidos[i]);
        if (cidadesEscolhidas[i]) {
            horarios[i] = atoi(cidadesEscolhidas[i]->cidade.eventos[i].horario);
        }
    }

// -- CAIXEIRO VIAJANTE MIRIM -- 
//Nome dado porque o caixeiro não precisa voltar ao ponto inicial, só descobrir a melhor rota
