
// ---------------------------  Metodos de ordenacao ---------------------------


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Prototipos
void merge(int *Point,int i1,int j1,int i2,int j2);
void Merge_Sort(int *Point,int i,int j);
void Shell_Sort(int *Point, int Max);
void Selection_Sort (int *Point, int Max);
void Bubble_Sort (int *Point, int Max);
void QuickSort(int *Point, int inicio, int fim);
void InsertionSort(int *Point, int Max);
void CarregarArquivo(int *Point,int Num);
void CriaDoc(int *Point,int Num);
void RandNumb(int *Point,int Max);
void SaveFileSucesso(int *Point,int Num);
void PrintResult();

struct {
    long int troca;
    double tempo;
} Info; 

int * ArrayAux;

int main()  {
    clock_t end,start;
    srand ( time(NULL) );
    int OPC=0,
        OPC2=0;
    int * ArrayMestre = malloc(2 * sizeof(long int));
    ArrayAux = malloc(2 * sizeof(long int));

    do{
        printf("Tamanho do arquivo que deseja processar?\n");
        printf("0 - SAIR\n1 - 1000\n2 - 10000\n3 - 100000\n4 - 1000000\n");
        scanf("%d",&OPC);
        if(OPC==1){
            OPC=1000;
        }else if(OPC==2){
            OPC=10000;
        }else if(OPC==3){
            OPC=100000;
        }else if(OPC == 4){
            OPC = 1000000;
            printf("chegou aqui 1");
        }
        printf("\nchegou aqui 2");
        ArrayMestre = realloc(ArrayMestre, OPC * sizeof(long int));
        printf("\nchegou aqui 3");
        ArrayAux = realloc(ArrayAux, OPC * sizeof(long int));
        printf("\nchegou aqui 4");
        RandNumb(ArrayMestre,OPC);
        printf("\nchegou aqui 5");
        l(ArrayMestre,OPC);
        printf("\nChegou aqui 5\n");
        do{
            printf("\nChegou aqui 2\n");
            Info.tempo =0;
            Info.troca =0.0;
            printf("Metodo de ordenação?\n");
            printf("0 - SAIR\n1 - Quick_Sort\n2 - Insertion_Sort\n3 - Bubble_Sort\n4 - Selection_Sort\n5 - Shell_Sort\n6 - Merge_Sort\n");
            scanf("%d",&OPC2);
            if(OPC2!=0){
                start = clock();
                //OPC+1: Pois como sorteamos do 0 ao 1000, então temos 1001 numeros não repetidos.
                if(OPC2==1){
                    QuickSort(ArrayMestre,0,OPC);
                }else if(OPC2==2){
                    InsertionSort(ArrayMestre,OPC+1);
                }else if(OPC2==3){
                    Bubble_Sort(ArrayMestre,OPC+1);
                }else if(OPC2==4){
                    Selection_Sort(ArrayMestre,OPC+1);
                }else if(OPC2==5){
                    Shell_Sort(ArrayMestre,OPC+1);
                }else if(OPC2==6){
                    Merge_Sort(ArrayMestre,0,OPC);
                }
                end = clock();
                Info.tempo += 1000*(double)(end-start)/(double)(CLOCKS_PER_SEC);
                SaveFileSucesso(ArrayMestre,OPC);
                CarregarArquivo(ArrayMestre,OPC);
                PrintResult();
            }
        }while(OPC2!=0);
    }while(OPC!=0);
}

void merge(int *Point,int i1,int j1,int i2,int j2){    
	int i,j,k;
	i=i1;
	j=i2;
	k=0;
	while(i<=j1 && j<=j2){
		if(Point[i]<Point[j]){
			ArrayAux[k++]=Point[i++];
		}else{
			ArrayAux[k++]=Point[j++];
        }
	}
	
	while(i<=j1){	//copia os elementos restantes da segunda lista
		ArrayAux[k++]=Point[i++];
    }
		
	while(j<=j2){	//copia os elementos restantes da segunda lista
		ArrayAux[k++]=Point[j++];
    }
		
	//Transfer elements from temp[] back to a[]
	for(i=i1,j=0;i<=j2;i++,j++){
	    Point[i]=ArrayAux[j];
        // --- INFORMAÇÃO DE TROCA DE TROCA --
        Info.troca++;
    }
}
void Merge_Sort(int *Point,int i,int j){
	int mid;
		
	if(i<j){
		mid=(i+j)/2;
        //Recursão a esqueda.
		Merge_Sort(Point,i,mid);

        //Recursão a direita.
		Merge_Sort(Point,mid+1,j);

        //Merge dentro de dois arrays.
		merge(Point,i,mid,mid+1,j);
	}
}
void Shell_Sort(int *Point, int Max){
    int i = (Max - 1) / 2;
    int chave, k, aux;
    
    while(i != 0){
        do{
            chave = 1;
            for(k = 0; k < Max - i; ++k){
                if(Point[k] > Point[k + i]){
                    aux = Point[k];
                    Point[k] = Point[k + i];
                    Point[k + i] = aux;
                    chave = 0;

                    // --- INFORMAÇÃO DE TROCA DE TROCA --
                    Info.troca++;
                }
            }
        }while(chave == 0);
        i = i / 2;
    }
}

void Selection_Sort (int *Point, int Max){
    int i, j, min, aux;
    
    for (i = 0; i < (Max - 1); i++) {
        //O minimo é o primeiro número não ordenado ainda
        min = i;
        for (j = i+1; j < Max; j++) {
            // Caso tenha algum numero menor ele faz a troca do minimo
            if (Point[j] < Point[min]) {
            min = j;
            }
        }
        //Se o minimo for diferente do primeiro numero não ordenado ele faz a troca para ordena-los
        if (i != min) {
            aux = Point[i];
            Point[i] = Point[min];
            Point[min] = aux;
            // --- INFORMAÇÃO DE TROCA DE TROCA --
            Info.troca++;
        }
    }
}
void Bubble_Sort (int *Point, int Max){
    int k, j, aux;

    for (k = 1; k < Max; k++) {

        for (j = 0; j < Max - k; j++) {

            if (Point[j] > Point[j + 1]) {
                aux          = Point[j];
                Point[j]     = Point[j + 1];
                Point[j + 1] = aux;

                // --- INFORMAÇÃO DE TROCA DE TROCA --
                Info.troca++;
            }
        }
    }
}
void QuickSort(int *Point, int inicio, int fim){
    int i, j, meio, aux;
 
    i = inicio;
    j = fim;
    meio = Point[(inicio + fim) / 2];
 
    do{
        while(Point[i] < meio)
            i++;
        while(Point[j] > meio)
            j--;
        if(i <= j){
            aux = Point[i];
            Point[i] = Point[j];
            Point[j] = aux;
            i++;
            j--;

            // --- INFORMAÇÃO DE TROCA DE TROCA --
            Info.troca++;
        }
   }while(i <= j);
    if(inicio < j)
        QuickSort(Point, inicio, j);
    if(i < fim)
        QuickSort(Point, i, fim);
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

            // --- INFORMAÇÃO DE TROCA DE TROCA --
            Info.troca++;
       } 
       Point[j+1] = key; 
   } 
}
void  CarregarArquivo(int *Point,int Num){
    FILE *arq;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    int cont =0,
        temp=0;
    if(Num==1000){
        arq = fopen("1000-arq1.txt", "r");
    }else if(Num==10000){
        arq = fopen("10000-arq1.txt", "r");      
    }else if(Num==100000){
        arq = fopen("100000-arq1.txt", "r");
    }else if(Num==1000000){
        arq = fopen("1000000-arq1.txt", "r");
    }

    if(arq == NULL){
        printf("Arquivo não encontrado\n");
    }else{
        while (!feof (arq)){
            fscanf (arq, "%d", &Point[cont]);
            cont++;
        }
        printf("Arquivo carregado!\n");
    }
    fclose(arq);
}

void  CriaDoc(int *Point,int Num){
	int i;
    FILE *arq;
    if(Num==1000){
        arq = fopen("1000-arq1.txt", "a");
        arq = fopen("1000-arq1.txt", "w");
    }else if(Num==10000){
        arq = fopen("10000-arq1.txt", "a");
        arq = fopen("10000-arq1.txt", "w");        
    }else if(Num==100000){
        arq = fopen("100000-arq1.txt", "a");
        arq = fopen("100000-arq1.txt", "w");
    }else if(Num==1000000){
        arq = fopen("1000000-arq1.txt", "a");
        arq = fopen("1000000-arq1.txt", "w");
    }

    if(arq == NULL){
        printf("arquivo nao foi criado\n");
    }else{
        for( i = 0; i <= Num; i++){
            if(i!=Num){
                fprintf(arq, "%d\n",Point[i]);
            }else{
                fprintf(arq, "%d",Point[i]);
            }
        }
        printf("arquivo criado com sucesso !\n ");
    }
    fclose(arq);
}

void RandNumb(int *Point,int Max){
    int Temp=0;
    int * array = malloc(Max * sizeof(long int));
    int i;
    for( i = 0; i <= Max; i++){
        array[i]=0;
    }
    for( i = 0; i <= Max; i++){
        Point[i] = (rand() % (Max + 1 - 0)) + 0;
        if(array[Point[i]]==1){
            i--;
        }else{
            array[Point[i]]=1;
        }
    }
    free(array);
}
void SaveFileSucesso(int *Point,int Num){
	int i;
    FILE *arq;
    if(Num==1000){
        arq = fopen("1000-arq2.txt", "w");
    }else if(Num==10000){
        arq = fopen("10000-arq2.txt", "w");
    }else if(Num==100000){
        arq = fopen("100000-arq2.txt", "w");
    }else if(Num==1000000){
        arq = fopen("1000000-arq2.txt", "w");
    }

    if(arq == NULL){
        printf("Erro ao salvar arquivo!\n");
    }else{
        for( i = 0; i <= Num; i++){
            if(i!=Num){
                fprintf(arq, "%d\n",Point[i]);
            }else{
                fprintf(arq, "%d",Point[i]);
            }
        }
        printf("Arquivo salvo!\n");
    }
    fclose(arq);
}

void PrintResult(){
    printf("Quantidade de trocas: %ld\n",Info.troca);
    printf("Tempo de processamento: %f\n",Info.tempo);
}


