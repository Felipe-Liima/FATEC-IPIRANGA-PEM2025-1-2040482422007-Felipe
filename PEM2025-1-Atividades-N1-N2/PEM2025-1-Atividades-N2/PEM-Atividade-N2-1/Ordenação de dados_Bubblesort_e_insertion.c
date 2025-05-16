
#include <stdio.h>
#include <stdlib.h>

// Funções de leitura e exibição
int lerQuantidade();
void lerNumeros(int *vetor, int quantidade);
void exibirNumeros(const int *vetor, int quantidade);

// Funções de ordenação
void bubbleSort(int *vetor, int quantidade);
void insertionSort(int *vetor, int quantidade);

// Função utilitária de troca de elementos
void trocar(int *a, int *b);

int main() {
    // Solicita ao usuário quantos números deseja ordenar
    int quantidade = lerQuantidade();

    // Aloca dinamicamente o vetor de acordo com a quantidade informada
    int *vetor = malloc(sizeof(int) * quantidade);
    if (vetor == NULL) {
        fprintf(stderr, "Erro: não foi possível alocar memória.\n");
        return EXIT_FAILURE;
    }

    // Lê os números a serem ordenados
    lerNumeros(vetor, quantidade);

    // Escolhe o algoritmo de ordenação
    printf("\nEscolha o método de ordenação:\n");
    printf(" 1 - Bubble Sort\n");
    printf(" 2 - Insertion Sort\n");
    printf("Opção: ");

    int opcao;
    if (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
        fprintf(stderr, "Opção inválida. Encerrando programa.\n");
        free(vetor);
        return EXIT_FAILURE;
    }

    // Aplica o algoritmo escolhido
    if (opcao == 1) {
        bubbleSort(vetor, quantidade);
        printf("\nVetor ordenado (Bubble Sort):\n");
    } else {
        insertionSort(vetor, quantidade);
        printf("\nVetor ordenado (Insertion Sort):\n");
    }

    // Exibe o resultado final
    exibirNumeros(vetor, quantidade);

    // Libera memória e finaliza
    free(vetor);
    return EXIT_SUCCESS;
}

// Lê quantos números o usuário deseja ordenar
int lerQuantidade() {
    int n;
    printf("Quantos números deseja ordenar? ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        // Limpa o buffer em caso de leitura inválida
        while (getchar() != '\n');
        printf("Por favor, insira um número inteiro positivo: ");
    }
    return n;
}

// Lê 'quantidade' inteiros do usuário para preencher 'vetor'
void lerNumeros(int *vetor, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Informe o número #%d: ", i + 1);
        while (scanf("%d", &vetor[i]) != 1) {
            // Limpa buffer e solicita novamente
            while (getchar() != '\n');
            printf("Entrada inválida. Digite um número inteiro para a posição #%d: ", i + 1);
        }
    }
}

// Exibe os números do vetor separados por espaço
void exibirNumeros(const int *vetor, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// Bubble Sort: compara pares adjacentes e troca se estiverem fora de ordem
void bubbleSort(int *vetor, int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        // A cada iteração, o maior elemento "borbulha" para o final
        for (int j = 0; j < quantidade - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
}

// Insertion Sort: insere cada elemento na posição correta à esquerda
void insertionSort(int *vetor, int quantidade) {
    for (int i = 1; i < quantidade; i++) {
        int chave = vetor[i];
        int j = i - 1;
        // Desloca elementos maiores que a chave para a direita
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        // Insere a chave na posição correta
        vetor[j + 1] = chave;
    }
}

// Troca os valores apontados por 'a' e 'b'
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}