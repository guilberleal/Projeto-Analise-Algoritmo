#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int SIZE = 1000;


void InsertionSort(int *Point, int Max);
void count_sort(int *numbers, int size);
void bubble_sort(int *vet);
void QuickSort(int *vet,int begin,int end);
void Merge(int *vet,int begin, int middle, int end);
void Sort(int *vet,int begin, int end);
void read_archive(int *vet, char *name);
void QuickSort_rand(int *vet,int begin,int end);
void test(int *vet, char *name_a);
void clear_vet(int *vet);

int main(int argc, char const *argv[])
{
	int *vet;
    vet = (int*)malloc( sizeof(int) * SIZE);     
    char *name_a = "arq1.txt";
    test(vet,name_a);     
  
	return 0;	
}


void test(int *vet, char *name_a){
	clock_t start_time, end_time;
	double time_cost;

	
	read_archive(vet, name_a);
    
	printf("antes: %d %d\n",vet[0],vet[SIZE-1]);
	start_time = clock();
	bubble_sort(vet);
	end_time = clock();
	time_cost =(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf( "Execution time was %lfs\n",time_cost );
	printf("%d %d // bubble: ok\n\n",vet[0],vet[SIZE-1]);
	

	read_archive(vet, name_a);
	printf("antes: %d %d\n",vet[0],vet[SIZE-1]);
	start_time = clock();
	QuickSort(vet, 0, SIZE-1);
	end_time = clock();
	time_cost =(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf( "Execution time was %lfs\n",time_cost );
	printf("%d %d // Quick: ok\n\n",vet[0], vet[SIZE-1]);
	

	read_archive(vet, name_a);
	printf("antes: %d %d\n",vet[0],vet[SIZE-1]);
	start_time = clock();
	QuickSort_rand(vet, 0, SIZE-1);
	end_time = clock();
	time_cost =(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf( "Execution time was %lfs\n",time_cost );
	printf("%d %d // Quick random: ok\n\n",vet[0], vet[SIZE-1]);

	read_archive(vet, name_a);
	printf("antes: %d %d\n",vet[0],vet[SIZE-1]);
	start_time = clock();
	InsertionSort(vet, SIZE);
	end_time = clock();
	time_cost = (double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf( "Execution time was %lfs\n",time_cost );
	printf("%d %d Insertion: ok\n\n",vet[0], vet[SIZE-1]);
	

	read_archive(vet, name_a);
	printf("antes: %d %d\n",vet[0],vet[SIZE-1]);
	start_time = clock();
	Sort(vet, 0, SIZE-1);
	end_time = clock();
	time_cost =(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf( "Execution time was %lfs\n",time_cost );
	printf("%d %d // Merge: ok\n\n",vet[0],vet[SIZE-1]);

    

	read_archive(vet, name_a);
	printf("antes: %d %d\n",vet[0],vet[SIZE-1]);
	start_time = clock();
	count_sort(vet, SIZE);
	end_time = clock();
	time_cost =(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf( "Execution time was %lfs\n",time_cost );
	printf("%d %d // Count: ok\n\n",vet[0],vet[SIZE-1]);
    
}


void read_archive(int *vet,char *name){

    int n;
    int i;
    FILE *arqv;
 
    //recebe nome de arquivo com valores desordenados
    // ex.: 1000-arq1.txt
    
    arqv = fopen(name,"r");

    if(arqv == NULL){
        printf("Fail, could not open file.\n");
    }

    i = 0;

    while( !feof(arqv) ){
        
        fscanf(arqv,"%d",&n);
        vet[i++] = n;
    }

    fclose(arqv);
	
   
}


void bubble_sort(int *vet){
    int i, j,aux;

    for(j = SIZE - 1; j >= 1; j--){

        for(i = 0; i < j; i++){
                
                if(vet[i] > vet[i+1]){

                    aux = vet[i];
                    vet[i] = vet[i+1];
                    vet[i+1] = aux;
                }
        }
        
    }
    
}

void QuickSort(int *vet,int begin,int end){

    int i,j,pivo,aux;
    i = begin;
    j = end;

    pivo = vet[( ( end + begin )/2 )];
    
    while ( i <= j){
        
        if (vet[i] < pivo){

            i++;
        } else if( vet[j] > pivo){
            j--;
        } else{
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    
    }
    if(j > begin){
        QuickSort(vet, begin, j);

    }
    if(i < end){
        QuickSort(vet,j+1,end);
    }
}
void QuickSort_rand(int *vet,int begin,int end){

    int i,j,pivo,aux;
    i = begin;
    j = end;

    pivo = vet[rand() % SIZE];
    
    while ( i <= j){
        
        if (vet[i] < pivo){

            i++;
        } else if( vet[j] > pivo){
            j--;
        } else{
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    
    }
    if(j > begin){
        QuickSort_rand(vet, begin, j);

    }
    if(i < end){
        QuickSort_rand(vet,j+1,end);
    }
}

void InsertionSort(int *Point, int Max){ 
   int i, key, j; 
   for (i = 1; i < Max; i++) 
   { 
       key = Point[i]; 
       j = i-1; 
       while (j >= 0 && Point[j] > key) 
       { 
           Point[j+1] = Point[j]; 
           j = j-1;
       } 
       Point[j+1] = key; 
   } 
}



// faz o merge e volta as galhas ordenando
void Merge(int *vet,int begin, int middle, int end){
        int *vetAux,size;
        int i,j,k;
        
        size = (end - begin) + 1;
        
        vetAux = (int*) malloc(sizeof(int) * size);
        // i com o inicio do subvetor a esquerda
        i = begin;
        // j com o inicio do subvetor a direita
        j = middle + 1;
        // tamanho do vetor inicial
        for(k = 0; k < size; k++){
            // verifica se os lados dos meus subvetores ainda tem valores a direita
            if(i < (middle+1) && j <= end){
                // faz a ordenacao crescente
                if(vet[i] < vet[j]){
                    
                    vetAux[k] = vet[i++];
                    
                }else{
                    
                    vetAux[k] = vet[j++];
                    
                }
                
            // se um dos subvetores chegou ao fim completa com o outro
            }else if(i < (middle+1) && j > end){
                
                vetAux[k] = vet[i++];
                
            }else{
                
                vetAux[k] = vet[j++];
                
            }
                
        }
        i = 0;
        for(k = begin; k <= end; k++){
            vet[k] = vetAux[i++];
            
        }
        free(vetAux);
            
}

void Sort(int *vet,int begin, int end){
    int middle;
    if( begin < end){
        middle = ( (begin + end)/ 2);
        // quebra pro lado esquerdo
        Sort(vet, begin, middle);
        // quebra pro lado direito
        Sort(vet, middle + 1, end);
        // faz o merge
        Merge(vet,begin, middle, end);
    }
    
}


void count_sort(int *numbers, int size)
{
	int i;
    int count[SIZE];
    for ( i=0; i<SIZE; i++)
        count[i] = 0;

    for ( i=0; i<size; i++)
        count[numbers[i]]++;

    int index = 0;
    for ( i=0; i<SIZE; i++)
    {
        while (count[i] > 0)
        {
            numbers[index] = i;
            index++;
            count[i]--;
        }
    }
}
