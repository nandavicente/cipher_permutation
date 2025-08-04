#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "breaker.h"
#include "frequency.h"
#include "cipher.h"
#include "utils.h"
#include "constants.h"
#include "bigram.h"

// Função auxiliar para trocar dois caracteres na chave
void swap_chars(char* key, int i, int j) {
    char tmp = key[i];
    key[i] = key[j];
    key[j] = tmp;
}

int hill_climbing_breaker(const char* ciphertext,
                         char bigrams[][3], double freqs[], int n_bigrams,
                         char* best_key, int max_iter) {
    srand((unsigned)time(NULL));

    char current_key[ALPHABET_SIZE + 1];
    strcpy(current_key, ALPHABET);

    char decrypted[10000];

    decipher(ciphertext, current_key, decrypted);
    double current_score = score_text_log(decrypted, bigrams, freqs, n_bigrams);

    strcpy(best_key, current_key);
    double best_score = current_score;

    for (int iter = 0; iter < max_iter; iter++) {
        int i = rand() % ALPHABET_SIZE;
        int j = rand() % ALPHABET_SIZE;
        if (i == j) continue;

        swap_chars(current_key, i, j);
        decipher(ciphertext, current_key, decrypted);
        double new_score = score_text_log(decrypted, bigrams, freqs, n_bigrams);

        if (new_score > current_score) {
            current_score = new_score;
            if (new_score > best_score) {
                best_score = new_score;
                strcpy(best_key, current_key);
            }
        } else {
            swap_chars(current_key, i, j); // desfaz troca
        }
    }
    return 0;
}
