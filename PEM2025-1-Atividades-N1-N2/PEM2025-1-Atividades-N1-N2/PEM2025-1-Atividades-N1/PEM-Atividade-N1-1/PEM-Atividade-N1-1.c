/*----------------------------------------------------------*
*                      FATEC Ipiranga                       *
* Disciplina: Programaçao Estruturada e Modular             *
*          Prof. Veríssimo                                  *
*-----------------------------------------------------------*
* Objetivo do Programa: Seleção dos candidatos à residência *
* Data - 28/02/20205                                        * 
* Autor: Felipe Bezerra de Lima; 2040482422007              *
*-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50
#define MAX_NOME 100

typedef struct {
    char nome[MAX_NOME];
    float notaPE;
    float notaAC;
    float notaPP;
    float notaEB;
    float NF;
} Candidato;

float calcularSomaCentrais(float notas[], int tamanho) {
    float soma = 0.0, menor, maior;
    int i;

    menor = notas[0];
    maior = notas[0];

    for (i = 0; i < tamanho; i++) {
        soma += notas[i];

        if (notas[i] < menor) {
            menor = notas[i];
        }
        if (notas[i] > maior) {
            maior = notas[i];
        }
    }

    return soma - menor - maior;
}

void lerNotas(float notas[], int quantidade, const char *tipo) {
    int i;

    printf("Digite as %d notas para %s:\n", quantidade, tipo);

    for (i = 0; i < quantidade; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float calcularNotaFinal(float pe, float ac, float pp, float eb) {
    return (pe * 0.3) + (ac * 0.1) + (pp * 0.4) + (eb * 0.2);
}

void cadastrarCandidatos(Candidato candidatos[], int *numCandidatos) {
    int i;
    float notas[10];

    printf("Digite o numero de candidatos (maximo %d): ", MAX_CANDIDATOS);
    scanf("%d", numCandidatos);

    if (*numCandidatos > MAX_CANDIDATOS) {
        printf("Numero de candidatos excede o limite.\n");
        exit(1);
    }

    for (i = 0; i < *numCandidatos; i++) {
        printf("\nCandidato %d:\n", i + 1);
        getchar();
        printf("Nome: ");
        fgets(candidatos[i].nome, MAX_NOME, stdin);
        candidatos[i].nome[strcspn(candidatos[i].nome, "\n")] = '\0';

        lerNotas(notas, 4, "Prova Escrita (PE)");
        candidatos[i].notaPE = calcularSomaCentrais(notas, 4);

        lerNotas(notas, 5, "Analise Curricular (AC)");
        candidatos[i].notaAC = calcularSomaCentrais(notas, 5);

        lerNotas(notas, 10, "Prova Pratica (PP)");
        candidatos[i].notaPP = calcularSomaCentrais(notas, 10);

        lerNotas(notas, 3, "Entrevista em Banca (EB)");
        candidatos[i].notaEB = calcularSomaCentrais(notas, 3);

        candidatos[i].NF = calcularNotaFinal(candidatos[i].notaPE, candidatos[i].notaAC, candidatos[i].notaPP, candidatos[i].notaEB);
    }
}

void ordenarCandidatos(Candidato candidatos[], int numCandidatos) {
    int i, j;
    Candidato temp;

    for (i = 0; i < numCandidatos - 1; i++) {
        for (j = 0; j < numCandidatos - i - 1; j++) {
            if (candidatos[j].NF < candidatos[j + 1].NF) {
                temp = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = temp;
            }
        }
    }
}

void exibirMelhoresCandidatos(Candidato candidatos[], int numCandidatos) {
    int i, numTop;

    numTop = (numCandidatos < 15) ? numCandidatos : 15;

    printf("\nClassificacao dos %d melhores candidatos:\n", numTop);
    printf("------------------------------------------------\n");
    printf("| Posicao | Nome\t\t| Nota Final |\n");
    printf("------------------------------------------------\n");

    for (i = 0; i < numTop; i++) {
        printf("| %2d      | %-15s | %.2f |\n", i + 1, candidatos[i].nome, candidatos[i].NF);
    }

    printf("------------------------------------------------\n");
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int numCandidatos;

    cadastrarCandidatos(candidatos, &numCandidatos);
    ordenarCandidatos(candidatos, numCandidatos);
    exibirMelhoresCandidatos(candidatos, numCandidatos);

    return 0;
}