#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Vertice {
    int dado;
    struct Vertice* prox;
};

struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
};

struct Grafo {
    int numVertices;
    struct Vertice* listasAdjacencia[MAX_VERTICES];
};

struct Vertice* criarVertice(int dado) {
    struct Vertice* novoVertice = (struct Vertice*)malloc(sizeof(struct Vertice));
    novoVertice->dado = dado;
    novoVertice->prox = NULL;
    return novoVertice;
}

struct Aresta* criarAresta(int destino, int peso) {
    struct Aresta* novaAresta = (struct Aresta*)malloc(sizeof(struct Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;
    return novaAresta;
}

struct Grafo* criarGrafo(int n) {
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->numVertices = n;

    for (int i = 0; i < n; i++) {
        grafo->listasAdjacencia[i] = NULL;
    }

    return grafo;
}

void adicionarAresta(struct Grafo* grafo, int origem, int destino, int peso) {
    struct Aresta* aresta = criarAresta(destino, peso);
    aresta->prox = grafo->listasAdjacencia[origem];
    grafo->listasAdjacencia[origem] = aresta;
}

void imprimirGrafo(struct Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        struct Aresta* atual = grafo->listasAdjacencia[i];
        printf("Vértice %d: ", i);
        while (atual != NULL) {
            printf("(%d, %d) -> ", atual->destino, atual->peso);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

void buscaEmLargura(struct Grafo* grafo, int inicio, int fim) {
    bool visitado[MAX_VERTICES] = {false};
    int pai[MAX_VERTICES] = {-1};

    visitado[inicio] = true;
    pai[inicio] = -1;

    // Implementação da busca em largura (BFS)
    int fila[MAX_VERTICES];
    int frente = 0, fimFila = 0;

    fila[fimFila++] = inicio;

    while (frente < fimFila) {
        int verticeAtual = fila[frente++];
        struct Aresta* atual = grafo->listasAdjacencia[verticeAtual];

        while (atual != NULL) {
            int destino = atual->destino;
            if (!visitado[destino]) {
                visitado[destino] = true;
                pai[destino] = verticeAtual;
                fila[fimFila++] = destino;
            }
            atual = atual->prox;
        }
    }

    // Imprimir o caminho mais curto
    printf("Caminho mais curto entre %d e %d: ", inicio, fim);
    int vertice = fim;
    while (vertice != -1) {
        printf("%d", vertice);
        vertice = pai[vertice];
        if (vertice != -1) {
            printf(" <- ");
        }
    }
    printf("\n");
}

int main() {
    struct Grafo* grafo = criarGrafo(6);

    adicionarAresta(grafo, 0, 1, 2);
    adicionarAresta(grafo, 0, 2, 4);
    adicionarAresta(grafo, 1, 2, 1);
    adicionarAresta(grafo, 1, 3, 7);
    adicionarAresta(grafo, 2, 4, 3);
    adicionarAresta(grafo, 3, 5, 2);
    adicionarAresta(grafo, 4, 5, 5);

    int inicio = 0;
    int fim = 5;

    buscaEmLargura(grafo, inicio, fim);

    return 0;
}
