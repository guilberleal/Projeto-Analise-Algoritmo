#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
//node of a linked list
#define MAX_SIZE 100
#define EMPTY_VERTEX -1

typedef struct NODE{
    int value;
    struct NODE *next;
}Node;


typedef struct VERTEX{
    int value;
    int number_of_edges;
    struct NODE *head;
}Vertex;

//static list of vertexes
//which is a graph
typedef struct GRAPH{
    struct VERTEX vector[MAX_SIZE];
    int current_size;
}Graph;


//alloc a new edge dinamically and returns its address
Node *new_edge(int value){
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
}


void initialize_graph(Graph *G){
    for(int i=0; i<MAX_SIZE; i++){
        G->vector[i].head = NULL;
        G->vector[i].number_of_edges = 0;
        G->vector[i].value = EMPTY_VERTEX;
    }
    G->current_size = 0;
}


//adds an edge to the list of edges from a
//vertex, its a recursive function, and it adds
//the edge in ascending order 
void add_to_edge_list(Node **edge, int value){
    if (*edge){
        if ((*edge)->value > value){
            Node *new_node = new_edge(value);
            new_node->next = *edge;
            *edge = new_node;
        }else{
            add_to_edge_list(&(*edge)->next, value);
        }
    }else{
        *edge = new_edge(value);
    }
}

//add an edge to the graph G
//conecting the vertex V to the vertex E
void add_edge(Graph* G, int V, int E){
    if (G->vector[V].value == EMPTY_VERTEX){    //Θ(1)
        G->vector[V].value = V;                 //O(1)
        G->current_size++;                      //O(1)
    }
    add_to_edge_list(&(G->vector[V].head), E);  //O(n)
    G->vector[V].number_of_edges++;             //Θ(1)
}                                               //so this function is O(n)

//print graph for debugging
void print_graph(Graph *G){
    int i = -1;
    Node *iterator;
    printf("Number of vertices: %d\n", G->current_size);
    while(G->vector[++i].value != EMPTY_VERTEX){
        printf("Edges: %d ::: |%d| -> ", G->vector[i].number_of_edges, G->vector[i].value);
        for (iterator = G->vector[i].head; iterator; iterator = iterator->next){
            printf("[%d] -> ", iterator->value);
        }
        printf("[NULL]\n");
    }
}

//returns a new graph taking the complement of
//the graph G "parameter"
Graph *graph_complement(Graph *G){
    int i = -1, edge_value;
    Graph *complement = malloc(sizeof(Graph));
    Node *iterator;
    initialize_graph(complement);

    //goes until it finds a empty vertex
    while(G->vector[++i].value != EMPTY_VERTEX){
        edge_value = 0;
        complement->vector[i].value = i;
        //iterate through a list of edges from Vertex i
        for (iterator = G->vector[i].head; iterator; iterator = iterator->next){
            //here i take the advantage that the edges are in ascending order
            //so, in each edge i get the edges that are missing from value until the edge value
            //ie: |Vertex 0| -> [v3] -> [v4] -> [NULL]
            //what this while is doing is:
            //putting the edge 1 and 2 to the graphs complement
            while(edge_value < iterator->value){
                if (i == edge_value){ //ignoring looping edges
                    edge_value++;
                }else{
                    add_edge(complement, i, edge_value++);
                }
            }
            edge_value++;
        }
        //if there are still edges to add
        while(edge_value < G->current_size && i != edge_value){
            add_edge(complement, i, edge_value++);
        }
    }
    complement->current_size = G->current_size;
    return complement;
}

void free_list(Node *node){
    if(node){
        free_list(node->next);
        free(node);
    }
}

//free graph
void free_graph(Graph *G){
    for(int i = 0; i < G->current_size; i++){
        free_list(G->vector[i].head);
    }
    free(G);
}
#endif