#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Estrutura do item atualizada para o Nivel Mestre
struct Item {
    char nome[100];
    char tipo[50];
    int quantidade;
    int prioridade; // Valores de 1 a 5
};

// Funcao auxiliar para limpar o \n gerado pelo fgets
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
    
    // Flag booleana para controle de estado da ordenacao
    bool ordenadaPorNome = false;

    do {
        printf("\n=== INVENTARIO MESTRE ===\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Ordenar Mochila\n");
        printf("5. Busca Binaria por Nome\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        opcao = atoi(buffer);

        switch (opcao) {
            case 1: // ADICIONAR ITEM
                if (totalItens >= MAX_ITENS) {
                    printf("\n[ERRO] A mochila esta cheia! Limite: %d itens.\n", MAX_ITENS);
                } else {
                    printf("\n--- Novo Item ---\n");
                    
                    printf("Nome: ");
                    fgets(mochila[totalItens].nome, sizeof(mochila[totalItens].nome), stdin);
                    remove_newline(mochila[totalItens].nome);

                    printf("Tipo: ");
                    fgets(mochila[totalItens].tipo, sizeof(mochila[totalItens].tipo), stdin);
                    remove_newline(mochila[totalItens].tipo);

                    printf("Quantidade: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    mochila[totalItens].quantidade = atoi(buffer);

                    do {
                        printf("Prioridade (1 a 5): ");
                        fgets(buffer, sizeof(buffer), stdin);
                        mochila[totalItens].prioridade = atoi(buffer);
                        if (mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5) {
                            printf("[AVISO] A prioridade deve ser entre 1 e 5!\n");
                        }
                    } while (mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5);

                    totalItens++;
                    ordenadaPorNome = false; // Inserir quebra a ordenacao por nome
                    printf("\n[SUCESSO] Item guardado na mochila!\n");
                }
                break;

            case 2: // REMOVER ITEM
                if (totalItens == 0) {
                    printf("\n[AVISO] Mochila vazia.\n");
                } else {
                    char nomeRemover[100];
                    int achou = 0;
                    
                    printf("\nNome do item para remover: ");
                    fgets(nomeRemover, sizeof(nomeRemover), stdin);
                    remove_newline(nomeRemover);
                    
                    for (int i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            achou = 1;
                            for (int j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            totalItens--;
                            printf("\n[SUCESSO] Item '%s' removido.\n", nomeRemover);
                            break;
                        }
                    }
                    if (!achou) {
                        printf("\n[ERRO] Item '%s' nao encontrado.\n", nomeRemover);
                    }
                }
                break;

            case 3: // LISTAR ITENS
                if (totalItens == 0) {
                    printf("\n[AVISO] Mochila vazia.\n");
                } else {
                    printf("\n======================== MOCHILA ========================\n");
                    printf("%-20s | %-12s | %-6s | %-10s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");
                    printf("---------------------------------------------------------\n");
                    for (int i = 0; i < totalItens; i++) {
                        printf("%-20s | %-12s | %-6d | Prio: %d\n", 
                               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
                    }
                    printf("=========================================================\n");
                    printf("Espaco: %d/%d | Ordenada por Nome: %s\n", totalItens, MAX_ITENS, ordenadaPorNome ? "SIM" : "NAO");
                }
                break;

            case 4: // ORDENACAO COM INSERTION SORT
                if (totalItens < 2) {
                    printf("\n[AVISO] Itens insuficientes para ordenar (minimo 2).\n");
                } else {
                    int criterio;
                    printf("\n--- Criterios de Ordenacao ---\n");
                    printf("1. Por Nome\n");
                    printf("2. Por Tipo\n");
                    printf("3. Por Prioridade (Maior -> Menor)\n");
                    printf("Escolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    criterio = atoi(buffer);

                    if (criterio < 1 || criterio > 3) {
                        printf("\n[ERRO] Opcao invalida!\n");
                        break;
                    }

                    int comparacoes = 0;

                    // Algoritmo Insertion Sort estavel e limpo
                    for (int i = 1; i < totalItens; i++) {
                        struct Item chave = mochila[i];
                        int j = i - 1;

                        while (j >= 0) {
                            comparacoes++; // Conta a comparacao que sera feita a seguir
                            bool trocar = false;

                            if (criterio == 1) { // Nome
                                if (strcmp(mochila[j].nome, chave.nome) > 0) trocar = true;
                            } else if (criterio == 2) { // Tipo
                                if (strcmp(mochila[j].tipo, chave.tipo) > 0) trocar = true;
                            } else if (criterio == 3) { // Prioridade descrescente
                                if (mochila[j].prioridade < chave.prioridade) trocar = true;
                            }

                            if (trocar) {
                                mochila[j + 1] = mochila[j];
                                j--;
                            } else {
                                break;
                            }
                        }
                        mochila[j + 1] = chave;
                    }

                    // Atualiza o estado da flag de ordenacao
                    if (criterio == 1) {
                        ordenadaPorNome = true;
                        printf("\n[SUCESSO] Mochila ordenada por Nome!\n");
                    } else {
                        ordenadaPorNome = false;
                        if (criterio == 2) printf("\n[SUCESSO] Mochila ordenada por Tipo!\n");
                        if (criterio == 3) printf("\n[SUCESSO] Mochila ordenada por Prioridade!\n");
                    }

                    printf("Desempenho: %d comparacoes feitas na ordenacao.\n", comparacoes);
                }
                break;

            case 5: // BUSCA BINARIA
                if (totalItens == 0) {
                    printf("\n[AVISO] Mochila vazia.\n");
                } else if (!ordenadaPorNome) {
                    // Pre-requisito obrigatorio da busca binaria
                    printf("\n[ERRO] A busca binaria precisa da mochila ordenada por NOME (Opcao 4 -> Opcao 1)!\n");
                } else {
                    char nomeBuscar[100];
                    printf("\nNome do item para buscar (Busca Binaria): ");
                    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
                    remove_newline(nomeBuscar);

                    int inicio = 0;
                    int fim = totalItens - 1;
                    int meio;
                    bool encontrado = false;

                    // Algoritmo de Busca Binaria
                    while (inicio <= fim) {
                        meio = (inicio + fim) / 2;
                        int resultado = strcmp(mochila[meio].nome, nomeBuscar);

                        if (resultado == 0) {
                            encontrado = true;
                            printf("\n--- Item Localizado ---\n");
                            printf("Nome:       %s\n", mochila[meio].nome);
                            printf("Tipo:       %s\n", mochila[meio].tipo);
                            printf("Quantidade: %d\n", mochila[meio].quantidade);
                            printf("Prioridade: %d\n", mochila[meio].prioridade);
                            printf("-----------------------\n");
                            break;
                        } else if (resultado < 0) {
                            inicio = meio + 1;
                        } else {
                            fim = meio - 1;
                        }
                    }

                    if (!encontrado) {
                        printf("\n[AVISO] O item '%s' nao existe na mochila.\n", nomeBuscar);
                    }
                }
                break;

            case 6:
                printf("\nSaindo do Inventario Mestre. Ate mais!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida.\n");
        }
    } while (opcao != 6);

    return 0;
}