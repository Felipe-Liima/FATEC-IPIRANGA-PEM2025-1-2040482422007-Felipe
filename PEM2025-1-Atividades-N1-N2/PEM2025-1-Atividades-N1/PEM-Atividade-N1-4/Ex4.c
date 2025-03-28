/*----------------------------------------------------------*
*                      FATEC Ipiranga                       *
* Disciplina: Programaçao Estruturada e Modular             *
*          Prof. Veríssimo                                  *
*-----------------------------------------------------------*
* Objetivo do Programa: gerenciando uma árvore diretórios   *
* Data - 28/03/2025                                         * 
* Autor: Felipe Bezerra de Lima; 2040482422007              *
*-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define INDENT_SIZE 4
#define MAX_CAMINHO 4096

void imprimir_indentacao(int nivel) {
    for (int i = 0; i < nivel * INDENT_SIZE; i++) {
        printf(" ");
    }
}

int eh_ponto_ou_ponto_duplo(const char *nome) {
    return (strcmp(nome, ".") == 0 || strcmp(nome, "..") == 0);
}

void exibir_arvore(const char *caminho, int nivel) {
    DIR *dir;
    struct dirent *entrada;
    struct stat info;
    char caminho_completo[MAX_CAMINHO];

    dir = opendir(caminho);
    if (dir == NULL) {
        imprimir_indentacao(nivel);
        fprintf(stderr, "[Erro ao abrir %s]: %s\n", caminho, strerror(errno));
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (eh_ponto_ou_ponto_duplo(entrada->d_name))
            continue;
        snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", caminho, entrada->d_name);
        if (lstat(caminho_completo, &info) == -1) {
            imprimir_indentacao(nivel);
            fprintf(stderr, "[Erro ao acessar %s]: %s\n", caminho_completo, strerror(errno));
            continue;
        }
        imprimir_indentacao(nivel);
        printf("%s\n", entrada->d_name);
        if (S_ISDIR(info.st_mode))
            exibir_arvore(caminho_completo, nivel + 1);
    }
    closedir(dir);
}

int main() {
    char caminho_inicial[MAX_CAMINHO];
    printf("Digite o caminho do diretório a ser explorado: ");
    if (fgets(caminho_inicial, sizeof(caminho_inicial), stdin) == NULL) {
        fprintf(stderr, "Erro na leitura do caminho.\n");
        return EXIT_FAILURE;
    }
    caminho_inicial[strcspn(caminho_inicial, "\n")] = '\0';
    if (access(caminho_inicial, F_OK) != 0) {
        fprintf(stderr, "O caminho '%s' não existe.\n", caminho_inicial);
        return EXIT_FAILURE;
    }
    printf("\nÁrvore de diretórios:\n");
    exibir_arvore(caminho_inicial, 0);
    return EXIT_SUCCESS;
}