/*----------------------------------------------------------*
*                      FATEC Ipiranga                       *
* Disciplina: Programaçao Estruturada e Modular             *
*          Prof. Veríssimo                                  *
*-----------------------------------------------------------*
* Objetivo do Programa: vetor multidimensional modular      *
* Data - 14/03/2025                                        * 
* Autor: Felipe Bezerra de Lima; 2040482422007              *
*-----------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#define RUAS 3
#define GONDOLAS 10
#define MAX_CODIGO 10

// Matriz global para armazenar os produtos
char estoque[RUAS][GONDOLAS][MAX_CODIGO];

// Inicializa o estoque zerando a matriz
void inicializarEstoque() {
    memset(estoque, 0, sizeof(estoque));
}

// Armazena um produto no estoque
void armazenarProduto(char *codigo, int rua, int gondola) {
    if (rua < 0 || rua >= RUAS || gondola < 0 || gondola >= GONDOLAS) {
        printf("Erro: Posição inválida!\n");
        return;
    }

    if (estoque[rua][gondola][0] == '\0') {
        strcpy(estoque[rua][gondola], codigo);
        printf("Produto %s armazenado na Rua %c, Gôndola %d.\n", codigo, 'A' + rua, gondola + 1);
    } else if (strcmp(estoque[rua][gondola], codigo) == 0) {
        printf("Produto %s já está armazenado nesta posição.\n", codigo);
    } else {
        printf("Erro: Gôndola ocupada por outro produto!\n");
    }
}

// Retira um produto do estoque
void retirarProduto(char *codigo) {
    for (int i = 0; i < RUAS; i++) {
        for (int j = 0; j < GONDOLAS; j++) {
            if (strcmp(estoque[i][j], codigo) == 0) {
                printf("Produto %s retirado da Rua %c, Gôndola %d.\n", codigo, 'A' + i, j + 1);
                estoque[i][j][0] = '\0'; // Remove o produto
                return;
            }
        }
    }
    printf("Produto %s não encontrado no estoque.\n", codigo);
}

// Exibe o estoque atual
void exibirEstoque() {
    printf("\n=== Estoque Atual ===\n");
    int vazio = 1; // Flag para verificar se o estoque está vazio

    for (int i = 0; i < RUAS; i++) {
        for (int j = 0; j < GONDOLAS; j++) {
            if (estoque[i][j][0] != '\0') {
                printf("Rua %c, Gôndola %d: %s\n", 'A' + i, j + 1, estoque[i][j]);
                vazio = 0;
            }
        }
    }

    if (vazio) {
        printf("O estoque está vazio.\n");
    }
}

// Exibe o menu de opções
void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Armazenar Produto\n");
    printf("2. Retirar Produto\n");
    printf("3. Exibir Estoque\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// Programa principal
int main() {
    inicializarEstoque();

    int opcao, rua, gondola;
    char codigo[MAX_CODIGO];

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o código do produto: ");
                scanf("%s", codigo);
                printf("Digite a Rua (0 para A, 1 para B, 2 para C): ");
                scanf("%d", &rua);
                printf("Digite a Gôndola (1-10): ");
                scanf("%d", &gondola);
                armazenarProduto(codigo, rua, gondola - 1);
                break;

            case 2:
                printf("Digite o código do produto para retirar: ");
                scanf("%s", codigo);
                retirarProduto(codigo);
                break;

            case 3:
                exibirEstoque();
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
