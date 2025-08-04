#include <stdio.h>
#include <string.h>
#include "constants.h"

int carregar_frequencias_bigrama(const char* filename, char bigrams[][3], double* freqs) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;

    int count = 0;
    while (fscanf(f, "%2s %lf", bigrams[count], &freqs[count]) == 2 && count < 1000) {
        count++;
    }

    fclose(f);
    return count;
}

double score_text_log(const char* texto, char bigrams[][3], double* freqs, int n) {
    double score = 0.0;
    for (int i = 0; texto[i + 1] != '\0'; i++) {
        char bg[3] = { texto[i], texto[i + 1], '\0' };
        for (int j = 0; j < n; j++) {
            if (strcmp(bg, bigrams[j]) == 0) {
                score += freqs[j];
                break;
            }
        }
    }
    return score;
}

