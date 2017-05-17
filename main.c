#include "load.h"
#include <time.h>


#define DIM 500000
int contI = 0, contR = 0, contB = 0;

//******************************************************************************
//                      FUNCION printArray
//Imprime un array por pantalla
//******************************************************************************

void printArray(int array[], int dim){
    int i;

    for(i = 0; i < dim; i++)
        printf("%d ", array[i]);

    printf("\n");
    
}

//******************************************************************************
//                      FUNCION ricercaBanale
//Busca un elemento en un array(muy lento)
//******************************************************************************
int ricercaBanale(int miarray[], int numric, int dim){
    
    int pos=0;
    //Mientras que no haya llegado al final y no haya encontrado el numero
    while(pos<dim && miarray[pos]<=numric){   
        contB++;
        //si lo ecuentra,retorna posicion
        if(numric==miarray[pos]){
            return pos;
        }else{
            pos++;
        }
    }
    return -1;
}


//******************************************************************************
//                      FUNCION ricercaBintariaIter
//Su funcion es buscar un elemento en una array de una forma un poco mas rapida
//******************************************************************************

int ricercaBinariaIter(int array[],int numric,int dim){
    
    int primo=0;
    int ultimo=dim-1;
    //Partimos el array en dos trozos,para como minimo reducir el tiempo de 
    //busqueda a la mitad
    while(primo<=ultimo){
        contI++;
        //aqui partimos el vector en dos
        int mezzo=(primo+ultimo)/2;
        if(numric<array[mezzo]){
            ultimo=mezzo-1;
        }else{
            if(numric==array[mezzo]){
                return mezzo;
            }else{
                primo=mezzo+1;
                
            }
        }
           
    }
    
    return -1;
}

//******************************************************************************
//                      FUNCION ricBinRic
//Su funcion es buscar un elemento en un array de forma recursiva
//******************************************************************************

int ricBinRic(int array[],int numric,int primo,int ultimo){
    int mezzo=0;
    
    //Caso base
    if(primo>ultimo){
        return -1;
    }
    //Partimos el vector en dos
    mezzo=(primo+ultimo)/2;
    //
    if(array[mezzo]==numric){
            //contR++;

        return mezzo;
    }else{
        if(array[mezzo]<numric){
            contR++;

            
            return ricBinRic(array,numric,mezzo+1,ultimo);
        }else{
            contR++;

            return ricBinRic(array,numric,primo,mezzo-1);
        }
    }
}

int main() 
{
    //Numero a buscar
    int numric;
    //Cargamos el array de un fichero
    int *array = loadFromFile(DIM);
    //printArray(array,DIM);
    //Declaramos las variables para calcular los tiempos
    clock_t start,start1,start2,end,end1,end2;
    double time,time1,time2;
    printf("Teclee el numero que desea buscar: ");
    scanf("%d",&numric);

    //Le damos la hora a la variable star
    start=clock();
    //Buscamos con la funcion banale
    int c=ricercaBanale(array,numric,DIM);
    end=clock();
    start1=clock();
    //buscamos con la funcion iterativa
    int a=ricercaBinariaIter(array,numric,DIM);
    end1=clock();
    start2=clock();
    //Buscamos con la funcion recursiva
    int b=ricBinRic(array,numric,0,DIM-1);
    end2=clock();
    
    //Calculamos el tiempo que ha tardado
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    time1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    time2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    
    printf("Posicion para la busqueda banal: %d\n",c);
    printf("POsicion para la busqueda iterativa: %d\n",a);
    printf("Posicion para la busqueda recursiva: %d\n",b);
    
    printf("\nPasos de la busqueda banal: %d\n",contB);
    printf("Pasos para ls buequeda iterativa: %d\n",contI);
    printf("Pasos para la busqueda recursiva: %d\n",contR);
    
    printf("\nTiempo para la busqueda banal: %f segundos", time);
    printf("\nTiempo para la busqueda iterativa: %f segundos", time1);
    printf("\nTiempo para la busqueda recursiva: %f segundos\n\n", time2);
    
    return 0;
}
