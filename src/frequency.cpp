#include "frequency.h"
#include <stdio.h>
#include "constants.h"

void contar_frequencia_letras(const char* texto, int freq[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = 0;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
        }
    }
}

void imprimir_frequencia(const int freq[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'A' + i, freq[i]);
    }
}
