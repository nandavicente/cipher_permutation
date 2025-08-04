# 🔐 Cipher Permutation Breaker

Projeto de engenharia reversa e quebra de cifra por permutação monoalfabética usando heurísticas como **Hill Climbing** e **Simulated Annealing**.

## 💡 Objetivo

O projeto simula a análise de arquivos criptografados (como `.psf`) usando apenas estatísticas de frequência de bigramas da língua para **recuperar o texto original sem conhecer a chave**.

---

## 🛠️ Funcionalidades

- **Cifra por permutação** (criptografia simples de substituição).
- **Quebra heurística** com:
  - Hill Climbing (`--heuristica hc`)
  - Simulated Annealing (`--heuristica sa`)
- **Benchmark automático** com:
  - Múltiplas execuções (10+)
  - Score de texto (log de probabilidade)
  - Tempo de execução
  - Acurácia da chave
- **Leitura via texto ou arquivo**
- **Suporte a múltiplos idiomas via arquivos de bigramas**

---

## 📁 Estrutura
```text 
cipher_permutation/
├── include/ # Headers: cipher.h, breaker.h, benchmark.h etc.
├── src/ # Códigos-fonte em C++
├── data/
│ └── bigrams/
│ ├── pt-br.txt # Frequência de bigramas em português
│ └── en.txt # (opcional) Frequência em inglês
├── entrada.txt # Texto de entrada (exemplo)
├── analisador # Binário compilado
└── README.md # Este arquivo
```

---

##  Como compilar

```bash
g++ src/*.cpp -o analisador -Iinclude
🔍 Exemplos de uso
Benchmark com entrada direta:
```
```bash
Copiar código
./analisador --modo benchmark --texto "ESTE É UM TEXTO TESTE" --heuristica hc --bigrams data/bigrams/pt-br.txt
````
```bash
Benchmark com arquivo:
````
```bash
bash
Copiar código
./analisador --modo benchmark --arquivo entrada.txt --heuristica sa --bigrams data/bigrams/pt-br.txt
````
Saída gerada (CSV)
csv

seed,tempo_ms,score,acuracia
1754316307,69.00,0.0452,19.23
1754316344,51.00,0.0421,7.69
1754316381,52.00,0.0397,0.00
1754316418,55.00,0.0000,7.69
1754316455,50.00,0.0943,0.00
1754316492,61.00,0.0111,7.69
1754316529,58.00,0.0665,0.00
1754316566,59.00,0.0371,11.54
1754316603,52.00,0.1101,0.00
1754316640,45.00,0.0304,7.69
Media,55.20,0.0477,6.15

````
🧠 Autor
Projeto desenvolvido por [Maria Fernanda de Oliveira Vicente], com foco em engenharia reversa, criptografia clássica e análise de desempenho heurístico.

