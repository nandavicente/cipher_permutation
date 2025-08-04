// src/psf_analyzer.cpp
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cctype>

#include "psf_analyzer.h"

bool analisar_psf_hexdump(const char* caminho_entrada, const char* caminho_saida) {
    std::ifstream in(caminho_entrada, std::ios::binary);
    std::ofstream out(caminho_saida);

    if (!in || !out) {
        std::cerr << "Erro ao abrir arquivos para leitura/escrita.\n";
        return false;
    }

    unsigned char byte;
    int count = 0;
    while (in.read((char*)&byte, 1)) {
        out << std::hex << std::setw(2) << std::setfill('0') << (int)byte << ' ';
        if (++count % 16 == 0) out << '\n';
    }

    return true;
}

bool extrair_dados_psf(const char* caminho_entrada, const char* caminho_saida) {
    std::ifstream in(caminho_entrada, std::ios::binary);
    std::ofstream out(caminho_saida);

    if (!in || !out) {
        std::cerr << "Erro ao abrir arquivos para leitura/escrita.\n";
        return false;
    }

    unsigned char byte;
    while (in.read((char*)&byte, 1)) {
        if (std::isprint(byte))
            out << byte;
        else
            out << '.';
    }

    return true;
}
