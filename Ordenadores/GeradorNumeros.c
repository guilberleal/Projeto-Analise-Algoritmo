
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int i,k;

    int max_element = atoi(argv[1]);
    int max_value = atoi(argv[2]);
    FILE *arqv;
    int controle;
    //nome do arquivo de saida com numeros aleatorios que nao se repetem
    char *namearq="";

    
    srand(time(NULL));

    printf("name: %s\n",argv[3]);
    arqv = fopen(argv[3],"w");
    srand(time(NULL));
    if(arqv == NULL){
        printf("Erro na abertura do arquivo.\n");
    }        
    for(i=0; i < max_element; i++){
        
        controle = (1+rand() % 999999);
        if(controle < max_value){
            fprintf(arqv,"%d\n", controle);
        } else {
            i--;
        }
    }

   
    fclose(arqv);
    arqv = NULL;    

    
     return 0;
}


