// src/bigram.h
#ifndef BIGRAM_H
#define BIGRAM_H

int carregar_frequencias_bigrama(const char* filename, char bigrams[][3], double* freqs);
double score_text_log(const char* texto, char bigrams[][3], double* freqs, int n);

#endif
