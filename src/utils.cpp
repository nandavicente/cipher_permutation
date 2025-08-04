// utils.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <cstring>
#include <cmath>
#include <cstdlib>  // para rand()


const char ALPHABET[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void gerar_permutacao(char chave[26]) {
    for (int i = 0; i < 26; i++) chave[i] = 'A' + i;

    // Embaralhar com Fisher-Yates
    for (int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);
        char tmp = chave[i];
        chave[i] = chave[j];
        chave[j] = tmp;
    }
}
void aplicar_chave(const char* entrada, char* saida, const char chave[26]) {
    int i = 0;
    while (entrada[i] != '\0') {
        char c = entrada[i];
        if (c >= 'A' && c <= 'Z') {
            saida[i] = chave[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            saida[i] = chave[c - 'a'] + 32;
        } else {
            saida[i] = c;
        }
        i++;
    }
    saida[i] = '\0';
}

void inverter_chave(const char chave[26], char chave_inv[26]) {
    for (int i = 0; i < 26; i++) {
        char c = chave[i];
        chave_inv[c - 'A'] = 'A' + i;
    }
}

void copiar_array(const char* origem, char* destino, int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

void trocar_dois_elementos(char* array) {
    int a = rand() % 26;
    int b = rand() % 26;
    char temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void gerar_vizinho(const char* chave_atual, char* chave_vizinha) {
    // Copia chave atual para chave vizinha
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        chave_vizinha[i] = chave_atual[i];
    }

    // Seleciona duas posições aleatórias para trocar
    int i = rand() % ALPHABET_SIZE;
    int j = rand() % ALPHABET_SIZE;

    // Troca os elementos nas posições i e j
    char temp = chave_vizinha[i];
    chave_vizinha[i] = chave_vizinha[j];
    chave_vizinha[j] = temp;
}
