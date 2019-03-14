#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>

//Definimos los intervalos de la funcion a calcular
//Intervalo minimo
#define MINIMO 3
//Intervalo maximo
#define MAXIMO 17
//Maximo numero de hilos
#define MAX_HILOS 1000

double funcion(double x);

//La funcion que vamos a utilizar para las sumas de riemann
double funcion(double x) 
{
	return (100 - pow((x - 10),4) + (50 * (pow((10 - x),2))) - (8 * x));
}

int main(int argc, char const *argv[])
{
	
	if (argc < 2)
	{
		printf("Por favor, especifique el numero de hilos\n");
		exit(1);		
	} 
	//p es el numero de procesadores 
	int p = 0;
	sscanf(argv[1], "%i", &p);
	if (p < 1 || p > MAX_HILOS) 
	{
		printf("Numero de hilos no valido (%i)\n", p);
		exit(1);
	}

	//resultado
	double resul;
	//suma de riemann
	double suma;
	double id_hilo;
	//Incognita x
	double x = MINIMO;
	//Incremento
	double incremento = ((double)MAXIMO-(double)MINIMO)/(double)(p*5);
	omp_set_num_threads(p*5);
	//Funcion paralela
	#pragma omp parallel private(suma,id_hilo)
	{
		id_hilo = omp_get_thread_num();
		//variable auxiliar
		double aux = (p*5);
		//indice i
		int i;
		for (i = id_hilo; i < aux; i+=aux)
		{
			suma += (incremento * (funcion(x) + funcion(x+incremento)))/2.0;
			x += incremento;
		}
		resul += suma;
	}//Termina la funcion paralela

	//Imprime el resultado
	printf("El resultado es %f\n", resul);
	return 0;
}//Fin de la Practica03