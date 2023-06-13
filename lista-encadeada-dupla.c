#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Node {
    int key;
    char value[50];
    struct Node* next;
    struct Node* prev;
} Node;

Node* criarNo(int key, const char* value) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->key = key;
    strcpy(novoNo->value, value);
    novoNo->next = NULL;
    novoNo->prev = NULL;
    return novoNo;
}

void inserir(Node* tabelaHash[], int key, const char* value) {
    int index = key % SIZE;

    if (tabelaHash[index] == NULL) {
        tabelaHash[index] = criarNo(key, value);
        return;
    }

    Node* novoNo = criarNo(key, value);
    novoNo->next = tabelaHash[index];
    tabelaHash[index]->prev = novoNo;
    tabelaHash[index] = novoNo;
}

Node* buscar(Node* tabelaHash[], int key) {
    int index = key % SIZE;
    Node* currentNode = tabelaHash[index];

    while (currentNode != NULL) {
        if (currentNode->key == key) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    return NULL;
}

int contar(Node* tabelaHash[], int key) {
    int index = key % SIZE;
    Node* currentNode = tabelaHash[index];
    int count = 0;

    while (currentNode != NULL) {
        if (currentNode->key == key) {
            count++;
        }
        currentNode = currentNode->next;
    }

    return count;
}

void removerElemento(Node* tabelaHash[], int key) {
    int index = key % SIZE;
    Node* currentNode = tabelaHash[index];

    while (currentNode != NULL) {
        if (currentNode->key == key) {
            if (currentNode->prev != NULL) {
                currentNode->prev->next = currentNode->next;
            }
            if (currentNode->next != NULL) {
                currentNode->next->prev = currentNode->prev;
            }
            free(currentNode);
            return;
        }
        currentNode = currentNode->next;
    }
}

void trocar(Node* arr[], int i, int j);

void quickSort(Node* arr[], int low, int high) {
    if (low < high) {
        int pivot = particionar(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int particionar(Node* arr[], int low, int high) {
    Node* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j]->key < pivot->key) {
            i++;
            trocar(arr, i, j);
        }
    }

    trocar(arr, i + 1, high);
    return i + 1;
}

void trocar(Node* arr[], int i, int j) {
    Node* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void imprimirTabelaHash(Node* tabelaHash[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("Posição %d: ", i);
        Node* currentNode = tabelaHash[i];
        while (currentNode != NULL) {
            printf("(%d, %s) ", currentNode->key, currentNode->value);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

void ordenarElementosPorChave(Node* tabelaHash[], int key) {
    int index = key % SIZE;
    Node* currentNode = tabelaHash[index];
    int count = contar(tabelaHash, key);

    if (count <= 1) {
        return;
    }

    Node* arr[count];
    int i = 0;

    while (currentNode != NULL) {
        if (currentNode->key == key) {
            arr[i] = currentNode;
            i++;
        }
        currentNode = currentNode->next;
    }

    quickSort(arr, 0, count - 1);

    for (int j = 0; j < count - 1; j++) {
        arr[j]->next = arr[j + 1];
        arr[j + 1]->prev = arr[j];
    }

    arr[0]->prev = NULL;
    arr[count - 1]->next = NULL;

    tabelaHash[index] = arr[0];
}

int main() {
    Node* tabelaHash[SIZE];
    memset(tabelaHash, 0, SIZE * sizeof(Node*));

    inserir(tabelaHash, 10, "Valor 1");
    inserir(tabelaHash, 20, "Valor 2");
    inserir(tabelaHash, 10, "Valor 3");
    inserir(tabelaHash, 30, "Valor 4");

    printf("Tabela Hash antes da ordenação:\n");
    imprimirTabelaHash(tabelaHash);

    int chave = 10;
    ordenarElementosPorChave(tabelaHash, chave);

    printf("Tabela Hash após a ordenação:\n");
    imprimirTabelaHash(tabelaHash);

    return 0;
}
