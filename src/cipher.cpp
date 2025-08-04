// cipher.cpp
#include <string.h>
#include "cipher.h"
#include "constants.h"


void criptografar(const char* texto, char* resultado, const char chave[26]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (c >= 'A' && c <= 'Z')
            resultado[i] = chave[c - 'A'];
        else if (c >= 'a' && c <= 'z')
            resultado[i] = chave[c - 'a'] + 32;
        else
            resultado[i] = c;
    }
    resultado[i] = '\0';
}

void descriptografar(const char* texto, char* resultado, const char chave_inv[26]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (c >= 'A' && c <= 'Z')
            resultado[i] = chave_inv[c - 'A'];
        else if (c >= 'a' && c <= 'z')
            resultado[i] = chave_inv[c - 'a'] + 32;
        else
            resultado[i] = c;
    }
    resultado[i] = '\0';
}
// Função para descriptografar usando uma chave direta (sem inversão), usada pela heurística
// A heurística trabalha diretamente com permutações, então essa função facilita testes.
void descriptografar_com_chave(const char* texto, char* resultado, const char chave[26]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (c >= 'A' && c <= 'Z') {
            // Para descriptografar, precisamos achar a letra original que mapeia para c.
            // Como chave é uma permutação: dado resultado[i], queremos i tal que chave[i] == c.
            // Como não podemos usar estruturas complexas, fazemos busca linear:
            int j;
            for (j = 0; j < 26; j++) {
                if (chave[j] == c) {
                    resultado[i] = 'A' + j;
                    break;
                }
            }
            if (j == 26) resultado[i] = c; // não achou, copia igual
        } else if (c >= 'a' && c <= 'z') {
            // mesma lógica para minúsculas
            char c_upper = c - 32;
            int j;
            for (j = 0; j < 26; j++) {
                if (chave[j] == c_upper) {
                    resultado[i] = 'a' + j;
                    break;
                }
            }
            if (j == 26) resultado[i] = c;
        } else {
            resultado[i] = c;
        }
    }
    resultado[i] = '\0';
}

void decipher(const char* texto, const char chave[26], char* resultado) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (c >= 'A' && c <= 'Z') {
            // busca na chave qual índice leva a c
            for (int j = 0; j < 26; j++) {
                if (chave[j] == c) {
                    resultado[i] = 'A' + j;
                    break;
                }
            }
        } else if (c >= 'a' && c <= 'z') {
            for (int j = 0; j < 26; j++) {
                if (chave[j] == (c - 32)) { // compara com maiúscula
                    resultado[i] = 'a' + j;
                    break;
                }
            }
        } else {
            resultado[i] = c;
        }
    }
    resultado[i] = '\0';
}