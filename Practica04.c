#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>


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
	} else if() {
	 	sscanf(argv[1], "%i", &potencia);
	 	sscanf(argv[1], "%i", &semilla);
		if (potencia < 1)
		{
			printf("Ingresa un numero positivo\n");
		}
		int id_hilo;
		//Tamanio del arreglo
	 	int n;
	 	n = pow(2,potencia) + 1;
	 	//Arreglo X = {x1,...,xn}
	 	int arrayX[n];
	 	//Ingresa los elementos aleatorios que se ingreso en la semilla
	 	for (int i = 0; i < n; i++)
	 	{
	 		arreglo[i] = rand() % semilla;
	 	}
	 	//Imprime el arreglo original con sus elementos aleatorios
	 	printf("Arreglo X: \n");
	 	for (int i = 0; i < n; i++)
	 	{
	 		printf("%i \n", arrayX[i]);
	 	}
	 	//Numero de hilos que se van a utilizar
	 	omp_set_num_threads(id_hilo);
	 	//Seccion paralela
	 	#pragma omp parallel private(n, id_hilo)
	 	{
	 		id_hilo = omp_get_thread_num();
	 		int arrayY[];
	 		if (n == 2)
	 		{
	 			arrayX[1] += arrayX[0];
	 		} else
	 		{
	 			for (int i = 2; i < n; i++)
	 			{
	 				if ((id_hilo % i) == (i - 1))
	 				{
	 					arrayX[id_hilo] += arrayX[id_hilo - (n/2)];
	 				}
	 			}
	 			for (i = i/2; i > 1; i/=2)
	 			{
	 				if ((id_hilo % 2) == ((i/2) - 1))
	 				{
	 					if (!(id_hilo < ((i/2) - 1)))
	 					{
	 						arrayX[id_hilo] += arrayX[id_hilo - i/20];
	 					}
	 				}
	 			}
	 		}
	 	}
	}


	return 0;
}//Fin de la Practica04