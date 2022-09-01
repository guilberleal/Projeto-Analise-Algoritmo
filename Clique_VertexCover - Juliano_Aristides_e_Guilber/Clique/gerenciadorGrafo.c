#include "gerenciadorGrafo.h"

//cria um grafo vazio 
grafo *criaGrafoDesconexo(int qtdVertices){
	grafo *g = (grafo*)malloc(sizeof(grafo));
	g->size = qtdVertices;
	g->keys = NULL;
	g->mat3D = (int**)malloc(sizeof(int*)*qtdVertices);
	int i = 0, j;
	
	while(i < qtdVertices){
		g->mat3D[i] = (int*)malloc(sizeof(int)*qtdVertices);
		j = 0;
		while(j < qtdVertices){
			g->mat3D[i][j] = 0; //Inicializacao do grafo sem conexao entre os vertices
			j++;
		}
		i++;
	}
	
	return g;
}
//carrega o arquivo de entrada e armazena no grafo vazio
grafo *carregarGrafo(char *nomeArq){
	FILE *arq = fopen(nomeArq,"r");
	
	if(arq == NULL){
		return NULL;
	}
	
	int size;
	
	fscanf(arq,"%d", &size);
	grafo *g = criaGrafoDesconexo(size);
	int i, j;
	
	while(fscanf(arq,"%d %d", &i, &j) != EOF){
		g->mat3D[i][j] = 1;
	}
	
	return g;
}

//varre a matriz e salva o grafo no txt de saida
int salvarGrafo(grafo *g, char*nomeArq){
	FILE *arq = fopen(nomeArq,"w+");
	
	if(arq == NULL){
		return 0;
	}
	
	int i = 0, j;
	fprintf(arq,"%d\n", g->size);
	
	while(i < g->size){
		j = 0;
		while(j < g->size){
			if(g->mat3D[i][j]){
				fprintf(arq,"%d %d\n", i, j);
			}
			j++;
		}
		i++;
	}
	
	return 1;
}

//printa o grafo
void showGrafo(grafo *g){
	int i = 0, j, flag;
	
	if(g != NULL){
		while(i < g->size){
			printf("[%d] => ", i);
			flag = 1;
			j = 0;
			while(j < g->size){
				if(g->mat3D[i][j]){ 
					printf("[%d]", j);
					flag = 0;
				}
				j++;
			}
			
			if(flag){
				printf("Desconectado");
			}
			
			printf("\n");
			i++;
		}
	}else{
		printf("Grafo Inexistente!\n");
	}
}

//nega a matriz, aonde tinha conecçao passa a nao ter e aonde nao tinha agora tem
grafo *grafoComplemento(grafo *g){
	grafo *complemento = criaGrafoDesconexo(g->size);
	int i = 0, j;
	
	while(i < g->size){
		j = 0;
		while(j < g->size){
			//A segunda verificacao eh para evitar que um no fique conectado com ele mesmo
			if((!g->mat3D[i][j]) && (i != j)){
				complemento->mat3D[i][j] = 1;
			}
			j++;
		}
		i++;
	}
	
	//Verifica se ja tem solucao para o grafo a ser convertido
	if(g->keys != NULL){ // só entra na volta reducao da solucao do vertex para o clique
		i = 0;
		complemento->keys = g->keys;
		while(i < g->size){
			complemento->keys[i] = !complemento->keys[i];
			i++;
		}
	}
	
	return complemento;
}

//Cria tabela verdade
int **getPossibilidades(int qtdVertices){
	int linhas = pow(2,qtdVertices);
	int **tabela = (int**)malloc(sizeof(int*)*linhas); //criando linhas
	
	int i = 0, j;
	while(i < linhas){
		tabela[i] = (int*)malloc(sizeof(int)*qtdVertices); //criando colunas
		i++;
	}
	
	j = 0;
	int aux = linhas/2; 
	int flag = 1; //valor verdade
	
	//escreve V(1) e F(0) na tabela verdade
	while(j < qtdVertices){
		i = 0;
		while(i < linhas){
			if((i%aux) == 0){ 
				flag = !flag;
			}
			tabela[i][j] = flag;
			i++;
		}
		
		aux = aux/2;
		
		j++;
	}
	
	return tabela;
}

//printa a tabela
void showTabela(int **tabela, int sizeCol){
	int linhas = pow(2,sizeCol);
	int i = 0, j;
	
	while(i < linhas){
		j = 0;
		while(j < sizeCol){
			printf("[%d]", tabela[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

//conta a quantidade de vigias(vertices solucao)
int qtdVigias(int *guardas, int size){
	int i = 0, qtd = 0;
	
	while(i < size){
		if(guardas[i]){
			qtd++;
		}
		i++;
	}
	
	return qtd;
}

//ele analiza todo vertice que nao é vigia e compara se ele é conexo com outro que tambem nao é vigia
int ehSolucao(grafo *g, int *arranjo){
	int i = 0, j;
	
	while(i < g->size){
		if(!arranjo[i]){ //Verifica se nao eh guarda = (1)
			j = 0;
			while(j < g->size){
				//Verifica se existe um NO nao guarda que esta conectado a outro NO nao guarda
				//E que seja diferente dele mesmo
				if((g->mat3D[i][j] && !arranjo[j]) && (i != j)){
					return 0;
				}
				j++;
			}
		}
		i++;
	}
	
	return 1;
}


grafo *resolveVertex(grafo *g){
	int linhas = pow(2,g->size);
	int **tabVerdade = getPossibilidades(g->size);
	int i = 1, qtdMinGuardas = 0, flag;
	int *solucao = NULL;
	
	while(i < linhas){
		flag = qtdVigias(tabVerdade[i],g->size);
		if(ehSolucao(g,tabVerdade[i]) && ((flag < qtdMinGuardas) || (qtdMinGuardas == 0))){ //verifica se é uma solucao com menos vigias que a solucao ja encontrada
			qtdMinGuardas = flag; // atualiza o flag
			solucao = tabVerdade[i]; // vetor de solucao recebe a linha da tabela verdade 
		}
		i++;
	}
	
	if(solucao != NULL){ //verifica se achou ou nao a resposta
		g->keys = solucao;
		return g;
	}else{
		return NULL;
	}
}

grafo *resolveClique(grafo *clique, int k){
	if(k <= 1){
		return NULL;
	}
	grafo *g = grafoComplemento(clique); 
	int linhas = pow(2,g->size);
	int **tabVerdade = getPossibilidades(g->size);
	int i = 1, qtdMinGuardas = 0, flag;
	int *solucao = NULL;
	int qtdVig = g->size - k;
	if(qtdVig == 0){
		return NULL;
	}
	
	while(i < linhas){
		flag = qtdVigias(tabVerdade[i],g->size);
		if(qtdVig == flag){
			if(ehSolucao(g,tabVerdade[i]) && ((flag < qtdMinGuardas) || (qtdMinGuardas == 0))){
				qtdMinGuardas = flag;
				solucao = tabVerdade[i];
				break;
			}
		}
		i++;
	}
	
	if(solucao != NULL){
		g->keys = solucao;
		g = grafoComplemento(g);
		return g;
	}else{
		return NULL;
	}
}
//printa os vertices solucao
void showSolucao(grafo *g){
	if((g != NULL) && (g->keys != NULL)){
		int i = 0;
		
		while(i < g->size){
			if(g->keys[i]){
				printf("[%d]", i);
			}
			i++;
		}
	}else{
		printf("Sem solucao!\n");
	}
}

//aloca o vetor de uma possivel solucao dada como entrada
int *criaInstanciaToSolucao(int qtdNOs){
	int *ins = (int*)malloc(sizeof(int)*qtdNOs);
	int i = 0;
	
	while(i < qtdNOs){
		ins[i] = 0;
		i++;
	}
	
	return ins;
}
//le a instancia do possivel solucao
void preencherInstancia(int *ins, int size){
	if(ins != NULL){
		int i = 0;
		int qtdEscolha = 0;
		printf("Escolha os NOs Possiveis: ");
		while(i < size){
			printf("[%d]",i);
			i++;
		}
		printf("\nQuantos nos fazem parte da sua solucao? ");
		scanf("%d",&qtdEscolha);
		if((qtdEscolha > 0) && (qtdEscolha <= size)){
			int no = 0;
			i = 0;
			while(i < qtdEscolha){
				scanf("%d", &no);
				if((no >= 0) && (no < size)){
					ins[no] = 1;
					i++;
				}else{
					printf("Valor %d invalido\n", no);
				}
			}
		}else{
			printf("Quantidade %d Invalida\n", qtdEscolha);
		}
	}else{
		printf("Instancia Inexistente!\n");
	}
}
