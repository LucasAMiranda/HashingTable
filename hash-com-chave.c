#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 53

typedef struct sElemento {
   char nome[31];
   struct sElemento *next;
   struct sElemento *prev;
} Elemento;

typedef struct sLista {
     struct sElemento *head;
     struct sElemento *tail;
     int tam;
} Lista;
 
typedef struct sTabelaHash {
   Lista *chaves[SIZE];
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

int main(void) {
  TabelaHash *hash;
  hash = criaTabela();
    
  FILE* arquivo = fopen("nomes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  char linha[31];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';
    insereNaTabela(hash, linha);
  }

  fclose(arquivo);

  percorreTabela(hash);
  
  return 0;
}

Lista* criaLista() {
  Lista* lista = (Lista*) malloc(sizeof(Lista));
  if (lista == NULL) {
    return NULL;
  }
  else {
    lista->head = NULL;
    lista->tail = NULL;
    lista->tam = 0;
  }
  return lista;
}

TabelaHash* criaTabela() {
  TabelaHash* tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
  if (tabela == NULL) {
    return NULL;
  } else {
    for (int i = 0; i < SIZE; i++) {
      tabela->chaves[i] = criaLista();
    }
  }
  return tabela;
}

Elemento* criaElemento(char nome[]) {
  Elemento* nodo = (Elemento*) malloc(sizeof(Elemento));
  if (nodo == NULL) {
    return NULL;
  } else {
    strcpy(nodo->nome, nome);
    nodo->next = NULL;
    nodo->prev = NULL;
  }
  return nodo;
}

int insereNaLista(Lista* lista, Elemento* novo) {
  if (lista == NULL || novo == NULL) {
    return 0;
  }
  
  if (lista->head == NULL) {
    lista->head = novo;
    lista->tail = novo;
  } else {
    novo->prev = lista->tail;
    lista->tail->next = novo;
    lista->tail = novo;
  }
  
  lista->tam++;
  return 1;
}

int removeDaLista(Lista* lista, Elemento* elemento) {
  if (lista == NULL || elemento == NULL) {
    return 0;
  }
  
  if (elemento == lista->head) {
    lista->head = elemento->next;
    if (lista->head == NULL) {
      lista->tail = NULL;
    } else {
      lista->head->prev = NULL;
    }
  } else {
    elemento->prev->next = elemento->next;
    if (elemento->next == NULL) {
      lista->tail = elemento->prev;
    } else {
      elemento->next->prev = elemento->prev;
    }
  }
  
  free(elemento);
  lista->tam--;
  return 1;
}

Elemento* pesquisaNaLista(Lista* lista, char nome[]) {
  if (lista == NULL) {
    return NULL;
  }

  Elemento* aux = lista->head;
  while (aux != NULL) {
    if (strcmp(aux->nome, nome) == 0) {
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}

void percorreLista(Lista* lista) {
  if (lista == NULL || lista->head == NULL) {
    return;
  }

  Elemento* aux = lista->head;
  while (aux != NULL) {
    printf("%s, ", aux->nome);
    aux = aux->next;
  }
}

void limpaLista(Lista* lista) {
  if (lista == NULL) {
    return;
  }

  while (lista->head != NULL) {
    removeDaLista(lista, lista->head);
  }
  free(lista);
}

int funcaoHash(char* nome) {
  int h = 0;
  for (int i = 0; i < strlen(nome); i++) {
    h = ((31 * h + (int) nome[i]) % SIZE);
  }
  return h;
}

void insereNaTabela(TabelaHash* tabela, char nome[]) {
  int posicao = funcaoHash(nome);
  Elemento* novo = criaElemento(nome);
  if (novo != NULL) {
    insereNaLista(tabela->chaves[posicao], novo);
  }
}

void removeNaTabela(TabelaHash* tabela, char nome[]) {
  int posicao = funcaoHash(nome);
  Elemento* elemento = pesquisaNaLista(tabela->chaves[posicao], nome);
  if (elemento != NULL) {
    removeDaLista(tabela->chaves[posicao], elemento);
  }
}

void percorreTabela(TabelaHash* tabela) {
  for (int i = 0; i < SIZE; i++) {
    printf("\nChave: %i\n", i);
    percorreLista(tabela->chaves[i]);
  }
}
