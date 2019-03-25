#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>
#include <math.h>



/* Funcion que permite la impresion de un arreglo
 * X el arreglo que va recibir
 * n es el tamanio del arreglo
 */
int imprimeArreglo(int *X, int n)
{
	printf("Arreglo no ordenado: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%i,", X[i]);
	}
	printf("\n");
}

/* Funcion que permite la impresion de un arreglo
 * X el arreglo que va recibir
 * n es el tamanio del arreglo
 */
int imprimeResultado(int *X, int n)
{
	printf("Arreglo ordenado: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%i,", X[i]);
	}
	printf("\n");	
}

int main(int argc, char const *argv[])
{
	int potencia;
	int semilla;
	if (argc < 2)
	{
		printf("Por favor, especifique el numero de hilos\n");
		exit(1);		
	}
	//Primer argumento que recibe la terminal, potencia
	sscanf(argv[1], "%i", &potencia);
	sscanf(argv[2], "%i", &semilla);
	//Asignamos el tamanio del arreglo	
	int n = pow(2,potencia) + 1;
	//Arreglo X con su tamanio
	int X[n];
	//Indice i del for
	int i = 0;
	srand(semilla);
	//La cota del numero de elementos aleatorios
	//Tambien ingresa elementos en el arreglo
	for (; i < n; ++i)
	{
		X[i] = rand() % 101;
	}

	/*Funcion que permite hacer el intercambio de indices
	 * i el indice
	 * j el segundo indice
	 */
	void swap(int i, int j) 
	{
		int aux = X[i];
		X[i] = X[j];
		X[j] = aux;
	}

	//Imprimimos el arreglo original
	imprimeArreglo(X,n);
	//Numero de procesadores que se van a utilizar en el arreglo
	omp_set_num_threads(n);
	//Funcion paralela
	#pragma omp parallel
	{
		int i = 0;
		int par = 0;
		int impar = 1;
		do
		{
			if (X[par + 1] < X[par])
			{
				swap(par, par+1);
			}
			par+=2;
			if (X[impar + 1] < X[impar])
			{
				swap(impar, impar+1);
			}
			impar += 2;
			i += 1;
		} while (i < (n/2));
	}//Fin de la funcion paralela
	//Imprimimos el arreglo ordenado
	imprimeResultado(X,n);	
	return 0;
}