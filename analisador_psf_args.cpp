#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "psf_analyzer.h"
#include "benchmark.h"

void mostrar_ajuda() {
    printf("Uso:\n");
    printf("  analisador_psf --input caminho.psf --output resultado.txt [--modo hexdump|extrair|quebrar]\n");
    printf("\n");
    printf("Modo 'quebrar' opções adicionais:\n");
    printf("  --heuristica hillclimb|simann       Heurística (padrão: hillclimb)\n");
    printf("  --bigramas freq.txt                 Arquivo de frequências de bigramas\n");
    printf("  --iteracoes N                       Iterações (padrão: 10000)\n");
    printf("  --temperatura T                     Temperatura inicial (simulated annealing)\n");
    printf("  --resfriamento R                    Fator de resfriamento (simulated annealing)\n");
    printf("  --seed S                            Semente aleatória (opcional)\n");
}

int main(int argc, char* argv[]) {
    const char* caminho_input = nullptr;
    const char* caminho_output = "saida.txt";
    const char* modo = "hexdump";

    // Parâmetros do modo 'quebrar'
    const char* heuristica = "hillclimb";
    const char* caminho_bigramas = "data/freq_en.txt";
    int iteracoes = 10000;
    double temperatura = 10.0;
    double resfriamento = 0.95;
    int seed = -1;  // aleatório se não fornecido

    // Parse de argumentos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            caminho_input = argv[++i];
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            caminho_output = argv[++i];
        } else if (strcmp(argv[i], "--modo") == 0 && i + 1 < argc) {
            modo = argv[++i];
        } else if (strcmp(argv[i], "--heuristica") == 0 && i + 1 < argc) {
            heuristica = argv[++i];
        } else if (strcmp(argv[i], "--bigramas") == 0 && i + 1 < argc) {
            caminho_bigramas = argv[++i];
        } else if (strcmp(argv[i], "--iteracoes") == 0 && i + 1 < argc) {
            iteracoes = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--temperatura") == 0 && i + 1 < argc) {
            temperatura = atof(argv[++i]);
        } else if (strcmp(argv[i], "--resfriamento") == 0 && i + 1 < argc) {
            resfriamento = atof(argv[++i]);
        } else if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            seed = atoi(argv[++i]);
        }
    }

    if (!caminho_input) {
        printf("Erro: caminho de input não fornecido.\n\n");
        mostrar_ajuda();
        return 1;
    }

    if (strcmp(modo, "hexdump") == 0) {
        if (!analisar_psf_hexdump(caminho_input, caminho_output)) {
            printf("Falha ao processar arquivo em modo hexdump.\n");
            return 1;
        }
    } else if (strcmp(modo, "extrair") == 0) {
        if (!extrair_dados_psf(caminho_input, caminho_output)) {
            printf("Falha ao extrair dados do arquivo .psf.\n");
            return 1;
        }
    } else if (strcmp(modo, "quebrar") == 0) {
        if (!executar_benchmark(
                caminho_input,
                caminho_output,
                caminho_bigramas,
                heuristica,
                iteracoes,
                temperatura,
                resfriamento,
                seed)) {
            printf("Falha ao quebrar cifra.\n");
            return 1;
        }
    } else {
        printf("Erro: modo '%s' não reconhecido.\n\n", modo);
        mostrar_ajuda();
        return 1;
    }

    printf("Processamento concluído com sucesso.\n");
    return 0;
}
