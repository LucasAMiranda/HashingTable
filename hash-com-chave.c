#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gnuplot_c.h>

#define MAX_NOMES 100788
#define TAM_MAX_NOME 100
#define NUM_CHAVES 53

typedef struct {
    char nome[TAM_MAX_NOME];
    // Adicione outras informações adicionais, se necessário
} Registro;

int hash(const char* nome) {
    int soma = 0;
    int i = 0;
    while (nome[i] != '\0') {
        soma += (int) nome[i];
        i++;
    }
    return soma % NUM_CHAVES;
}

int main() {
    Registro tabela[NUM_CHAVES];

    // Inicializar todas as posições como vazias
    for (int i = 0; i < NUM_CHAVES; i++) {
        tabela[i].nome[0] = '\0';
    }

    // Abrir o arquivo
    FILE *arquivo = fopen("nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler os nomes do arquivo e inserir na tabela hash
    char linha[TAM_MAX_NOME];
    while (fgets(linha, TAM_MAX_NOME, arquivo) != NULL) {
        // Remover o caractere de nova linha (\n) da string
        linha[strcspn(linha, "\n")] = '\0';

        // Calcular a chave usando a função de hash
        int chave = hash(linha);

        // Inserir o nome na tabela hash
        strcpy(tabela[chave].nome, linha);
    }

    // Fechar o arquivo
    fclose(arquivo);

    //configurar o gnuplot- para plotar no gráfico

    gnuplot_ctrl *gp;
    gp = gnuplot_init();

    // Preparar os dados para plotagem
    char comando[100];
    sprintf(comando, "set xlabel 'Chave'");
    gnuplot_cmd(gp, comando);
    sprintf(comando, "set ylabel 'Contagem de Nomes'");
    gnuplot_cmd(gp, comando);
    sprintf(comando, "set title 'Distribuição dos Nomes nas Chaves'");
    gnuplot_cmd(gp, comando);
    sprintf(comando, "set style fill solid");
    gnuplot_cmd(gp, comando);
    sprintf(comando, "plot '-' using 1:2 with boxes");
    gnuplot_cmd(gp, comando);

    // Enviar os dados para o gnuplot
    for (int i = 0; i < NUM_CHAVES; i++) {
        sprintf(comando, "%d %d", i, contagens[i]);
        gnuplot_cmd(gp, comando);
    }
    gnuplot_cmd(gp, "e");

    // Aguardar ação do usuário antes de fechar o gráfico
    printf("Pressione enter para fechar o gráfico.\n");
    getchar();

    // Fechar o gnuplot
    gnuplot_close(gp);


    // buscar um nome específico
    char nome_desejado[TAM_MAX_NOME] = "João";
    int chave_desejada = hash(nome_desejado);

    if (strcmp(tabela[chave_desejada].nome, nome_desejado) == 0) {
        printf("O nome %s está na base de dados.\n", nome_desejado);
    } else {
        printf("O nome %s não foi encontrado na base de dados.\n", nome_desejado);
    }

    return 0;
}
