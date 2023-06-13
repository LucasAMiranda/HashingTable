#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMES 100788
#define TAM_MAX_NOME 100

int main() {
    char nomes[MAX_NOMES][TAM_MAX_NOME];

    // Abrir o arquivo
    FILE *arquivo = fopen("nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler os nomes do arquivo e armazenar na matriz
    int total_nomes = 0;
    char linha[TAM_MAX_NOME];
    while (fgets(linha, TAM_MAX_NOME, arquivo) != NULL && total_nomes < MAX_NOMES) {
        strcpy(nomes[total_nomes], linha);
        total_nomes++;
    }

    // Exemplo: contar o número total de nomes
    printf("Número total de nomes: %d\n", total_nomes);

    // Exemplo: encontrar um nome específico no arquivo "nomes.txt"
    char nome_desejado[TAM_MAX_NOME] = "João";
    int encontrado = 0;
    for (int i = 0; i < total_nomes; i++) {
        if (strcmp(nomes[i], nome_desejado) == 0) {
            encontrado = 1;
            break;
        }
    }
    if (encontrado) {
        printf("O nome %s está na base de dados.\n", nome_desejado);
    } else {
        printf("O nome %s não foi encontrado na base de dados.\n", nome_desejado);
    }

    // Exemplo: realizar operações estatísticas com os nomes
    // (encontrar o nome mais comum)
    int contador_nomes[MAX_NOMES] = {0};
    int nome_mais_comum_indice = 0;
    for (int i = 0; i < total_nomes; i++) {
        for (int j = 0; j < total_nomes; j++) {
            if (strcmp(nomes[i], nomes[j]) == 0) {
                contador_nomes[i]++;
            }
        }
        if (contador_nomes[i] > contador_nomes[nome_mais_comum_indice]) {
            nome_mais_comum_indice = i;
        }
    }
    printf("O nome mais comum é: %s\n", nomes[nome_mais_comum_indice]);

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}