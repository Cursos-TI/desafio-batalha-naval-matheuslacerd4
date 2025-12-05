#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

#define LINHAS 10
#define COLUNAS 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define AFETADO 5

int main() {
    // Declaração da matriz do tabuleiro 10x10
    int tabuleiro[LINHAS][COLUNAS];

    // Inicialização do tabuleiro com 0 (representando água)
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- Posicionamento dos Navios ---
    // Vamos posicionar 4 navios: 1 Horizontal, 1 Vertical, 2 Diagonais.

    // 1. Navio Horizontal
    int h_linha = 3;
    int h_coluna = 1;
    if (h_coluna + TAM_NAVIO <= COLUNAS) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[h_linha][h_coluna + i] = NAVIO;
        }
        printf("Navio Horizontal posicionado.\n");
    }

    // 2. Navio Vertical
    int v_linha = 6;
    int v_coluna = 7;
    if (v_linha + TAM_NAVIO <= LINHAS) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[v_linha + i][v_coluna] = NAVIO;
        }
        printf("Navio Vertical posicionado.\n");
    }

    // 3. Navio Diagonal Principal
    int d1_linha = 0;
    int d1_coluna = 0;
    if (d1_linha + TAM_NAVIO <= LINHAS && d1_coluna + TAM_NAVIO <= COLUNAS) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[d1_linha + i][d1_coluna + i] = NAVIO;
        }
        printf("Navio Diagonal Principal posicionado.\n");
    }

    // 4. Navio Diagonal Secundária
    int d2_linha = 1;
    int d2_coluna = 8;
    if (d2_linha + TAM_NAVIO <= LINHAS && d2_coluna - TAM_NAVIO + 1 >= 0) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[d2_linha + i][d2_coluna - i] = NAVIO;
        }
        printf("Navio Diagonal Secundaria posicionado.\n");
    }

    // --- Definição das Matrizes de Habilidade ---
    int matrizCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int matrizCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int matrizOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    int centro = TAM_HABILIDADE / 2; // Centro da matriz (2 para tamanho 5)

    // Construção das matrizes de habilidade
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Inicializa com 0
            matrizCone[i][j] = 0;
            matrizCruz[i][j] = 0;
            matrizOctaedro[i][j] = 0;

            // Habilidade Cone (Triângulo apontando para cima na matriz, ou seja, base embaixo? 
            // O enunciado diz: "ponto de origem no topo e expandindo-se em direção à base".
            // Vamos fazer um triângulo simples nas primeiras linhas.
            // Linha 0: 1 ponto (centro)
            // Linha 1: 3 pontos
            // Linha 2: 5 pontos
            if (i <= centro) { // Limita a altura do cone
                if (j >= (centro - i) && j <= (centro + i)) {
                    matrizCone[i][j] = 1;
                }
            }

            // Habilidade Cruz (Linha central ou Coluna central)
            if (i == centro || j == centro) {
                matrizCruz[i][j] = 1;
            }

            // Habilidade Octaedro (Losango: Distância de Manhattan <= centro)
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matrizOctaedro[i][j] = 1;
            }
        }
    }

    // --- Aplicação das Habilidades no Tabuleiro ---
    // Definindo pontos de origem (centros) para as habilidades no tabuleiro
    int origemCone_linha = 2, origemCone_coluna = 4;
    int origemCruz_linha = 5, origemCruz_coluna = 2;
    int origemOcta_linha = 7, origemOcta_coluna = 7;

    // Aplicando Cone
    printf("\nAplicando Habilidade Cone em (%d, %d)\n", origemCone_linha, origemCone_coluna);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matrizCone[i][j] == 1) {
                int tab_i = origemCone_linha - centro + i;
                int tab_j = origemCone_coluna - centro + j;
                // Verifica limites do tabuleiro
                if (tab_i >= 0 && tab_i < LINHAS && tab_j >= 0 && tab_j < COLUNAS) {
                    tabuleiro[tab_i][tab_j] = AFETADO;
                }
            }
        }
    }

    // Aplicando Cruz
    printf("Aplicando Habilidade Cruz em (%d, %d)\n", origemCruz_linha, origemCruz_coluna);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matrizCruz[i][j] == 1) {
                int tab_i = origemCruz_linha - centro + i;
                int tab_j = origemCruz_coluna - centro + j;
                if (tab_i >= 0 && tab_i < LINHAS && tab_j >= 0 && tab_j < COLUNAS) {
                    tabuleiro[tab_i][tab_j] = AFETADO;
                }
            }
        }
    }

    // Aplicando Octaedro
    printf("Aplicando Habilidade Octaedro em (%d, %d)\n", origemOcta_linha, origemOcta_coluna);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matrizOctaedro[i][j] == 1) {
                int tab_i = origemOcta_linha - centro + i;
                int tab_j = origemOcta_coluna - centro + j;
                if (tab_i >= 0 && tab_i < LINHAS && tab_j >= 0 && tab_j < COLUNAS) {
                    tabuleiro[tab_i][tab_j] = AFETADO;
                }
            }
        }
    }

    // --- Exibição do Tabuleiro ---
    printf("\n--- Tabuleiro Batalha Naval ---\n");
    printf("0 = Agua, 3 = Navio, 5 = Habilidade\n\n");
    
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}