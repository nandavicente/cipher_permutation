#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "cipher.h"
#include "breaker.h"
#include "frequency.h"
#include "utils.h"

#define MAX_TEXTO 10000


bool executar_benchmark(
    const char* texto,
    const char* nome_entrada,
    const char* heuristica,
    const char* caminho_bigrams
) {
    char chave[26], chave_inv[26], chave_heuristica[26];
    char criptado[MAX_TEXTO], quebrado[MAX_TEXTO];
    char bigrams[676][3];
    double freqs[676];

    int n_bigrams = carregar_frequencias_bigrama(caminho_bigrams, bigrams, freqs);
    if (n_bigrams <= 0) {
        printf("Erro ao carregar bigramas de %s.\n", caminho_bigrams);
        return false;
    }

    printf("Benchmark em memória\n");
    printf("Entrada: %s\n", nome_entrada);
    printf("Heurística: %s\n", heuristica);
    printf("Bigramas: %s\n", caminho_bigrams);
    printf("seed,tempo_ms,score,acuracia\n");

    double soma_score = 0.0;
    double soma_tempo = 0.0;
    double soma_acuracia = 0.0;

    for (int exec = 0; exec < 10; exec++) {
        unsigned int seed = (unsigned int)(time(NULL) + exec * 37);
        srand(seed);

        gerar_permutacao(chave);
        inverter_chave(chave, chave_inv);
        criptografar(texto, criptado, chave);

        clock_t inicio = clock();

        if (strcmp(heuristica, "simann") == 0 || strcmp(heuristica, "sa") == 0) {
            simulated_annealing_breaker(criptado, bigrams, freqs, n_bigrams, chave_heuristica,
                                        10000, 100.0, 0.01, 0.99);
        } else {
            hill_climbing_breaker(criptado, bigrams, freqs, n_bigrams, chave_heuristica, 10000);
        }

        clock_t fim = clock();

        aplicar_chave(criptado, quebrado, chave_heuristica);

        double tempo_ms = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
        double score = score_text_log(quebrado, bigrams, freqs, n_bigrams);

        int corretos = 0;
        for (int i = 0; i < 26; i++) {
            if (chave[i] == chave_heuristica[i])
                corretos++;
        }
        double acuracia = (corretos / 26.0) * 100.0;

        printf("%u,%.2f,%.4f,%.2f\n", seed, tempo_ms, score, acuracia);

        soma_score += score;
        soma_tempo += tempo_ms;
        soma_acuracia += acuracia;
    }

    printf("Media,%.2f,%.4f,%.2f\n",
           soma_tempo / 10.0,
           soma_score / 10.0,
           soma_acuracia / 10.0);

    return true;
}
