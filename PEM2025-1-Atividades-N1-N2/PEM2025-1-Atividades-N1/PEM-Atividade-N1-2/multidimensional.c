/*----------------------------------------------------------*
*                      FATEC Ipiranga                       *
* Disciplina: Programaçao Estruturada e Modular             *
*          Prof. Veríssimo                                  *
*-----------------------------------------------------------*
* Objetivo do Programa: vetor multidimensional              *
* Data - 07/03/20205                                        * 
* Autor: Felipe Bezerra de Lima; 2040482422007              *
*-----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#define RUAS 3
#define GONDOLAS 10
#define MAX_CODIGO 10

// Matriz 3D pra armazenar os códigos dos produtos
char estoque[RUAS][GONDOLAS][MAX_CODIGO];

// Função pra armazenar um produto
void armazenarProduto(char codigo[], int rua, int gondola) {
    if (rua < 0 || rua >= RUAS || gondola < 0 || gondola >= GONDOLAS) {
        printf("Posição inválida!\n");
        return;
    }
    
    // Verifica se a gôndola está vazia
    if (estoque[rua][gondola][0] == '\0') {
        strcpy(estoque[rua][gondola], codigo);
        printf("Produto %s armazenado na Rua %c, Gôndola %d.\n", codigo, 'A' + rua, gondola + 1);
    } else if (strcmp(estoque[rua][gondola], codigo) == 0) {
        printf("Produto %s já está armazenado na mesma posição.\n", codigo);
    } else {
        printf("Erro: Gôndola ocupada por outro produto!\n");
    }
}

// Função para retirar um produto do estoque
void retirarProduto(char codigo[]) {
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

// Função para exibir o estoque
void exibirEstoque() {
    printf("\n=== Estoque Atual ===\n");
    for (int i = 0; i < RUAS; i++) {
        for (int j = 0; j < GONDOLAS; j++) {
            if (estoque[i][j][0] != '\0') {
                printf("Rua %c, Gôndola %d: %s\n", 'A' + i, j + 1, estoque[i][j]);
            }
        }
    }
}

int main() {
    // Inicializa o estoque vazio
    memset(estoque, 0, sizeof(estoque));
    
    int opcao;
    char codigo[MAX_CODIGO];
    int rua, gondola;
    
    do {
        printf("\nMenu:\n");
        printf("1. Armazenar Produto\n");
        printf("2. Retirar Produto\n");
        printf("3. Exibir Estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
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
        }
    } while (opcao != 0);
    
    return 0;
}
