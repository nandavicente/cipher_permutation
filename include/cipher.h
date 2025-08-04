// cipher.h
#ifndef CIPHER_H
#define CIPHER_H
#include "constants.h"

void criptografar(const char* texto, char* resultado, const char chave[26]);
void descriptografar(const char* texto, char* resultado, const char chave_inv[26]);

// Descriptografa o texto usando a chave direta (permutações) — para heurística.
void descriptografar_com_chave(const char* texto, char* resultado, const char chave[26]);
void decipher(const char* texto, const char chave[26], char* resultado);

#endif
