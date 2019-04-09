#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#define CHAR_BITS 2



int imprimeResultado(int *X, int n)
{
	for (int i = 1; i <= n; ++i)
	{
		printf("%d,", X[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
if (argc < 3){     /*Verificacion de argumentos */
		printf("por favor especifique la semilla");
		exit(1);
	}else {   /*Aprobacion de argumentos*/
  int semilla;
  int vertice;  //Auxiliar potencia
  sscanf(argv[1],"%i",&vertice);
  sscanf(argv[2],"%i",&semilla);
	if (vertice < 0 || semilla < 0){
		printf("Ingrese un entero positivo por favor \n");
		exit(1);
	}

	int arreglo[vertice];
	  int aux;
	  srand(semilla);
	  for(int i = 1; i <= vertice; ++i){
	    aux = (rand() % vertice +1);
	    int aux2 = 0;
	    while(aux2 < i){
	      if(aux != arreglo[aux2])
	        aux2++;
	      else{
	        aux = (rand() % vertice +1);
	        aux2 = 0;
	      }
	    }
	    arreglo[i] = aux;
	  }




  printf("Arreglo original\n");

  for (int j = 1; j <= vertice; j++){
    int aux = arreglo[j];
    printf("%i,", aux);
  }
  printf("\n");

	int binarioI(int num)
  {
      int sup = CHAR_BITS*sizeof(int);
      int i = 0;
      while(sup >= i)
      {
          if(num & (((long int)1) << sup))
              return 1;
          else
              return 0;
          sup--;
      }
      printf("\n");
  	}

		unsigned binario(unsigned num)
		{
			if(num == 0) return 0;
			if(num == 1) return 1;
			return (num%2) + 10 * binario(num/2);
		}

	int x;
  for (int j = 1; j <= vertice; ++j){
		x = binario(arreglo[j]);
		arreglo[j] = x;
	}
int ci[100];
	imprimeResultado(arreglo, vertice);
	omp_set_num_threads(vertice);
	#pragma omp parallel
	{
		int k;
		int idHilo = omp_get_thread_num();

		for (int i = 1; i <= vertice; ++i)
		{
				if (arreglo[idHilo] != arreglo[idHilo+1])
				{
					++k;
				}
				ci[i] = (2*k) + arreglo[idHilo];

		}
	}
		imprimeResultado(ci,vertice);

}
	return 0;
}
