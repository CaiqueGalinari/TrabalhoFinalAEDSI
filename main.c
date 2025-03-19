#include <stdio.h>
#include <stdlib.h>
#include <AppBusca.h>


int main(){
    srand(time(NULL));
    TArvore arvore = {NULL};
    preencherArvore(&arvore);
    //Básico, árvore montada

    //Danilo, essa é a parte do roteiro de viagem, você precisará colocar no lugar certo
    int totalEventos;
    char eventosEscolhidos[MAX_EVENTOS][MAX_NOME]; 
    
    // Solicitar ao usuário a quantidade de eventos desejada
    do {
        printf("Quantos eventos deseja visitar? (1 a 4): ");
        scanf("%d", &totalEventos);
    } while (totalEventos < 1 || totalEventos > 4);
    
    // Solicitar os eventos desejados
    for (int i = 0; i < totalEventos; i++) {
        printf("Digite o nome do evento %d: ", i + 1);
        scanf(" %49[^\n]", eventosEscolhidos[i]);
    }
    
    encontrarMelhorRota(&arvore, eventosEscolhidos, totalEventos);
}