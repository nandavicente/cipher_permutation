// frequency.h
#ifndef FREQUENCY_H
#define FREQUENCY_H
#define MAX_BIGRAMS 1000

#include "constants.h"

typedef struct {
    char bigram[3]; // 2 letras + '\0'
    double freq;    // frequência log ou normal
} BigramFreq;

// Contagem de frequência de letras simples
void contar_frequencia_letras(const char* texto, int freq[ALPHABET_SIZE]);
void imprimir_frequencia(const int freq[ALPHABET_SIZE]);

// Bigramas
int carregar_bigramas(const char* filename, BigramFreq bigrams[], int max_bigrams);
double score_bigramas(const char* texto, const BigramFreq bigrams[], int bigram_count);
double score_text_log(const char* texto, char bigrams[][3], double freqs[], int n_bigrams);

#endif
