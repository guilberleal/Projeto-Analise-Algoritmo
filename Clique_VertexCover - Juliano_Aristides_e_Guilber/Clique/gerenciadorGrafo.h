#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Grafo{
	int size; // qtd de vertices
	int *keys; //Armazena a solucao, vetor de inteiro armazena a solucao da tabela vedade
	int **mat3D;	//estruturacao do grafo, aonde é 1 tem aresta aonde tem 0 eles nao sao conectados
}grafo;

grafo *criaGrafoDesconexo(int qtdVertices);
grafo *carregarGrafo(char *nomeArq);
int salvarGrafo(grafo *g, char*nomeArq);
void showGrafo(grafo *g);
grafo *grafoComplemento(grafo *g);
int **getPossibilidades(int qtdVertices);
void showTabela(int **tabela, int sizeCol);
int ehSolucao(grafo *g, int *arranjo);
grafo *resolveVertex(grafo *g);
grafo *resolveClique(grafo *clique, int k);
void showSolucao(grafo *g);

int *criaInstanciaToSolucao(int qtdNOs);
void preencherInstancia(int *ins, int size);
