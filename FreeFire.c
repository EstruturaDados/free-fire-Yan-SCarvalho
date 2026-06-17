#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Definição da struct para representar o item
struct Item {
    char nome[100];
    char tipo[50];
    int quantidade;
};

int main() {
    struct Item mochila[MAX_ITENS];
    int totalItens = 0; // Controla quantos itens existem atualmente na mochila
    int opcao;

    do {
        // Exibição do menu interativo
        printf("\n=== INVENTARIO BASICO ===\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' que ficou no buffer do teclado

        switch (opcao) {
            case 1: // ADICIONAR ITEM
                if (totalItens >= MAX_ITENS) {
                    printf("\n[ERRO] A mochila esta cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
                } else {
                    printf("\n--- Adicionar Novo Item ---\n");
                    
                    printf("Nome do item: ");
                    scanf("%99[^\n]", mochila[totalItens].nome);
                    getchar(); // Limpa o buffer

                    printf("Tipo do item (ex: Arma, Pocao, Armadura): ");
                    scanf("%49[^\n]", mochila[totalItens].tipo);
                    getchar(); // Limpa o buffer

                    printf("Quantidade: ");
                    scanf("%d", &mochila[totalItens].quantidade);
                    getchar(); // Limpa o buffer

                    totalItens++;
                    printf("\n[SUCESSO] Item adicionado com sucesso!\n");
                }
                break;

            case 2: // REMOVER ITEM
                if (totalItens == 0) {
                    printf("\n[AVISO] A mochila ja esta vazia.\n");
                } else {
                    char nomeRemover[100];
                    int encontrado = 0;

                    printf("\nDigite o nome do item que deseja remover: ");
                    scanf("%99[^\n]", nomeRemover);
                    getchar(); // Limpa o buffer

                    for (int i = 0; i < totalItens; i++) {
                        // Compara o nome digitado com o nome do item no inventário
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            encontrado = 1;
                            
                            // Move os itens seguintes uma posição para trás para cobrir o buraco
                            for (int j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            
                            totalItens--; // Decrementa o total de itens
                            printf("\n[SUCESSO] Item '%s' removido do inventario.\n", nomeRemover);
                            break; // Sai do laço de busca
                        }
                    }

                    if (!encontrado) {
                        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeRemover);
                    }
                }
                break;

            case 3: // LISTAR ITENS
                if (totalItens == 0) {
                    printf("\n[AVISO] A mochila esta vazia.\n");
                } else {
                    printf("\n=================== MOCHILA ===================\n");
                    // Formatação em formato de tabela
                    printf("%-20s | %-15s | %-10s\n", "NOME", "TIPO", "QTD");
                    printf("-----------------------------------------------\n");
                    
                    for (int i = 0; i < totalItens; i++) {
                        printf("%-20s | %-15s | %-10d\n", 
                               mochila[i].nome, 
                               mochila[i].tipo, 
                               mochila[i].quantidade);
                    }
                    printf("===============================================\n");
                    printf("Espaco ocupado: %d/%d\n", totalItens, MAX_ITENS);
                }
                break;

            case 4:
                printf("\nFechando o inventario. Ate a proxima aventura!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}