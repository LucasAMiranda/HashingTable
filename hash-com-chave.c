#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 53

typedef struct sElemento {
    char nome[30];
    struct sElemento* next;
    struct sElemento* prev;
} Elemento;

typedef struct sLista {
    struct sElemento* head;
    struct sElemento* tail;
    int tam;
} Lista;

typedef struct sTabelaHash {
    Lista* chaves[SIZE];
} TabelaHash;

// Funções da lista encadeada
Lista* criaLista();
Elemento* criaElemento(char*);
int insereNaLista(Lista*, Elemento*);
int removeDaLista(Lista*, Elemento*);
void percorreLista(Lista*);
Elemento* pesquisaNaLista(Lista*, char*);
void limpaLista(Lista*);

// Funções da tabela hash
int funcaoHash(char*);
void insereNaTabela(TabelaHash*, char*);
TabelaHash* criaTabela();
void percorreTabela(TabelaHash*);
void removeNaTabela(TabelaHash*, char*);
int verificaNome(TabelaHash*, char*);

// Funções de manipulação dos dados
void quickSort(char* arr[], int low, int high);
int partition(char* arr[], int low, int high);
void displayHistogram(TabelaHash* tabela);

int main(void) {
    TabelaHash* hash;
    hash = criaTabela();

    FILE* arquivo = fopen("nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[30];
    while (fgets(linha, 30, arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        insereNaTabela(hash, linha);
    }

    fclose(arquivo);

    int opcao;
    printf("Escolha uma opcao:\n");
    printf("1 - Verificar se um nome esta presente\n");
    printf("2 - Mostrar histograma de nomes\n");
    printf("3 - Remover um nome\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            char nomePesquisar[30];
            printf("Digite o nome a ser pesquisado: ");
            scanf("%s", nomePesquisar);

            if (verificaNome(hash, nomePesquisar)) {
                printf("O nome esta presente no arquivo.\n");
            } else {
                printf("O nome nao esta presente no arquivo.\n");
            }
            break;
        }
        case 2:
            displayHistogram(hash);
            break;
        case 3: {
            char nomeRemover[30];
            printf("Digite o nome a ser removido: ");
            scanf("%s", nomeRemover);
            removeNaTabela(hash, nomeRemover);
            printf("Nome removido com sucesso.\n");
            break;
        }
        default:
            printf("Opcao invalida.\n");
            break;
    }

    return 0;
}

Lista* criaLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        return NULL;
    } else {
        lista->head = NULL;
        lista->tail = NULL;
        lista->tam = 0;
    }
    return lista;
}

TabelaHash* criaTabela() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) {
        return NULL;
    } else {
        for (int i = 0; i < SIZE; i++) {
            tabela->chaves[i] = criaLista();
        }
    }
    return tabela;
}

Elemento* criaElemento(char* nome) {
    Elemento* elemento = (Elemento*)malloc(sizeof(Elemento));
    if (elemento == NULL) {
        return NULL;
    } else {
        strncpy(elemento->nome, nome, 30);
        elemento->next = NULL;
        elemento->prev = NULL;
    }
    return elemento;
}

int insereNaLista(Lista* lista, Elemento* elemento) {
    if (lista == NULL || elemento == NULL) {
        return 0;
    } else {
        if (lista->head == NULL) {
            lista->head = elemento;
            lista->tail = elemento;
        } else {
            lista->tail->next = elemento;
            elemento->prev = lista->tail;
            lista->tail = elemento;
        }
        lista->tam++;
    }
    return 1;
}

int removeDaLista(Lista* lista, Elemento* elemento) {
    if (lista == NULL || elemento == NULL) {
        return 0;
    } else {
        if (elemento == lista->head) {
            lista->head = elemento->next;
        } else {
            elemento->prev->next = elemento->next;
        }
        if (elemento == lista->tail) {
            lista->tail = elemento->prev;
        } else {
            elemento->next->prev = elemento->prev;
        }
        free(elemento);
        lista->tam--;
    }
    return 1;
}

void percorreLista(Lista* lista) {
    if (lista == NULL) {
        return;
    }
    Elemento* elemento = lista->head;
    while (elemento != NULL) {
        printf("%s\n", elemento->nome);
        elemento = elemento->next;
    }
}

Elemento* pesquisaNaLista(Lista* lista, char* nome) {
    if (lista == NULL || nome == NULL) {
        return NULL;
    }
    Elemento* elemento = lista->head;
    while (elemento != NULL) {
        if (strcmp(elemento->nome, nome) == 0) {
            return elemento;
        }
        elemento = elemento->next;
    }
    return NULL;
}

void limpaLista(Lista* lista) {
    if (lista == NULL) {
        return;
    }
    Elemento* elemento = lista->head;
    while (elemento != NULL) {
        Elemento* proximo = elemento->next;
        free(elemento);
        elemento = proximo;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->tam = 0;
}

int funcaoHash(char* chave) {
    if (chave == NULL) {
        return -1;
    }
    int soma = 0;
    int i = 0;
    while (chave[i] != '\0') {
        soma += (int)chave[i];
        i++;
    }
    return soma % SIZE;
}

void insereNaTabela(TabelaHash* tabela, char* nome) {
    if (tabela == NULL || nome == NULL) {
        return;
    }
    int posicao = funcaoHash(nome);
    Lista* lista = tabela->chaves[posicao];
    Elemento* elemento = criaElemento(nome);
    insereNaLista(lista, elemento);
}

void percorreTabela(TabelaHash* tabela) {
    if (tabela == NULL) {
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        Lista* lista = tabela->chaves[i];
        percorreLista(lista);
    }
}

void removeNaTabela(TabelaHash* tabela, char* nome) {
    if (tabela == NULL || nome == NULL) {
        return;
    }
    int posicao = funcaoHash(nome);
    Lista* lista = tabela->chaves[posicao];
    Elemento* elemento = pesquisaNaLista(lista, nome);
    if (elemento != NULL) {
        removeDaLista(lista, elemento);
    }
}

int verificaNome(TabelaHash* tabela, char* nome) {
    if (tabela == NULL || nome == NULL) {
        return 0;
    }
    int posicao = funcaoHash(nome);
    Lista* lista = tabela->chaves[posicao];
    Elemento* elemento = pesquisaNaLista(lista, nome);
    if (elemento != NULL) {
        return 1;
    }
    return 0;
}

void quickSort(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            char* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    char* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void displayHistogram(TabelaHash* tabela) {
    int count[SIZE] = {0};

    for (int i = 0; i < SIZE; i++) {
        Lista* lista = tabela->chaves[i];
        Elemento* elemento = lista->head;
        while (elemento != NULL) {
            count[i]++;
            elemento = elemento->next;
        }
    }

    char* nomes[SIZE];
    int totalNomes = 0;

    for (int i = 0; i < SIZE; i++) {
        if (count[i] > 0) {
            nomes[totalNomes] = tabela->chaves[i]->head->nome;
            totalNomes++;
        }
    }

    quickSort(nomes, 0, totalNomes - 1);

    printf("Histograma de Nomes:\n");
    for (int i = 0; i < totalNomes; i++) {
        printf("%s: ", nomes[i]);
        for (int j = 0; j < count[funcaoHash(nomes[i])]; j++) {
            printf("*");
        }
        printf("\n");
    }
}
