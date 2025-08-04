#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "benchmark.h"
#include "utils.h"

#define MAX_TEXTO 8192

void remover_quebras_de_linha(char* texto) {
    int i = 0, j = 0;
    while (texto[i]) {
        if (texto[i] != '\n' && texto[i] != '\r') {
            texto[j++] = texto[i];
        }
        i++;
    }
    texto[j] = '\0';
}

int modo_benchmark(int argc, char* argv[]) {
    char texto[MAX_TEXTO] = {0};
    const char* heuristica = "hc";
    const char* caminho_bigrams = "data/bigrams/pt-br.txt";
    const char* nome_entrada = NULL;

    bool entrada_por_arquivo = false;
    const char* caminho_arquivo = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--texto") == 0 && i + 1 < argc) {
            strncpy(texto, argv[++i], MAX_TEXTO - 1);
            nome_entrada = "entrada_manual";
        } else if (strcmp(argv[i], "--arquivo") == 0 && i + 1 < argc) {
            caminho_arquivo = argv[++i];
            entrada_por_arquivo = true;
        } else if (strcmp(argv[i], "--heuristica") == 0 && i + 1 < argc) {
            heuristica = argv[++i];
        } else if (strcmp(argv[i], "--bigrams") == 0 && i + 1 < argc) {
            caminho_bigrams = argv[++i];
        }
    }

    if (entrada_por_arquivo) {
        FILE* f = fopen(caminho_arquivo, "r");
        if (!f) {
            printf("Erro ao abrir arquivo: %s\n", caminho_arquivo);
            return 1;
        }

        // Corrigido para suportar Windows e Unix
        const char* barra1 = strrchr(caminho_arquivo, '/');
        const char* barra2 = strrchr(caminho_arquivo, '\\');
        const char* ultima_barra = (barra1 > barra2) ? barra1 : barra2;
        nome_entrada = (ultima_barra ? ultima_barra + 1 : caminho_arquivo);

        size_t total = 0;
        char linha[512];
        while (fgets(linha, sizeof(linha), f)) {
            size_t len = strlen(linha);
            if (total + len < MAX_TEXTO - 1) {
                strcpy(&texto[total], linha);
                total += len;
            } else {
                break;
            }
        }
        fclose(f);
    }

    if (texto[0] == '\0') {
        printf("Erro: Nenhum texto fornecido com --texto ou --arquivo.\n");
        return 1;
    }

    remover_quebras_de_linha(texto);
    executar_benchmark(texto, nome_entrada, heuristica, caminho_bigrams);
    return 0;
}

int modo_psf(int argc, char* argv[]) {
    printf("Modo PSF ainda não implementado.\n");
    return 1;
}

int main(int argc, char* argv[]) {
    const char* modo = "benchmark";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--modo") == 0 && i + 1 < argc) {
            modo = argv[++i];
        }
    }

    if (strcmp(modo, "benchmark") == 0) {
        return modo_benchmark(argc, argv);
    } else if (strcmp(modo, "psf") == 0) {
        return modo_psf(argc, argv);
    } else {
        printf("Modo desconhecido: %s\n", modo);
        printf("Modos suportados: benchmark, psf\n");
        return 1;
    }
}
