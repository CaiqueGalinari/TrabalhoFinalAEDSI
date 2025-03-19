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

// ********************************************************************** FUNÇÕES BÁSICAS (slides): **********************************************************************

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

// ********************************************************************** FUNÇÕES ALEATÓRIAS: **********************************************************************

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
//^^^^ Modificar quando forem colocados os metodos de ordenação


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

// ********************************************************************** FUNÇÕES DE ORDENAÇÃO **********************************************************************
//PARA ORDENAR OS EVENTOS DENTRO DA CIDADE DO MELHOR (10) PARA O PIOR (0)


// ********************************************************************** FUNÇÕES DE BUSCA **********************************************************************

//PROVISÓRIA, PRECISO DELA PARA FAZER O SISTEMA DE CAIXEIRO VIAJANTE
// Função para buscar um evento na árvore e retornar a cidade/célula da cidade
void buscarCidadesComEvento(TCelula *raiz, const char *eventoNome, TCelula *resultados[], int indices[], int *contador) {
    if (raiz == NULL) return; //se a célula for NULL, não tem o que fazer mais
    for (int i = 0; i < MAX_EVENTOS; i++) {
        if (strcmp(raiz->cidade.eventos[i].nome, eventoNome) == 0) {
            //Se o nome do evento "i" for igual ao nome do evento que queremos, então:
            resultados[*contador] = raiz; //preenche uma posição do vetor com a célula que tem o evento
            indices[*contador] = i; // Armazena o índice correto do evento para cada cidade
            (*contador)++; //próxima posição do vetor
            break; //Para o loop assim que encontra o evento
        }
    }

    //repete o processo para todas as células da árvore, armazenando todas que tem o evento que queremos
    buscarCidadesComEvento(raiz->esq, eventoNome, resultados, indices, contador);
    buscarCidadesComEvento(raiz->dir, eventoNome, resultados, indices, contador);
}

// ********************************************************************** CAIXEIRO VIAJANTE MIRIM ********************************************************************** 
//Nome dado porque o caixeiro não precisa voltar ao ponto inicial, só descobrir a melhor rota

//Hora p min, esse deu mais trabalho do que parece kkkkkkkkkk
int converterHorarioParaMinutos(const char *horario) {
    int horas, minutos;
    sscanf(horario, "%d:%d", &horas, &minutos);
    return horas * 60 + minutos;
}

//Para cálculos futuros
int calcularTempoViagem(int distancia) {
    return distancia * 60 / 50;
    //distância em km
    //multiplica por 60 para ter o tempo em minutos, mas no caso deveria ser depois, multiplico antes por medo de dar problema com decimal, divide por 50, pq adotaremos 50km/h como velocidade
    //Queremos em minutos por causa da particularidade da hora (60min = 1h e não 100min = 1h)
}

//Necessário para ver qual rota tomar
int calcularDistanciaAteRaiz(TCelula *cidade) {
    int distancia = 0; //Variável em que as distâncias vão se acumular
    TCelula *atual = cidade; //A cidade que será analisada a distância entre ela e a raiz
    while (atual->pai != NULL) {
        if (atual == atual->pai->esq) {
            // Se a cidade atual for a cidade à esquerda da cidade pai, então:
            distancia += atual->pai->cidade.distanciaEsq; //(Acumula a distância dela até a cidade pai)
        } else {
            // Se estiver à direita
            distancia += atual->pai->cidade.distanciaDir; //(Acumula a distância dela até a cidade pai)
        }
        atual = atual->pai;
    }
    return distancia; // Retorna a distância entre essa cidade e a raiz
}

// Essa será usada para otimizar, quebrei bastante a cabeça, porque anteriormente a função abaixo obrigava todas a passarem pela raiz, calculando um tempo impreciso
TCelula* encontrarAncestralComum(TCelula* a, TCelula* b) {
    while (a != b) {
        if (a->pai == NULL) {return a;} //Se a for a raiz, retorna a
        if (b->pai == NULL) {return b;} //Se b for a raiz, retorna b

        if (a == b) {return a;}

        //Se a estiver mais longe da raiz que b, então a recebe seu pai
        if (calcularDistanciaAteRaiz(a) > calcularDistanciaAteRaiz(b)) a = a->pai;
        //Do contrário b recebe seu pai
        else b = b->pai;
        //Isso vai se repetir até que sejam iguais, ou seja, sejam o ancestral comum um do outro
    }
    return a;
}

void encontrarMelhorRota(TArvore *arvore, char (*eventosEscolhidos)[MAX_NOME], int totalEventos) {
    //Se a raiz for nula, então a arvore não existe, precisa reiniciar aplicativo
    if (arvore->raiz == NULL) {
        printf("Erro: Árvore vazia. Reinicie o aplicativo.\n");
        return;
    }
    
    //Variáveis que serão usadas
    TCelula *cidadesEscolhidas[MAX_EVENTOS]; //Armazenará as cidades da rota
    int indicesEventos[MAX_EVENTOS]; // guarda o indice do evento dentro da cidade
    int tempoAtual = 0; //tempo total da rota
    
    TCelula *opcoes[MAX_EVENTOS]; //Guarda cidades onde o evento está disponível
    int indices[MAX_EVENTOS]; // Guarda o indice do evento dentro da cidade
    int contador = 0; // Conta quantas cidades possuem o evento

    for (int i = 0; i < totalEventos; i++) { //percorre todos os eventos escolhidos

        //Procura e armazena todas as cidades que têm o evento em questão
        buscarCidadesComEvento(arvore->raiz, eventosEscolhidos[i], opcoes, indices, &contador);
        
        //Se o contador for 0, quer dizer que o evento não foi encontrado
        if (contador == 0) {
            printf("Erro: Evento '%s' não encontrado.\n", eventosEscolhidos[i]);
            return;
        }
        
        //1 ESCOLHE A ROTA COM BASE NA NOTA
        //2 SE NÃO FOR POSSÍVEL, ESCOLHE A ROTA COM BASE NA ROTA MAIS RÁPIDA, IGNORANDO A NOTA

        int melhorIndice = 0; //Armazena o indice da melhor cidade encontrada até agora (a princípio a primeira)
        //Lembrando que o contador é o numero de cidades total que possuem o evento

        // ***** 1.:
        for (int j = 1; j < contador; j++) { //percorre todas as cidades onde o evento está disponível

            //indices[melhorIndice] é o indice do evento, opcoes[melhorIndice é o indice da cidade]
            int notaAtual = opcoes[melhorIndice]->cidade.eventos[indices[melhorIndice]].nota; //Pega a melhor nota até agora

            int notaNova = opcoes[j]->cidade.eventos[indices[j]].nota; //Pega a nota da próxima cidade (por isso j começa em 1)

            int distanciaAtual = calcularDistanciaAteRaiz(opcoes[melhorIndice]); // Calcula a distância até a raiz da cidade com a melhor nota
            int distanciaNova = calcularDistanciaAteRaiz(opcoes[j]); // Calcula a distância até a raiz da próxima cidade
            
            //Aqui é interessante, se a nota da próxima cidade é maior
            //OU se a nota das duas for igual, a que for mais perto é  escolhida
            if (notaNova > notaAtual || (notaNova == notaAtual && distanciaNova < distanciaAtual)) {
                melhorIndice = j;
            }
        }

        cidadesEscolhidas[i] = opcoes[melhorIndice]; // A cidade escolhida é passada para o vetor das cidades
        indicesEventos[i] = indices[melhorIndice]; // O indice dos eventos também é passado (para que não o perca)
    }
    
    // Verificar se é possível chegar a tempo ao próximo evento (por nota)
    for (int i = 0; i < totalEventos - 1; i++) {
        TCelula* ancestral = encontrarAncestralComum(cidadesEscolhidas[i], cidadesEscolhidas[i + 1]); //Encontra o ancestral comum entre as cidades escolhidas

        // Calcula a distancia da primeira até a raiz e subtrai com a distancia da ancestral até a raiz, depois soma a esse mesmo processo com a outra cidade sendo comparada
        int distancia = (calcularDistanciaAteRaiz(cidadesEscolhidas[i]) - calcularDistanciaAteRaiz(ancestral)) + (calcularDistanciaAteRaiz(cidadesEscolhidas[i + 1]) - calcularDistanciaAteRaiz(ancestral));
        if (distancia < 0) {distancia = -distancia;} //Manutenção p evitar bug, n tem como ter distância negativa entre cidades
        
        //Calcula o tempo de viagem dessa distância
        int tempoViagem = calcularTempoViagem(distancia);

        int horarioAtual = converterHorarioParaMinutos(cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].horario); //Pega o horario da cidade atual convertendo para minutos

        int horarioProximo = converterHorarioParaMinutos(cidadesEscolhidas[i + 1]->cidade.eventos[indicesEventos[i + 1]].horario); //Mesma coisa, mas com a outra cidade
        
        //Se o horario atual e o tempo de deslocamento for maior que o horario do proximo envento, então não será possível
        if (horarioAtual + tempoViagem > horarioProximo) {
            printf("Não é possível visitar todos os eventos com prioridade na nota. Tentando priorizar o tempo...");
            
            // ***** 2.
            contador = 0; //Reinicia o contador que conta quantas cidades têm o evento
            buscarCidadesComEvento(arvore->raiz, eventosEscolhidos[i], opcoes, indices, &contador); //mesmo processo anterior
            for (int i = 0; i < totalEventos; i++) {
                int melhorIndice = 0;

                for (int j = 1; j < contador; j++) {
                    if (calcularDistanciaAteRaiz(opcoes[j]) < calcularDistanciaAteRaiz(opcoes[melhorIndice])) { //Ao invés de comparar a nota, compara a distância, favorecendo a menor
                        melhorIndice = j;
                    }
                }
                cidadesEscolhidas[i] = opcoes[melhorIndice];
                indicesEventos[i] = indices[melhorIndice];
            }

            // Checar para ver se vai ser possível dar certo, se não for, mostrará um aviso
            int eventoRemovido = -1; //Assumindo que não tem nenhum "empacado"
            for (int i = 0; i < totalEventos - 1; i++) {

                //Mesmo processo de cálculo de distância da linha 460 a 476
                TCelula* ancestral = encontrarAncestralComum(cidadesEscolhidas[i], cidadesEscolhidas[i + 1]);
                int distancia = (calcularDistanciaAteRaiz(cidadesEscolhidas[i]) - calcularDistanciaAteRaiz(ancestral)) + (calcularDistanciaAteRaiz(cidadesEscolhidas[i + 1]) - calcularDistanciaAteRaiz(ancestral));
                if (distancia < 0) distancia = -distancia;
                
                int tempoViagem = calcularTempoViagem(distancia);
                int horarioAtual = converterHorarioParaMinutos(cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].horario);
                int horarioProximo = converterHorarioParaMinutos(cidadesEscolhidas[i + 1]->cidade.eventos[indicesEventos[i + 1]].horario);
                
                if (horarioAtual + tempoViagem > horarioProximo) {
                    //Adiciona 1 ao evento removido e quebra o laço for
                    eventoRemovido = i + 1;
                    break;
                }
            }
            
            if (eventoRemovido != -1) {
                printf("Não é possível visitar todos os eventos desejados. O evento '%s' na cidade '%s' precisará ser removido da rota.", cidadesEscolhidas[eventoRemovido]->cidade.eventos[indicesEventos[eventoRemovido]].nome, cidadesEscolhidas[eventoRemovido]->cidade.nome);
            }
            break;
        }
    }
    
    // Printar a rota
    printf("Melhor rota:\n");
    for (int i = 0; i < totalEventos; i++) {
        printf("%s -> ", cidadesEscolhidas[i]->cidade.nome);
    }
    printf("FIM\n");
}