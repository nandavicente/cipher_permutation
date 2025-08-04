#ifndef BREAKER_H
#define BREAKER_H

int carregar_frequencias_bigrama(const char* filename, char bigrams[][3], double freqs[]);

int hill_climbing_breaker(
    const char* ciphertext,
    char bigrams[][3],
    double freqs[],
    int n_bigrams,
    char* best_key,
    int max_iter
);
void simulated_annealing_breaker(
    const char* criptografado,
    char bigrams[][3],
    double* freqs,
    int n_bigrams,
    char* chave_melhor,
    int iter_max,
    double temp_ini,
    double temp_min,
    double cooling
);

#endif
