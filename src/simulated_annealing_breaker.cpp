#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cmath>
#include "utils.h"

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
) {
    char chave[26], chave_atual[26], chave_vizinha[26];
    char texto_atual[4096], texto_vizinho[4096];
    
    gerar_permutacao(chave);
    memcpy(chave_atual, chave, 26);
    aplicar_chave(criptografado, texto_atual, chave_atual);
    double score_atual = score_text_log(texto_atual, bigrams, freqs, n_bigrams);

    memcpy(chave_melhor, chave_atual, 26);
    double melhor_score = score_atual;

    double temp = temp_ini;

    for (int i = 0; i < iter_max && temp > temp_min; ++i) {
        gerar_vizinho(chave_atual, chave_vizinha);
        aplicar_chave(criptografado, texto_vizinho, chave_vizinha);
        double score_vizinho = score_text_log(texto_vizinho, bigrams, freqs, n_bigrams);

        double delta = score_vizinho - score_atual;

        if (delta > 0 || (rand() / (double)RAND_MAX) < exp(delta / temp)) {
            memcpy(chave_atual, chave_vizinha, 26);
            score_atual = score_vizinho;

            if (score_atual > melhor_score) {
                melhor_score = score_atual;
                memcpy(chave_melhor, chave_atual, 26);
            }
        }

        temp *= cooling;
    }
}
