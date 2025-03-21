#include <stdio.h>
#include <stdlib.h>
#include "AppBusca.h"


int main(){
    srand(time(NULL));
    TArvore arvore = {NULL};
    preencherArvore(&arvore);
    //Básico, árvore montada
    
    Central(arvore.raiz);

    //INICIO CAIXEIRO
    //Danilo, essa é a parte do roteiro de viagem, você precisará colocar no lugar certo
    int totalEventos;
    char eventosEscolhidos[MAX_EVENTOS][MAX_NOME]; 
    char nomePesquisa[MAX_NOME];
    
    // Solicitar ao usuário a quantidade de eventos desejada
    do {
        printf("Quantos eventos deseja visitar? (1 a 4): ");
        scanf("%d", &totalEventos);
    } while (totalEventos < 1 || totalEventos > 4);

    imprimirEventoPorHora(arvore.raiz);

    // Solicitar os eventos desejados
    for (int i = 0; i < totalEventos; i++) {
        printf("Digite o nome do evento %d: ", i + 1);
        scanf(" %49[^\n]", eventosEscolhidos[i]);
    }
   
    
    //pesquisas de cidade e evento dps tem colocar no local correto da main
    printf("Digite o nome da cidade para procurar: ");
    scanf(" %49[^\n]", nomePesquisa);

    ConfirmarCidade(&arvore, nomePesquisa);
    
    printf("Digite o nome do evento para verificar em qual cidade ele está: ");
    scanf(" %49[^\n]", nomePesquisa);

    ConfirmarEvento(&arvore, nomePesquisa);


    encontrarMelhorRota(&arvore, eventosEscolhidos, totalEventos);
    liberarArvore(arvore.raiz);
    //FIM CAIXEIRO
}
