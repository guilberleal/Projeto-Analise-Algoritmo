#include <stdlib.h>
#include <stdio.h>
#include "solution.h"
#include "graph.h"

#define GRAPH_FILE_PATH "graph.txt"



int main(){
    //inicializando o grafo do problema do clique
    Graph clique_problem;
    initialize_graph(&clique_problem);

    //inicializando o arquivo
    FILE *file;
    file = fopen(GRAPH_FILE_PATH, "r");
    int V,E;


    if (file){
        //preenchendo o grafo tendo o arquivo como entrada
        while(fscanf(file, "%d%d", &V, &E) != EOF){
            add_edge(&clique_problem, V, E);
        }
        //printando o grafo preenchido
        print_graph(&clique_problem);
        printf("\n\n\n");
        //printando a solucao
        print_solution(clique_solution(&clique_problem));
    }else{
        printf("Nao foi possivel abrir " GRAPH_FILE_PATH "\n");
    }
}