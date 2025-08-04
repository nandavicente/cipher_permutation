#ifndef UTILS_H
#define UTILS_H

#include "constants.h"
#define MAX_BIGRAMAS 1000

extern const char ALPHABET[ALPHABET_SIZE + 1];

void aplicar_chave(const char* entrada, char* saida, const char* chave);
void gerar_vizinho(const char* chave_atual, char* chave_vizinha);
double score_text_log(const char* texto, char bigrams[][3], double* freqs, int n_bigrams);
void gerar_permutacao(char chave[ALPHABET_SIZE]);
void inverter_chave(const char chave[ALPHABET_SIZE], char chave_inv[ALPHABET_SIZE]);


#endif
