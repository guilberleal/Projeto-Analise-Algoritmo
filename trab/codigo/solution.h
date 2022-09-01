#ifndef SOLUTION_H
#define SOLUTION_H
//34.5

#include <stdlib.h>
#include "graph.h"


typedef struct SOLUTION{
    int size, *solution, vec_size;
}Solution;

void print_solution(Solution *s);
void copy_solution(Solution *from, Solution *to);
Solution *new_solution(int size);
void free_solution(Solution *s);
void reset_solution(Solution *s);
Solution *solution_vertex_cover(Graph *G);
int verify_solution(Graph *G, Solution *s);
void convert_vertex_solution_to_clique(Solution *s);
Solution *clique_solution(Graph *G);

int comb(int m, int n, unsigned char *c, Solution *s, Graph *G)
{
    int i;
	for (i = 0; i < n; i++) c[i] = n - i;

	while (1) {
        reset_solution(s);
		for (i = n; i--;)
			s->solution[c[i]] = 1;
        if (verify_solution(G, s)){
            s->size = n;
            return 1;
        }

		i = 0;
		if (c[i]++ < m) continue;
 
		for (; c[i] >= m - i;) if (++i >= n) return 0;
		for (c[i]++; i; i--) c[i-1] = c[i] + 1;
	}
}


//copy a solution from "from" to "to"
void copy_solution(Solution *from, Solution *to){
    to->size = from->size;
    for (int i = 0; i<from->vec_size; i++){
        to->solution[i] = from->solution[i];
    }
}


//print solution for debugging
void print_solution(Solution *s){
    if (s){
        printf("solution size: %d\n", s->size);
        for (int i = 0; i < s->vec_size; i++){
            if (s->solution[i]) printf("%d ", i);
        }
        printf("\n");
    }else{
        printf("No solution\n");
    }
}


//alloc a new solution
Solution *new_solution(int size){
    Solution *s = (Solution*) malloc(sizeof(Solution));
    s->solution = (int*) malloc(sizeof(int) * size);
    s->size = 0;
    s->vec_size = size;
    for (int i = 0; i < size; i++){
        s->solution[i] = 0;
    }
    return s;
}

//free a solution
void free_solution(Solution *s){
    free(s->solution);
    free(s);
}


//reset the solution back to all 0
void reset_solution(Solution *s){
    for (int i = 0; i < s->vec_size; i++){
        s->solution[i] = 0;
    }
}


//gets a optimal solution to vertex cover problem
//brute forcing through every combination
Solution *solution_vertex_cover(Graph *G){
    char buffer[200];
    int is_isolated = 1;
    Solution *optimal = new_solution(G->current_size);
    Solution *current = new_solution(G->current_size);
    for (int i = 0; i < G->current_size; i++ ){
        if (G->vector[i].number_of_edges == 0){
            continue;
        }
        is_isolated = 0;
        break;
    }
    if (is_isolated){
        return optimal;
    }
    for(int i = G->current_size -1; i >= 1; i--){
        //if there are n vertices, first it tries finding a solution
        //in every combination of n-1 vertices
        //if it finds a solution it then tries within every combination of n-2
        //vertices and so on until it doesnt find a solution at every combination of
        // n-k vertices, so, the optimal solution is n-k+1
        if (comb(G->current_size, i, buffer, current, G)){
            copy_solution(current, optimal);
        }else{
            break;
        }
    }
    free_solution(current);
    return optimal;
}


//it verifies if a solution s is a solution for
//the vertex cover problem in graph G
int verify_solution(Graph *G, Solution *s){
    Node *iterator;
    //iterates through every vertex
    for(int i = 0; i < G->current_size; i++){
        //if the vertex is in the solution
        //jump it
        if(s->solution[i]){
            continue;
        }
        //if not, goes through every edge
        iterator = G->vector[i].head;
        while(iterator){
            //if i find an edge that is not connect to
            //a solution edge, then the solution is wrong
            if (!s->solution[iterator->value]){
                return 0;
            }
            iterator = iterator->next;
        }
    }
    return 1;
}


void convert_vertex_solution_to_clique(Solution *s){
    for(int i = 0; i < s->vec_size; i++){
        s->solution[i] = !s->solution[i];
    }
    s->size = s->vec_size - s->size;
}



Solution *clique_solution(Graph *G){
    //converte o grafo para uma entrada do problema vertex
    /**************************************************************************************
    ** O pior caso eh quando G eh o contrario de completo
    ** então o complemento de G seria um grafo completo
    ** um grafo completo tem (n*(n-1))/2 arestas, ou seja,
    ** iria chamar a função add_edge que tem complexidade O(n), n*(n-1), pois é este grafo
    ** se trata de um digrafo, se a está ligado em b, b está ligado em a
    ** então no pior caso, graph_complement tem a complexidade de O(n^2 * (n-1)), aprox O(n^3)
    ** se tratando então de uma função que pode ser executada em tempo polinomial
    **************************************************************************************/
    Graph *entrada_vertex = graph_complement(G);
    //soluciona o problema vertex
    /**************************************************************************************
    ** Para achar uma solução otima e deterministica para o vertex cover
    ** Foi usado uma espécie de brute force, testando todas as combinatorias de vertices
    ** Ex: Para um grafo de tamanho 3, temos os vertices 0, 1 e 2
    ** O algoritmo começa testando todas as amostras de tamanho n-1, ou seja, no nosso
    ** exemplo ele começa testando amostras com n de tamanho 2
    ** ele verifica se 0 1 é uma solução, se não, continua testando, verifca 0 2, se for uma
    ** solução, o algoritmo para de executar as amostras de tamanho n-1 e retorna a
    ** solução otima atual.
    ** Já que foi encontrado uma solução com tamanho n-1, tentaremos achar uma solução com
    ** amostras de tamanho n-2, isso continua até que o algoritmo tenta todas as
    ** amostras de tamanho n-k e falha em encontrar uma solução, ou até n-k = 0.
    ** assim sabemos que a solução ótima é de tamanho n-k+1
    ** 
    ** Para um grafo de n vertices, com uma amostra de tamanho r
    ** existem ( n! / (r! * (n-r)! ) ) amostras
    ** O pior caso do algoritmo é quando a solução otima é de tamanho 1
    ** e esse unico vertice está sempre presente na ultima amostra
    ** assim o algoritmo terá que rodar n-1 vezes testando todas as amostras
    ** então a complexidade do algoritmo pode ser expressa por um somatorio de k = 1 até n-1
    ** com a formula (n*(n-1)) * ( n! / (k! * (n-k)! ) )
    ** Onde n * (n-1) é o custo para verificar se uma solução é valida
    ** e ( n! / (k! * (n-k)! ) ) é o tamanho do total de amostras com k sendo o tamanho da amostra
    ** Como o fatorial está presente no dividendo e é sempre maior que o resultado do fatorial que está
    ** no divisor, pode-se inferir que esta função para encontrar uma solução otima para o vertex cover
    ** testando todas as combinações possiveis tem uma complexidade, no seu pior caso, exponencial
    ** Sendo assim, pode-se inferir que a complexidade é O(n!)
    **************************************************************************************/
    Solution *solucao = solution_vertex_cover(entrada_vertex);

    //para liberar o grafo, percorre-se por todas as arestas
    //assim, no pior caso, tem-se uma complexidade de O(n*(n-1)) aprox O(n^2)
    free_graph(entrada_vertex);
    
    //converte a solucao para uma solucao do clique
    /**************************************************************************************
    ** para converter a solução, percorre-se o vetor de solução de tamanho n
    ** fazendo uma operação basica de negação em cada elemento do vetor
    ** assim tendo uma complexidade de Θ(n)
    **************************************************************************************/
    convert_vertex_solution_to_clique(solucao);
    return solucao;
}

#endif