#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>
#include <math.h>
 

int existeElem(int *X, int n, int num)
{
	int enc = 0;
	for (int i = 1; i <= n && !enc; i++)
	{
		if(X[i] == num)
			enc = 1;
	}
	return enc;
}

void generador(int *X, int n)
{
	int num;
	srand(time(NULL));
	for (int i = 1; i <= n; i++)
	{
		while(existeElem(X, n, num = rand()%n+1));
		X[i] = num;
	}
}

int swap(int *X, int i, int j)
{
	int aux = X[i];
	X[i] = X[j];
	X[j] = aux;	
}

int max(int *X, int n, int i)
{
    int idx;
    int max_val;

    #pragma omp parallel for reduction(max:max_val) 
    for (idx = i; idx <= n; idx++)
    {
       max_val = max_val >= X[idx] ? max_val : X[idx];
       printf("Swap: %i\n", max_val);
    }

    printf("El elemento maximo es: %i\n", max_val);
    return max_val;
}

int imprimeArreglo(int *X, int n)
{
	printf("Arreglo inicial: \n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d,", X[i]);
	}
	printf("\n");
}

int imprimeResultado(int *X, int n)
{
	for (int i = 1; i <= n; i++)
	{
		printf("%d,", X[i]);
	}
	printf("\n");
}

 int main(int argc, char const *argv[])
 {
	 //Potencia para el tamanio del arreglo
	int k;
	//Semilla para hacer random los elementos del arreglo
	int semilla;
	if (argc < 1)
	{
		printf("Por favor, especifique el numero de hilos\n");
		exit(1);
	} 
	//Escanea potencia como primer argumento
	sscanf(argv[1], "%i", &k);
	//Escanea la semilla como segundo argumento
	//sscanf(argv[2], "%i", &semilla);
	if (k < 1)
	{
		printf("El numero que debes ingresar es positivo\n");
		exit(1);
	}
	//Tamanio del arreglo
	int n = pow(2,k);
	int *X = (int*)malloc((n+1)*sizeof(int));
	generador(X,n);

	imprimeArreglo(X,n);
	
	/*Funcion que permite hacer el intercambio de indices
	 * i el indice
	 * j el segundo indice
	 */
	/*
	void swap(int i, int j) 
	{
		int aux = X[i];
		X[i] = X[j];
		X[j] = aux;
	}*/

	omp_set_num_threads(n);
	int i = 0;

	#pragma omp parallel
	{
		/*//max(X,n,i);
    	int idx;
    	int max_val;

    	//#pragma omp parallel for reduction(max:max_val) 
    		for (idx = i; idx <= n; idx++)
    		{
    		   max_val = max_val >= X[idx] ? max_val : X[idx];
    		   printf("Swap: %i\n", X[idx]);
    		}

    	//return max_val;
    	printf("El elemento maximo es: %i\n", max_val);*/
    	int idHilo = omp_get_thread_num();
    	int ronda = pow(2,0+1);
    	printf("%i, \n", ronda);
    	i = n/ronda;
		for (; i <= n; i++)
		{
			ronda++;
			printf("ronda: %i\n", ronda);
		}

	}
	//Arreglo resultante
	imprimeResultado(X,n);	
 	return 0;
 }
