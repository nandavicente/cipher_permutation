import pandas as pd
import matplotlib.pyplot as plt

def analisar_benchmark(caminho_csv='results/benchmark.csv'):
    df = pd.read_csv(caminho_csv)

    # Filtra dados
    df_media = df[df['seed'] == 'Media']
    df_clean = df[df['seed'] != 'Media']

    df_clean['seed'] = df_clean['seed'].astype(int)
    df_clean['tempo_ms'] = df_clean['tempo_ms'].astype(float)
    df_clean['score'] = df_clean['score'].astype(float)
    df_clean['acuracia'] = df_clean['acuracia'].astype(float)

    # Calcula médias
    media_tempo = df_clean['tempo_ms'].mean()
    media_score = df_clean['score'].mean()
    media_acuracia = df_clean['acuracia'].mean()

    # Mostra dados básicos
    print("=== Estatísticas do Benchmark ===")
    print(df_clean.describe())
    print(f"\nMédias calculadas:")
    print(f"Tempo médio: {media_tempo:.2f} ms")
    print(f"Score médio: {media_score:.4f}")
    print(f"Acurácia média: {media_acuracia:.2f} %")

    if not df_media.empty:
        print("\nMédias do CSV:")
        print(df_media[['tempo_ms', 'score', 'acuracia']])

    # Função para salvar gráfico
    def salvar_grafico(fig, nome_arquivo):
        fig.savefig(nome_arquivo, bbox_inches='tight')
        print(f"Gráfico salvo em {nome_arquivo}")

    # Gráfico Tempo x Acurácia
    fig1, ax1 = plt.subplots(figsize=(10,6))
    ax1.scatter(df_clean['tempo_ms'], df_clean['acuracia'], c='blue', label='Execuções')
    ax1.set_xlabel('Tempo (ms)')
    ax1.set_ylabel('Acurácia (%)')
    ax1.set_title('Tempo vs Acurácia')
    ax1.grid(True)
    ax1.legend()
    salvar_grafico(fig1, 'results/tempo_vs_acuracia.png')
    plt.close(fig1)

    # Gráfico Score x Tempo
    fig2, ax2 = plt.subplots(figsize=(10,6))
    ax2.scatter(df_clean['tempo_ms'], df_clean['score'], c='green', label='Execuções')
    ax2.set_xlabel('Tempo (ms)')
    ax2.set_ylabel('Score')
    ax2.set_title('Score vs Tempo')
    ax2.grid(True)
    ax2.legend()
    salvar_grafico(fig2, 'results/score_vs_tempo.png')
    plt.close(fig2)

    # Gráfico Score x Acurácia
    fig3, ax3 = plt.subplots(figsize=(10,6))
    ax3.scatter(df_clean['score'], df_clean['acuracia'], c='red', label='Execuções')
    ax3.set_xlabel('Score')
    ax3.set_ylabel('Acurácia (%)')
    ax3.set_title('Score vs Acurácia')
    ax3.grid(True)
    ax3.legend()
    salvar_grafico(fig3, 'results/score_vs_acuracia.png')
    plt.close(fig3)

    # Gráfico barras médias
    fig4, ax4 = plt.subplots(figsize=(8,5))
    labels = ['Tempo (ms)', 'Score', 'Acurácia (%)']
    medias = [media_tempo, media_score, media_acuracia]
    ax4.bar(labels, medias, color=['orange', 'purple', 'cyan'])
    ax4.set_title('Médias do Benchmark')
    ax4.set_ylabel('Valor Médio')
    ax4.grid(axis='y')
    salvar_grafico(fig4, 'results/medias_benchmark.png')
    plt.close(fig4)

    # Gerar mini-relatório txt
    with open('results/relatorio_benchmark.txt', 'w') as f:
        f.write("=== Relatório Benchmark ===\n\n")
        f.write(f"Tempo médio (ms): {media_tempo:.2f}\n")
        f.write(f"Score médio: {media_score:.4f}\n")
        f.write(f"Acurácia média (%): {media_acuracia:.2f}\n\n")
        f.write("Gráficos salvos em:\n")
        f.write(" - results/tempo_vs_acuracia.png\n")
        f.write(" - results/score_vs_tempo.png\n")
        f.write(" - results/score_vs_acuracia.png\n")
        f.write(" - results/medias_benchmark.png\n")
    print("Relatório salvo em results/relatorio_benchmark.txt")

if __name__ == "__main__":
    analisar_benchmark()
