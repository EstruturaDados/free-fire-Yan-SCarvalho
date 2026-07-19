#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

struct Item {
    char nome[100];
    char tipo[50];
    int quantidade;
};

// Função auxiliar para limpar o \n que o fgets joga na string
void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int totalItens = 0;
    char buffer[100];
    int opcao;

    do {
        printf("\n=== INVENTARIO BASICO ===\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item por Nome\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        opcao = atoi(buffer); // Converte a opção para número de forma segura

        switch (opcao) {
            case 1:
                if (totalItens >= MAX_ITENS) {
                    printf("\n[ERRO] A mochila esta cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
                } else {
                    printf("\n--- Adicionar Novo Item ---\n");
                    
                    printf("Nome do item: ");
                    fgets(mochila[totalItens].nome, sizeof(mochila[totalItens].nome), stdin);
                    remove_newline(mochila[totalItens].nome);

                    printf("Tipo do item (ex: Arma, Pocao, Armadura): ");
                    fgets(mochila[totalItens].tipo, sizeof(mochila[totalItens].tipo), stdin);
                    remove_newline(mochila[totalItens].tipo);

                    printf("Quantidade: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    mochila[totalItens].quantidade = atoi(buffer);

                    totalItens++;
                    printf("\n[SUCESSO] Item adicionado com sucesso!\n");
                }
                break;

            case 2:
                if (totalItens == 0) {
                    printf("\n[AVISO] A mochila ja esta vazia.\n");
                } else {
                    char nomeRemover[100];
                    int encontrado = 0;
                    
                    printf("\nDigite o nome do item que deseja remover: ");
                    fgets(nomeRemover, sizeof(nomeRemover), stdin);
                    remove_newline(nomeRemover);
                    
                    for (int i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            encontrado = 1;
                            for (int j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            totalItens--; 
                            printf("\n[SUCESSO] Item '%s' removido do inventario.\n", nomeRemover);
                            break; 
                        }
                    }
                    if (!encontrado) {
                        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeRemover);
                    }
                }
                break;

            case 3:
                if (totalItens == 0) {
                    printf("\n[AVISO] A mochila esta vazia.\n");
                } else {
                    printf("\n=================== MOCHILA ===================\n");
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
                if (totalItens == 0) {
                    printf("\n[AVISO] A mochila esta vazia. Nao ha o que buscar.\n");
                } else {
                    char nomeBuscar[100];
                    int buscaEncontrado = 0;
                    
                    printf("\nDigite o nome do item que deseja buscar: ");
                    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
                    remove_newline(nomeBuscar);
                    
                    for (int i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
                            buscaEncontrado = 1; 
                            printf("\n--- Item Encontrado ---\n");
                            printf("Nome:       %s\n", mochila[i].nome);
                            printf("Tipo:       %s\n", mochila[i].tipo);
                            printf("Quantidade: %d\n", mochila[i].quantidade);
                            printf("-----------------------\n");
                            break; 
                        }
                    }
                    if (!buscaEncontrado) {
                        printf("\n[AVISO] O item '%s' nao foi encontrado na sua mochila.\n", nomeBuscar);
                    }
                }
                break;

            case 5:
                printf("\nFechando o inventario. Ate a proxima aventura!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}