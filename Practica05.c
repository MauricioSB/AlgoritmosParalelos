#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>
#include <math.h>

#define CHAR_BITS 2


/* Funcion que permite la impresion de un arreglo
 * X el arreglo que va recibir
 * n es el tamanio del arreglo
 */
int imprimeArreglo(int *X, int n)
{
	printf("Arreglo inicial: \n");
	for (int i = 1; i < n; i++)
	{
		printf("%d,", X[i]);
	}
	printf("\n");
}

int imprimeResultado(int *X, int n)
{
	printf("Arreglo final: \n");
	for (int i = 1; i < n; ++i)
	{
		printf("%d,", X[i]);
	}
	printf("\n");	
}

void binario(int num)
{
	int sup = CHAR_BITS*sizeof(int);
	while(sup >= 0)
	{
		if (num & (((long int)1) << sup))
		{
			printf("1");
		} else
		{
			printf("0");
		}
		sup--;
	}
	printf("\n");
}

 int main(int argc, char const *argv[])
 {
 	//Numero de vertices
	int n;
	//Semilla para hacer random los elementos del arreglo
	int semilla;
	if (argc < 2)
	{
		printf("Por favor, especifique el numero de hilos\n");
		exit(1);
	} 
	//Escanea potencia como primer argumento
	sscanf(argv[1], "%i", &n);
	//Escanea la semilla como segundo argumento
	sscanf(argv[2], "%i", &semilla);
	if (n < 1 || semilla < 1)
	{
		printf("Por favor ingresa numeros positivos\n");
		exit(1);
	}
	srand(semilla);
	//Le asignamos el tamanio del arreglo con 2^k	
	int *X = (int*)malloc((n+1)*sizeof(int));
	int *repetir = (int*)malloc((n+1)*sizeof(int));
	int i = 1;

	//Se llena el arreglo con números aleatorios, según la semilla. 
    for (int i = 1; i<n; i++){
        int elementoPoner = rand()%(n)+1;
        if(repetir[elementoPoner]==0){
            X[i] = elementoPoner;
            repetir[elementoPoner] = 1;
        }else{
            i--;
        }
    }

	imprimeArreglo(X,n);

	for (int i = 1; i < n; i++)
	{
		binario(X[i]);	
	}			
 	return 0;
 }