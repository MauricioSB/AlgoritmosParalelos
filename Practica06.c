#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>
#include <math.h>
 
int sort(int *X, int n)
{
	#pragma omp parallel 
	{	
		int i = 0;
		int par = 0;
		int impar = 1;
		do
		{
			if (X[par + 1] < X[par])
			{
				swap(X,par, par+1);
			}
			par+=2;
			if (X[impar + 1] < X[impar])
			{
				swap(X,impar, impar+1);
			}
			impar += 2;
			i += 1;
		} while (i < (n/2));
	}
}

void swap(int *X, int i, int j)
{
	int aux = X[i];
	X[i] = X[j];
	X[j] = aux;	
}

int imprimeArreglo(int *X, int n)
{
	printf("Arreglo inicial: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d,", X[i]);
	}
	printf("\n");
}

int imprimeResultado(int *X, int n)
{
	for (int i = 1; i <= n; ++i)
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
	if (argc < 2)
	{
		printf("Por favor, especifique el numero de hilos\n");
		exit(1);
	} 
	//Escanea potencia como primer argumento
	sscanf(argv[1], "%i", &k);
	//Escanea la semilla como segundo argumento
	sscanf(argv[2], "%i", &semilla);
	if (k < 1)
	{
		printf("El numero que debes ingresar es positivo\n");
		exit(1);
	}
	srand(semilla);
	//Tamanio del arreglo
	int n = pow(2,potencia);
	int *X = (int*)malloc((n+1)*sizeof(int));
	for(int i = 1; i <= n; ++i){
	  aux = (rand() % n +1);
	  int aux2 = 0;
	  while(aux2 < i){
	    if(aux != X[aux2])
	      aux2++;
	    else{
	      aux = (rand() % n +1);
	      aux2 = 0;
	    }
	  }
	  X[i] = aux;
	}
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

	#pragma omp parallel
	{

	}
	//Arreglo resultante
	imprimeResultado(X,n);	
 	return 0;
 }