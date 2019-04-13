#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>
#include <math.h>
 
/* Permite verficar si un numero se esta repitiendo
 * X es el arreglo
 * n es el tamanio del arreglo
 * num es el numero aleatorio generado
 */
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

/*Funcion que permite generar los numeros aleatorios
 * X es el arreglo que va a recibir
 * n es el tamanio del arreglo
 */
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

/* Funcion que permite la impresion de un arreglo
 * X el arreglo que va recibir
 * n es el tamanio del arreglo
 */
int imprimeArreglo(int *X, int n)
{
	printf("Arreglo inicial: \n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d,", X[i]);
	}
	printf("\n");
}

/* Funcion que permite la impresion de un arreglo
 * X el arreglo que va recibir
 * n es el tamanio del arreglo
 */
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
	sscanf(argv[1], "%i", &k);
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
	omp_set_num_threads(n/2);
	int posI;
	int posJ;
	#pragma omp parallel
	{

		int ronda = 1;
		int idHilo = omp_get_thread_num();
		while(ronda <= k)
		{
			//printf("Ronda: %i\n", ronda);
			for (int i = 1; i <= n; i++)
			{
				int iteraciones = n/pow(2,ronda);
				posI = (pow(2,ronda)*i)-(pow(2,ronda-1));
				posJ = (pow(2,ronda)*i);
				for (int j = 1; j <= iteraciones; j++)
				{
					if (X[posI] > X[posJ])
					{
						int aux = X[posI];
						X[posI] = X[posJ];
						X[posJ] = aux;
						//printf("Swap: %i\n", aux);						
					}
				}
			}
			ronda++;
		}	

	}
	//Arreglo resultante
	printf("Resultado: \n");
	imprimeResultado(X,n);	
 	return 0;
 }
