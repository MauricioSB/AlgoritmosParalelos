#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>
#include <math.h>


#define MAX_HILOS 100

/* Funcion recursiva prefix sum que permite realizar las operaciones
 * de la suma prefija.
 * X el arreglo que definimos en el main
 * n es el tamanio del arreglo
 */
void prefix_sum(int *X, int n)
{
	if (n > 1)
	{
		//malloc devuelve un apuntador inespecifico.
		//sizeof se utiliza para obtener el tamanio de bytes
		//de Y[]
		int *Y = (int*) malloc((n/2+1)*sizeof(int));
		//Indice i
		int i = 0;
		Y[n/2] = 0;
		//Permite la creacion de hilos & especificamos la estructura paralela
		#pragma omp parallel for 
		for (i = 0; i < n/2; ++i)
		{
			Y[i] = X[2*i] + X[2*i + 1];
		}
		//Hacemos la llamada recursiva
		#pragma omp task
		{
			prefix_sum(Y, n/2);
		}
		//Con esto especificamos una "espera" a la finalizacion
		//de las operaciones que se estan realizando
		#pragma omp taskwait
		//Volvemos a crear hilos & especificamos la estructura para los
		//casos par e impar (odd & even)
		#pragma omp parallel for
			for (i = 0; i < n/2; ++i)
			{
				X[i*2 + 1] = Y[i];
				X[i*2 + 2] = Y[i] + X[i*2 + 2];
			}
		
	}
}

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

/* Funcion que permite calcular los exponentes para nuestros
 * arreglos.
 * potencia es el exponente
 */
int potenciaCuadrada(int potencia) 
{
	int base = 2;
	int sol = 1;
	for (int i = 0; i <= potencia; ++i)
	{
		sol *= base;
	} 
}

int main(int argc, char const *argv[])
{
	 //Potencia para el tamanio del arreglo
	int potencia;
	//Semilla para hacer random los elementos del arreglo
	int semilla;
	if (argc < 2)
	{
		printf("Por favor, especifique el numero de hilos\n");
		exit(1);
	} 
	//Escanea potencia como primer argumento
	sscanf(argv[1], "%i", &potencia);
	//Escanea la semilla como segundo argumento
	sscanf(argv[2], "%i", &semilla);
	srand(semilla);
	//Le asignamos el tamanio del arreglo con 2^k
	int n = pow(2,potencia);
	if (potencia < 1 || potencia > MAX_HILOS) 
	{
		printf("Numero de hilos no valido (%i)\n", potencia);
		exit(1);
	}	
	int *X = (int*)malloc((n+1)*sizeof(int));
	int i = 0;
	//La cota del numero de elementos aleatorios
	//Tambien ingresa elementos en el arreglo
	for (; i < n; ++i)
	{
		X[i] = (int)rand() % 100;
	}
	X[n+1] = 0;
	//Imprimos nuestro arreglo inicial
	printf("Arreglo que se le va hacer prefix sum: \n");
	imprimeArreglo(X, n);
	//Funcion paralela
	#pragma omp parallel
	{
		//Llamada recursiva
		#pragma omp single
		{
			prefix_sum(X, n);
		}
	}//Termina la operacion paralela
	//Imprimimos el resulado
	//free(X);
	imprimeResultado(X,n);
	return 0;
}//Fin de la Practica04
