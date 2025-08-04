// utils/input.cpp
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

char* ler_texto_de_arquivo(const char* caminho, int* tamanho) {
    FILE* fp = fopen(caminho, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long tam = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*) malloc(tam + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, tam, fp);
    buffer[tam] = '\0';
    fclose(fp);

    if (tamanho) *tamanho = (int) tam;
    return buffer;
}

char* ler_texto_manual(int* tamanho) {
    printf("Digite o texto a ser cifrado (fim com linha vazia):\n");

    int cap = 1024;
    char* buffer = (char*) malloc(cap);
    if (!buffer) return NULL;

    int pos = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), stdin)) {
        if (linha[0] == '\n') break;

        int len = 0;
        while (linha[len] != '\0') len++;

        if (pos + len >= cap) {
            cap *= 2;
            char* novo = (char*) realloc(buffer, cap);
            if (!novo) {
                free(buffer);
                return NULL;
            }
            buffer = novo;
        }

        for (int i = 0; i < len; i++)
            buffer[pos++] = linha[i];
    }

    buffer[pos] = '\0';
    if (tamanho) *tamanho = pos;
    return buffer;
}
