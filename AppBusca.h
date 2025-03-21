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
    char horarioFinal[MAX_NOME];
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
//ORDEM CRESCENTE
void Central(TCelula *x){
    if(x != NULL){
        Central(x->esq);
        printf("%s:\n%s (%d) - %s a %s", x->cidade.nome, x->cidade.eventos[0].nome, x->cidade.eventos[0].nota, x->cidade.eventos[0].horario, x->cidade.eventos[0].horarioFinal);
        printf("\n%s (%d) - %s a %s", x->cidade.eventos[1].nome, x->cidade.eventos[1].nota, x->cidade.eventos[1].horario, x->cidade.eventos[1].horarioFinal);
        printf("\n%s (%d) - %s a %s", x->cidade.eventos[2].nome, x->cidade.eventos[2].nota, x->cidade.eventos[2].horario, x->cidade.eventos[2].horarioFinal);
        printf("\n%s (%d) - %s a %s\n", x->cidade.eventos[3].nome, x->cidade.eventos[3].nota, x->cidade.eventos[3].horario, x->cidade.eventos[3].horarioFinal);
        printf("-------------------------------------------------\n");
        Central(x->dir);
    }
}

//ORDEM DECRESCENTE
void CentralInverso(TCelula *x){
    if(x != NULL){
        Central(x->dir);
        printf("%s:\n%s (%d) - %s a %s", x->cidade.nome, x->cidade.eventos[0].nome, x->cidade.eventos[0].nota, x->cidade.eventos[0].horario, x->cidade.eventos[0].horarioFinal);
        printf("\n%s (%d) - %s a %s", x->cidade.eventos[1].nome, x->cidade.eventos[1].nota, x->cidade.eventos[1].horario, x->cidade.eventos[1].horarioFinal);
        printf("\n%s (%d) - %s a %s", x->cidade.eventos[2].nome, x->cidade.eventos[2].nota, x->cidade.eventos[2].horario, x->cidade.eventos[2].horarioFinal);
        printf("\n%s (%d) - %s a %s\n", x->cidade.eventos[3].nome, x->cidade.eventos[3].nota, x->cidade.eventos[3].horario, x->cidade.eventos[3].horarioFinal);
        printf("-------------------------------------------------\n");
        Central(x->esq);
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
    "Festival de Musica", "Feira de Artesanato", "Exposicao de Arte", "Aula de Brunao", "Cinema ao Ar Livre",
    "Teatro Comunitario", "Circo", "Arnold Ohio", "Festival de Gastronomia", "Feira de Livros"
};

//Baseados em nomes de cidades reais, modifiquei pq n faz sentido "Rio de Janeiro" estar a 20km de "Fortaleza"
const char *nomesCidades[] = {
    "Sao Vicente", "Rio de Abril", "Lindo Horizonte", "Coolritiba", "Porto da Felicidade",
    "Brasilica", "Salvador Dali", "Corais", "Castelo", "Mananeus",
    "Betem", "Goiasia", "Campinhos", "Natalnael", "Joao Humano",
    "Flor e Ana Opolis", "Dom Luis", "Teresinha", "Marcelo", "Plantacaju"
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

//Cidade repetida (Caíque)
int cidadeRepetida(TCelula *raiz, TCidade Cidade) {
    if (raiz == NULL) {
        return 0; // Retorna False se não tiver repetido
    }
    if (strcmp(raiz->cidade.nome, Cidade.nome) == 0) {
        return 1; // Retorna True se achar repetido
    }

    // percorre a arvore toda verificando se tem árvore repetida
    return cidadeRepetida(raiz->esq, Cidade) || cidadeRepetida(raiz->dir, Cidade);
}


//Eventos aleatórios, com horário e nota
void gerarEventos(TEvento eventos[]) {
    int totalEventos = 0;
    while (totalEventos < MAX_EVENTOS) {
        int indice = rand() % 10;
        if (!eventoRepetido(eventos, totalEventos, nomesEventos[indice])) {

            strcpy(eventos[totalEventos].nome, nomesEventos[indice]);

            int horaInicial = rand() % 16 + 5; // Eventos podem começar de 5h a 21h
            int minutoInicial = rand() % 60;
            sprintf(eventos[totalEventos].horario, "%02d:%02d", horaInicial, minutoInicial);

            int duracaoHoras = rand() % 2 + 1; 
            int duracaoMinutos = rand() % 60;
            int horaFinal = horaInicial + duracaoHoras;
            int minutoFinal = minutoInicial + duracaoMinutos;

            //para manter formatação 24h/60min
            if (minutoFinal >= 60) {
                minutoFinal -= 60;
                horaFinal += 1;
            }
            if (horaFinal >= 24) {
                horaFinal -= 24;
            }
            sprintf(eventos[totalEventos].horarioFinal, "%02d:%02d", horaFinal, minutoFinal);

            eventos[totalEventos].nota = rand() % 11;

            totalEventos++;
        }
    }
    escolherOrdenacao(eventos, totalEventos);
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
// Não vamos dar opção de fazer isso sem ser aleatório
void preencherArvore(TArvore *arvore) {
    for (int i = 0; i < TOTAL_CIDADES; i++) {
        TCidade cidade;
        strcpy(cidade.nome, nomesCidades[rand() % 20]);

        while(cidadeRepetida(arvore->raiz, cidade)){
            strcpy(cidade.nome, nomesCidades[rand() % 20]);
        }

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

// pesquisar cidade e confirmar a existencia
TCelula* PesquisarCidade(TCelula *x, const char *nomeCidade) {
    if (x == NULL) {
        return NULL; 
    }
    if (strcmp(x->cidade.nome, nomeCidade) == 0) {
        return x;  
    }
    TCelula *esq = PesquisarCidade(x->esq, nomeCidade);
    if (esq != NULL) {
        return esq;  
    }
    return PesquisarCidade(x->dir, nomeCidade);
}

void ConfirmarCidade(TArvore *arvore, const char *nomeCidade) {
    TCelula *resultado = PesquisarCidade(arvore->raiz, nomeCidade);
    if (resultado != NULL) {
        printf("A cidade '%s' existe na árvore.\n", nomeCidade);
    } else {
        printf("A cidade '%s' não foi encontrada.\n", nomeCidade);
    }
}
// pesquisar evento e confirmar a cidade
TCelula* PesquisarEvento(TCelula *x, const char *nomeEvento) {
    if (x == NULL) {
        return NULL;  
    }
    for (int i = 0; i < MAX_EVENTOS; i++) {
        if (strcmp(x->cidade.eventos[i].nome, nomeEvento) == 0) {
            return x; 
        }
    }
    TCelula *esq = PesquisarEvento(x->esq, nomeEvento);
    if (esq != NULL) {
        return esq; 
    }
    return PesquisarEvento(x->dir, nomeEvento);
}

void ConfirmarEvento(TArvore *arvore, const char *nomeEvento) {
    TCelula *resultado = PesquisarEvento(arvore->raiz, nomeEvento);
    if (resultado != NULL) {
        printf("O evento '%s' está na cidade '%s'.\n", nomeEvento, resultado->cidade.nome);
    } else {
        printf("O evento '%s' não foi encontrado.\n", nomeEvento);
    }
}

// ********************************************************************** FUNÇÕES DE ORDENAÇÃO **********************************************************************
//PARA ORDENAR OS EVENTOS DENTRO DA CIDADE DO MELHOR (10) PARA O PIOR (0)
void bubbleSort(TEvento *eventos, int n)
{
    int i, fim;
    TEvento aux;
    for (fim = n - 1; fim > 0; --fim)
    {
        for (i = 0; i < fim; ++i)
        {
            if (eventos[i].nota < eventos[i + 1].nota)
            {
                aux = eventos[i];
                eventos[i] = eventos[i + 1];
                eventos[i + 1] = aux;
            }
        }
    }
}

void selectionSort(TEvento *eventos, int n)
{
    int i, j, maxID;
    TEvento aux;
    for (i = 0; i < (n - 1); i++)
    {
        maxID = i;
        for (j = i + 1; j < n; j++)
        {
            if (eventos[j].nota > eventos[maxID].nota)
            {
                maxID = j;
            }
        }
        if (i != maxID)
        {
            aux = eventos[i];
            eventos[i] = eventos[maxID];
            eventos[maxID] = aux;
        }
    }
}

void insertionSort(TEvento *eventos, int n)
{
    int i, j;
    TEvento aux;
    for (i = 1; i < n; i++)
    {
        aux = eventos[i];
        j = i - 1;
        while (j >= 0 && eventos[j].nota < aux.nota)
        {
            eventos[j + 1] = eventos[j];
            j--;
        }
        eventos[j + 1] = aux;
    }
}

void shellSort(TEvento *eventos, int n)
{
    int i, j, intervalo;
    TEvento temp;
    for (intervalo = n / 2; intervalo > 0; intervalo /= 2)
    {
        for (i = intervalo; i < n; i++)
        {
            temp = eventos[i];
            j = i;
            while (j >= intervalo && eventos[j - intervalo].nota < temp.nota)
            {
                eventos[j] = eventos[j - intervalo];
                j -= intervalo;
            }
            eventos[j] = temp;
        }
    }
}

void quickSort(TEvento *eventos, int inicio, int fim)
{
    if (inicio < fim)
    {
        int q = partirQuickSort(eventos, inicio, fim);
        quickSort(eventos, inicio, q - 1);
        quickSort(eventos, q + 1, fim);
    }
}

int partirQuickSort(TEvento *eventos, int inicio, int fim)
{
    TEvento aux, pivo = eventos[fim];
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++)
    {
        if (eventos[j].nota >= pivo.nota)
        {
            i++;
            aux = eventos[i];
            eventos[i] = eventos[j];
            eventos[j] = aux;
        }
    }
    aux = eventos[i + 1];
    eventos[i + 1] = eventos[fim];
    eventos[fim] = aux;
    return i + 1;
}

void mergeSort(TEvento *eventos, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSort(eventos, inicio, meio);
        mergeSort(eventos, meio + 1, fim);
        merge(eventos, inicio, meio, fim);
    }
}

void merge(TEvento *eventos, int inicio, int meio, int fim)
{
    int primeiraParte = inicio;
    int segundaParte = meio + 1;
    int parteAux = 0;
    TEvento vetAux[fim - inicio + 1];

    while (primeiraParte <= meio && segundaParte <= fim)
    {
        if (eventos[primeiraParte].nota >= eventos[segundaParte].nota)
        {
            vetAux[parteAux] = eventos[primeiraParte];
            primeiraParte++;
        }
        else
        {
            vetAux[parteAux] = eventos[segundaParte];
            segundaParte++;
        }
        parteAux++;
    }

    while (primeiraParte <= meio)
    {
        vetAux[parteAux] = eventos[primeiraParte];
        parteAux++;
        primeiraParte++;
    }

    while (segundaParte <= fim)
    {
        vetAux[parteAux] = eventos[segundaParte];
        parteAux++;
        segundaParte++;
    }

    for (parteAux = inicio; parteAux <= fim; parteAux++)
    {
        eventos[parteAux] = vetAux[parteAux - inicio];
    }
}

void montarHeapSort(TEvento *eventos, int n, int i)
{
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    TEvento aux;

    if (esquerda < n && eventos[esquerda].nota > eventos[maior].nota)
    {
        maior = esquerda;
    }

    if (direita < n && eventos[direita].nota > eventos[maior].nota)
    {
        maior = direita;
    }

    if (maior != i)
    {
        aux = eventos[i];
        eventos[i] = eventos[maior];
        eventos[maior] = aux;
        montarHeapSort(eventos, n, maior);
    }
}

void heapSort(TEvento *eventos, int n)
{
    TEvento aux;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        montarHeapSort(eventos, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        aux = eventos[0];
        eventos[0] = eventos[i];
        eventos[i] = aux;
        montarHeapSort(eventos, i, 0);
    }
}

void escolherOrdenacao(TEvento *eventos, int n){
    int tipoOrdenacao = rand() % 6;
    switch (tipoOrdenacao)
    {
    case 0:
        bubbleSort(eventos, n);
        break;
    case 1:
        selectionSort(eventos, n);
        break;
    case 2:
        insertionSort(eventos, n);
        break;
    case 3:
        shellSort(eventos, n);
        break;
    case 4:
        quickSort(eventos, 0, n - 1);
        break;
    case 5:
        mergeSort(eventos, 0, n - 1);
        break;
    default:
        break;
    }
}

// ********************************************************************** FUNÇÕES DE BUSCA **********************************************************************

//PROVISÓRIA, PRECISO DELA PARA FAZER O SISTEMA DE CAIXEIRO VIAJANTE
// Função para buscar um evento na árvore e retornar a cidade/célula da cidade
void buscarCidadesComEvento(TCelula *raiz, const char *eventoNome, TCelula *resultados[], int indices[], int *contador) {
    if (raiz == NULL) {
        return;
    }

    if (eventoNome == NULL) { 
        printf("Erro: eventoNome é NULL.\n"); 
        return; 
    }

    for (int i = 0; i < TOTAL_CIDADES; i++) {
        if (strcmp(raiz->cidade.eventos[i].nome, eventoNome) == 0) {
            // Se o nome do evento "i" for igual ao nome do evento que queremos:
            resultados[*contador] = raiz; // Preenche uma posição do vetor com a célula que tem o evento
            indices[*contador] = i;      // Armazena o índice certo do evento para cada cidade
            (*contador)++;               // Próxima posição do vetor
        }
    }

    // Repete o processo para os filhos esquerdo e direito
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
    if (cidade == NULL) {
        printf("Erro: Cidade é NULL.\n");
        return -1; // Valor indicativo de erro
    }
    int distancia = 0; // Variável em que as distâncias vão se acumular
    TCelula *atual = cidade; // A cidade que será analisada a distância entre ela e a raiz

    while (atual->pai != NULL) {
        if (atual == atual->pai->esq) {
            // Se a cidade atual for a cidade à esquerda da cidade pai:
            distancia += atual->pai->cidade.distanciaEsq; // Acumula a distância até o pai
        } else {
            // Se estiver à direita:
            distancia += atual->pai->cidade.distanciaDir; // Acumula a distância até o pai
        }
        atual = atual->pai; // Move para o nó pai
    }

    return distancia; // Retorna a distância acumulada até a raiz
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
    TCelula *opcoes[TOTAL_CIDADES]; //Guarda cidades onde o evento está disponível
    int indices[TOTAL_CIDADES];  // Guarda o indice do evento dentro da cidade
    for (int i = 0; i < totalEventos; i++) { //percorre todos os eventos escolhidos
        int contador = 0; // Conta quantas cidades possuem o evento
        int melhorIndice = 0; //Armazena o indice da melhor cidade encontrada até agora (a princípio a primeira)
        //Inicializando as variaveis
        for (int i = 0; i < TOTAL_CIDADES; i++) {
            opcoes[i] = NULL; 
            indices[i] = -1;
        }
        //Procura e armazena todas as cidades que têm o evento em questão
        buscarCidadesComEvento(arvore->raiz, eventosEscolhidos[i], opcoes, indices, &contador);

        //Se o contador for 0, quer dizer que o evento não foi encontrado
        if (contador == 0) {
            printf("Erro: Evento '%s' nao encontrado.\n", eventosEscolhidos[i]);
            return;
        }

        //1 ESCOLHE A ROTA COM BASE NA NOTA
        //2 SE NÃO FOR POSSÍVEL, ESCOLHE A ROTA COM BASE NA ROTA MAIS RÁPIDA, IGNORANDO A NOTA
        //Lembrando que o contador é o numero de cidades total que possuem o evento
        // ***** 1:
        for (int j = 1; j < contador; j++) { //percorre todas as cidades onde o evento está disponível

            //indices[melhorIndice] é o indice do evento, opcoes[melhorIndice é o indice da cidade]
            int notaAtual = opcoes[melhorIndice]->cidade.eventos[indices[melhorIndice]].nota; //Pega a melhor nota até agora
            int notaNova = opcoes[j]->cidade.eventos[indices[j]].nota; //Pega a nota da próxima cidade (por isso j começa em 1)

            if(opcoes[melhorIndice] != NULL){ //Para evitar bugs (precaução)
                int distanciaAtual = calcularDistanciaAteRaiz(opcoes[melhorIndice]); // Calcula a distância até a raiz da cidade com a melhor nota
                int distanciaNova = calcularDistanciaAteRaiz(opcoes[j]); // Calcula a distância até a raiz da próxima cidade

                //Aqui é interessante, se a nota da próxima cidade é maior
                //OU se a nota das duas for igual, a que for mais perto é  escolhida
                if (notaNova > notaAtual || (notaNova == notaAtual && distanciaNova < distanciaAtual)) {
                melhorIndice = j;
                }
            }
        }

        cidadesEscolhidas[i] = opcoes[melhorIndice]; // A cidade escolhida é passada para o vetor das cidades
        indicesEventos[i] = indices[melhorIndice]; // O indice dos eventos também é passado (para que não o perca)
    }

    int velocidade = 0; //Usado para saber se vai procurar por velocidade e não por nota

    // Verificar se é possível chegar a tempo ao próximo evento (por nota)
    for (int i = 0; i < totalEventos - 1; i++) {
        TCelula* ancestral = encontrarAncestralComum(cidadesEscolhidas[i], cidadesEscolhidas[i + 1]); //Encontra o ancestral comum entre as cidades escolhidas

        // Calcula a distancia da primeira até a raiz e subtrai com a distancia da ancestral até a raiz, depois soma a esse mesmo processo com a outra cidade sendo comparada
        int distancia = (calcularDistanciaAteRaiz(cidadesEscolhidas[i]) - calcularDistanciaAteRaiz(ancestral)) + (calcularDistanciaAteRaiz(cidadesEscolhidas[i + 1]) - calcularDistanciaAteRaiz(ancestral));
        if (distancia < 0) {distancia = -distancia;} //Manutenção p evitar bug, n tem como ter distância negativa entre cidades
        
        //Calcula o tempo de viagem dessa distância
        int tempoViagem = calcularTempoViagem(distancia);

        int horarioAtual = converterHorarioParaMinutos(cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].horarioFinal); //Pega o horarioFinal do evento da cidade atual convertendo para minutos

        int horarioProximo = converterHorarioParaMinutos(cidadesEscolhidas[i + 1]->cidade.eventos[indicesEventos[i + 1]].horario); //Mesma coisa, mas com a outra cidade e usando o horario inicial do evento
        
        //Se o horario atual e o tempo de deslocamento for maior que o horario do proximo envento, então não será possível
        if (horarioAtual + tempoViagem > horarioProximo) {
            printf("Nao e possivel visitar todos os melhores eventos . Tentando priorizar o tempo...");
            velocidade = 10; //Valor fixo que será usado
            break;
        }
    }

    if(velocidade == 10){
        // ***** 2.
        for (int i = 0; i < totalEventos; i++) { //percorre todos os eventos escolhidos
            int contador = 0; // Conta quantas cidades possuem o evento
            int melhorIndice = 0; //Armazena o indice da melhor cidade encontrada até agora (a princípio a primeira)
            //Inicializando as variaveis
            for (int i = 0; i < TOTAL_CIDADES; i++) {
                opcoes[i] = NULL; 
                indices[i] = -1;
            }
            //Procura e armazena todas as cidades que têm o evento em questão
            //provavelmente desnecessário, mas peguei trauma de bugs
            buscarCidadesComEvento(arvore->raiz, eventosEscolhidos[i], opcoes, indices, &contador);

            //Se o contador for 0, quer dizer que o evento não foi encontrado
            if (contador == 0) {
                printf("Erro: Evento '%s' nao encontrado.\n", eventosEscolhidos[i]);
                return;
            }

            // ***** 2:
            if(opcoes[melhorIndice] != NULL){
                //percorre todas as cidades onde o evento está disponível
                for (int j = 1; j < contador; j++) {
                    int horarioAtual = converterHorarioParaMinutos(opcoes[melhorIndice]->cidade.eventos[indices[melhorIndice]].horario);
                    int horarioNovo = converterHorarioParaMinutos(opcoes[j]->cidade.eventos[indices[j]].horario);
                
                    // Verifica o evento com horário mais próximo do último selecionado e dentro do tempo permitido
                    if(i != 0){ //Para não quebrar por causa o i-1
                        if (horarioNovo >= converterHorarioParaMinutos(cidadesEscolhidas[i - 1]->cidade.eventos[indicesEventos[i - 1]].horarioFinal) &&
                            (horarioNovo < horarioAtual)) {
                            melhorIndice = j;
                        }
                    }
                }
            }

    
            cidadesEscolhidas[i] = opcoes[melhorIndice]; // A cidade escolhida é passada para o vetor das cidades
            indicesEventos[i] = indices[melhorIndice]; // O indice dos eventos também é passado (para que não o perca)
        }


        // Checar para ver se vai ter como visitar todas as cidades, se não for, mostrará um aviso
        int eventoRemovido = -1; //Assumindo que não tem nenhum "empacado"

        //Mesmo processo de cálculo de tempo anterior
        for (int i = 0; i < totalEventos - 1; i++) {
            //Cálculos de distância
            TCelula* ancestral = encontrarAncestralComum(cidadesEscolhidas[i], cidadesEscolhidas[i + 1]);
            int distancia = (calcularDistanciaAteRaiz(cidadesEscolhidas[i]) - calcularDistanciaAteRaiz(ancestral)) + (calcularDistanciaAteRaiz(cidadesEscolhidas[i + 1]) - calcularDistanciaAteRaiz(ancestral));
            if (distancia < 0) distancia = -distancia;
            
            //Cálculos de horário
            int tempoViagem = calcularTempoViagem(distancia);
            int horarioAtual = converterHorarioParaMinutos(cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].horarioFinal);
            int horarioProximo = converterHorarioParaMinutos(cidadesEscolhidas[i + 1]->cidade.eventos[indicesEventos[i + 1]].horario);
            
            if (horarioAtual + tempoViagem > horarioProximo) {
                //Adiciona 1 ao evento removido e quebra o laço for
                eventoRemovido = i + 1;
                break;
            }
        }
        
        if (eventoRemovido != -1) {
            printf("\nNao e possivel visitar todos os eventos desejados. O evento '%s' na cidade '%s' precisara ser removido da rota.", cidadesEscolhidas[eventoRemovido]->cidade.eventos[indicesEventos[eventoRemovido]].nome, cidadesEscolhidas[eventoRemovido]->cidade.nome);
        }
    }
    
    // Printar a rota
    printf("Melhor rota:\n");
    for (int i = 0; i < totalEventos; i++) {
        printf("%s (%s [%d] - de %s a %s)\n->\n ", cidadesEscolhidas[i]->cidade.nome, cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].nome, cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].nota, cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].horario, cidadesEscolhidas[i]->cidade.eventos[indicesEventos[i]].horarioFinal);
    }
    printf("FIM\n");
}

// ********************************************************************** FUNÇÕES EXTRAS ********************************************************************** 

void liberarArvore(TCelula *raiz){
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

void definirEventosPorHorario(TCelula *raiz, TCelula *manha[], int *indicesManha[], TCelula *dia[], int *indicesDia[], TCelula *tarde[], int *indicesTarde[], TCelula *noite[], int *indicesNoite[]) {
    if (raiz == NULL) return; // Base da recursão, fim do percurso
    
    // Primeiro, percorre a subárvore da esquerda
    definirEventosPorHorario(raiz->esq, manha, indicesManha, dia, indicesDia, tarde, indicesTarde, noite, indicesNoite);
    //COLOCAR VETORES NA POSICAO
    int k, cManha = 0, cDia = 0, cTarde = 0, cNoite = 0;
    while (indicesManha[cManha] != NULL){
        cManha++;
    }
    while (indicesDia[cDia] != NULL){
        cDia++;
    }
    while (indicesTarde[cTarde] != NULL){
        cTarde++;
    }
    while (indicesNoite[cNoite] != NULL){
        cNoite++;
    }

    // Verifica e organiza os eventos da cidade atual
    for (int i = 0; i < MAX_EVENTOS; i++) {
        k = 0;
        k = converterHorarioParaMinutos(raiz->cidade.eventos[i].horario);
        if(k < 600){
            manha[cManha] = raiz;
            indicesManha[cManha] = i;
            cManha++;
        } 
        if(k >= 600 && k < 840){
            dia[cDia] = raiz;
            indicesDia[cDia] = i;
            cDia++;
        } 
        if(k >= 840 && k < 1080){
            tarde[cTarde] = raiz;
            indicesTarde[cTarde] = i;
            cTarde++;
        } if(k >= 1080){
            noite[cNoite] = raiz;
            indicesNoite[cNoite] = i;
            cNoite++;
        }

    }
    definirEventosPorHorario(raiz->dir, manha, indicesManha, dia, indicesDia, tarde, indicesTarde, noite, indicesNoite);
}

void imprimirEventoPorHora(TCelula *raiz) {
    // Declarar os vetores como ponteiros
    TCelula *manha[40] = {NULL}, *dia[40] = {NULL}, *tarde[40] = {NULL}, *noite[40] = {NULL};
    int indicesManha[40] = {0}, indicesDia[40] = {0}, indicesTarde[40] = {0}, indicesNoite[40] = {0};

   // Passar os vetores como ponteiros para a função
   definirEventosPorHorario(raiz, manha, indicesManha, dia, indicesDia, tarde, indicesTarde, noite, indicesNoite);
    printf("\nIndice: %d\n", indicesManha[0]);
    printf("\n\n%s\n\n", manha[0]->cidade.eventos[0].nome);

    // Imprime os eventos organizados por horário
    printf("\n------------- EVENTOS DA MANHÃ -------------");
    for (int i = 0; manha[i] != NULL; i++) {
        printf("\n%s - %s a %s - %s",
               manha[i]->cidade.eventos[indicesManha[i]].nome,
               manha[i]->cidade.eventos[indicesManha[i]].horario,
               manha[i]->cidade.eventos[indicesManha[i]].horarioFinal,
               manha[i]->cidade.nome);
    }

    printf("\n------------- EVENTOS DO DIA -------------");
    for (int i = 0; dia[i] != NULL; i++) {
        printf("\n%s - %s a %s - %s",
               dia[i]->cidade.eventos[indicesDia[i]].nome,
               dia[i]->cidade.eventos[indicesDia[i]].horario,
               dia[i]->cidade.eventos[indicesDia[i]].horarioFinal,
               dia[i]->cidade.nome);
    }

    printf("\n------------- EVENTOS DA TARDE -------------");
    for (int i = 0; tarde[i] != NULL; i++) {
        printf("\n%s - %s a %s - %s",
               tarde[i]->cidade.eventos[indicesTarde[i]].nome,
               tarde[i]->cidade.eventos[indicesTarde[i]].horario,
               tarde[i]->cidade.eventos[indicesTarde[i]].horarioFinal,
               tarde[i]->cidade.nome);
    }

    printf("\n------------- EVENTOS DA NOITE -------------");
    for (int i = 0; noite[i] != NULL; i++) {
        printf("\n%s - %s a %s - %s",
               noite[i]->cidade.eventos[indicesNoite[i]].nome,
               noite[i]->cidade.eventos[indicesNoite[i]].horario,
               noite[i]->cidade.eventos[indicesNoite[i]].horarioFinal,
               noite[i]->cidade.nome);
    }
    printf("\n\n");
}
