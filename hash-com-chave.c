#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gnuplot_c.h>

#define MAX_NOMES 100788
#define TAM_MAX_NOME 100
#define NUM_CHAVES 53

typedef struct Node {
    char nome[TAM_MAX_NOME];
    struct Node* prox;
    struct Node* ant;
} Node;

Node* tabela[NUM_CHAVES];

int hash(const char* nome) {
    int soma = 0;
    int i = 0;
    while (nome[i] != '\0') {
        soma += (int) nome[i];
        i++;
    }
    return soma % NUM_CHAVES;
}

void inserirNome(const char* nome) {
    int chave = hash(nome);

    // Criar um novo nó para o nome
    Node* novoNome = (Node*) malloc(sizeof(Node));
    strcpy(novoNome->nome, nome);
    novoNome->prox = NULL;
    novoNome->ant = NULL;

    // Verificar se a chave está vazia
    if (tabela[chave] == NULL) {
        tabela[chave] = novoNome;
    } else {
        // Caso contrário, inserir no final da lista
        Node* atual = tabela[chave];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNome;
        novoNome->ant = atual;
    }
}

int consultarNome(const char* nome) {
    int chave = hash(nome);

    // Verificar se a chave está vazia
    if (tabela[chave] == NULL) {
        return 0;
    }

    // Procurar o nome na lista
    Node* atual = tabela[chave];
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return 1; // Nome encontrado
        }
        atual = atual->prox;
    }

    return 0; // Nome não encontrado
}

int contarElementosPorChave(int chave) {
    int count = 0;

    // Verificar se a chave está vazia
    if (tabela[chave] == NULL) {
        return 0;
    }

    // Contar os elementos na lista
    Node* atual = tabela[chave];
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }

    return count;
}

void removerNome(const char* nome) {
    int chave = hash(nome);

    // Verificar se a chave está vazia
    if (tabela[chave] == NULL) {
        return;
    }

    // Procurar o nome na lista
    Node* atual = tabela[chave];
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            // Remover o nó da lista
            if (atual->ant == NULL) {
                // O nó é o primeiro da lista
                tabela[chave] = atual->prox;
            } else {
                atual->ant->prox = atual->prox;
            }
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            }
            free(atual);
            return;
        }
        atual = atual->prox;
    }
}

void exibirHistograma() {
    // Configurar o gnuplot para plotagem
    gnuplot_ctrl* gp;
    gp = gnuplot_init();

    // Preparar os dados para plotagem
    int contagens[NUM_CHAVES] = {0};
    for (int i = 0; i < NUM_CHAVES; i++) {
        contagens[i] = contarElementosPorChave(i);
    }

    // Enviar os dados para o gnuplot
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
}

int main() {
    // Inicializar todas as posições como vazias
    for (int i = 0; i < NUM_CHAVES; i++) {
        tabela[i] = NULL;
    }

    // Abrir o arquivo
    FILE* arquivo = fopen("nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler os nomes do arquivo e inserir na tabela hash
    char linha[TAM_MAX_NOME];
    while (fgets(linha, TAM_MAX_NOME, arquivo) != NULL) {
        // Remover o caractere de nova linha (\n) da string
        linha[strcspn(linha, "\n")] = '\0';

        inserirNome(linha);
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Exibir o histograma
    exibirHistograma();

    // Buscar um nome específico
    char nome_desejado[TAM_MAX_NOME] = "VALDELUZIA";
    int chave_desejada = hash(nome_desejado);

    if (consultarNome(nome_desejado)) {
        printf("O nome %s está na base de dados.\n", nome_desejado);
    } else {
        printf("O nome %s não foi encontrado na base de dados.\n", nome_desejado);
    }

    // Remover um nome da base de dados
    char nome_remover[TAM_MAX_NOME] = "VALDELUZIA";
    removerNome(nome_remover);

    // Exibir o histograma atualizado após a remoção
    exibirHistograma();

    // Liberar a memória alocada
    for (int i = 0; i < NUM_CHAVES; i++) {
        Node* atual = tabela[i];
        while (atual != NULL) {
            Node* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    return 0;
}
