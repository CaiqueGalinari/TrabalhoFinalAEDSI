#include <stdio.h>
#include <stdlib.h>
#include "AppBusca.h"


int main(){
    srand(time(NULL));
    TArvore arvore = {NULL};
    preencherArvore(&arvore);
    //Básico, árvore montada

    int totalEventos;
    char eventosEscolhidos[MAX_EVENTOS][MAX_NOME]; 
    char nomePesquisa[MAX_NOME];
    

    int opcao, opcaoInterna = 1;
    char continuar = 's';

    while (opcaoInterna == 1) {
        printf("\n========================================\n");
        printf("Bem-vindo ao Guia de Viagens! \n");
        printf("\n========================================\n");
        printf("Deseja visualizar as cidades com base em:\n");
        printf("1 - Ordem Crescente (por nota geral)\n");
        printf("2 - Ordem Decrescente (por nota geral)\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\n📡 Acessando GPS...\n");
            printf("Voce esta em '%s'\n", arvore.raiz->cidade.nome);
            Central(arvore.raiz);
        } else if(opcao == 2){
            printf("\n📡 Acessando GPS...\n");
            printf("Voce esta em '%s'\n", arvore.raiz->cidade.nome);
            CentralInverso(arvore.raiz);
        } else {
            printf("Opção invalida. Escolha novamente.\n");
            continue;
        }

        printf("\n----------------------------------------\n");
        printf(" O que deseja fazer agora?\n");
        printf("1 - Gerar um roteiro de viagem sugerido\n");
        printf("2 - Buscar uma cidade\n");
        printf("3 - Buscar um evento\n");
        printf("4 - Ver os eventos do dia\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Gerar roteiro de viagem
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
                encontrarMelhorRota(&arvore, eventosEscolhidos, totalEventos);

                printf("\nDeseja continuar utilizando?\n1 - Sim\n2 - Não\n");
                scanf("%d", &opcaoInterna);
                    break;

            }

            case 2: { // Buscar cidade
                    //pesquisas de cidade e evento dps tem colocar no local correto da main
                printf("Digite o nome da cidade para procurar: ");
                scanf(" %49[^\n]", nomePesquisa);

                ConfirmarCidade(&arvore, nomePesquisa);
    
                printf("\nDeseja continuar utilizando?\n1 - Sim\n2 - Não\n");
                scanf("%d", &opcaoInterna);
                    break;
            }

            case 3: { // Buscar evento
                printf("Digite o nome do evento para verificar em qual cidade ele está: ");
                scanf(" %49[^\n]", nomePesquisa);

                ConfirmarEvento(&arvore, nomePesquisa);

                printf("\nDeseja continuar utilizando?\n1 - Sim\n2 - Não\n");
                scanf("%d", &opcaoInterna);
                break;

            }

            case 4: {
                imprimirEventoPorHora(arvore.raiz);
                
                printf("Deseja continuar utilizando?\n1 - Sim\n2 - Não\n");
                scanf("%d", &opcaoInterna);
                break;
                
            }

            default:
                printf("Opção inválida. Tente novamente.\n");
                continue;
        }
        
    }

    printf("\n Obrigado por usar nosso sistema de busca de viagens. Até a próxima!\n");
    liberarArvore(arvore.raiz);
    return 0;

}
