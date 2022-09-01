#include <stdio.h>
#include <stdlib.h>
#include "gerenciadorGrafo.h"

int main(int argc, char *argv[]) {
	
	grafo *g = carregarGrafo("exemplo1.txt");
	printf("Grafo do Clique\n");
	showGrafo(g);
	printf("\nVerifica se tem solucao do Clique com K NOs\n");
	showSolucao(resolveClique(g,6)); //teste com k
	
	printf("\nGrafo Complemento do Clique\n");
	grafo *complemento = grafoComplemento(g);
	showGrafo(complemento);
	
	printf("\nCrie sua solucao\n");
	int *ins = criaInstanciaToSolucao(complemento->size);
	preencherInstancia(ins,complemento->size);
	if(ehSolucao(complemento,ins)){
		printf("A instancia eh uma solucao!\n");
	}else{
		printf("A instancia nao eh uma solucao\n");
	}
	
	complemento = resolveVertex(complemento);
	printf("\nSolucao do Vertex\n");
	showSolucao(complemento);
	printf("\n");
	
	grafo *cliqueSolucao = grafoComplemento(complemento);
	printf("\nGrafo Complemento do Vertex\n");
	showGrafo(cliqueSolucao);
	printf("\nSolucao do Clique\n");
	showSolucao(cliqueSolucao);
	
	//showTabela(getPossibilidades(4),4);
	
	
	return 0;
}
