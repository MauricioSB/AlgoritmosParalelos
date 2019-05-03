#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>
#include <math.h>
#include <regex.h>

/*NO esta terminado*/
//Notaciones: k: witness dado, i.e., witness(j-1+1)
//m: Largo del patron (length)
//p(k): Posicion del patron
//s es el candidato de B
//B: es el bloque
void witness(char* patron)
{
	int k;
	int s;
	char *witnes = (char*)malloc((n+1)*sizeof(char));
	#pragma omp parallel for
	for (int i = 1; i <= (sizeof(patron))/2; i++)
	{
		witnes[i] = 0;
	}
	for (int i = 1; i <= (sizeof(patron) - 1); ++i)
	{
		//Primer candidato en el i-bloque
		int j = 2;
		fuerzaBruta(patron,witnes[j]);
		if (witnes[j] == 0)
		 {
		 	exit(1);
		 }
		#pragma omp parallel for
		for (i = 2; i <= count; i++)
		 {
		 	duelo(k,s, patron);
		 } 

	}
}

/*Ni idea si este funciona*/
void fuerzaBruta(char* patron, int j)
{
	for (int i = 1; i <= sizeof(patron); i++)
	{
		int p = sizeof(patron) - (i + 1);
		witness(i);
	}
}

/*Ignorar este*/
void duelo(int k, int s, char* patron)
{
	if (k <= (sizeof(patron) - (j+1)))
	{
		while(patron[k] != patron[k+j-1])
		{
			k = witness(j);
		}


	}	
}

int main(int argc, char** argv)
{

	/*Primero paso, recibir de entrada un archivo .txt*/
	//Notas: r = read
	// w = write
	//b = binary
	//Alfabeto va a ser el conjunto de caracteres o numeros
	//Patron lo que s epuede formar a partir del alfabeto dado en el archivo
	regex_t regex;
	int try;
	char msgbuf[100];
	FILE *flujo = fopen("test.txt", "r");
	if (flujo == NULL)
	{
		perror("Error en la apertura del archivo");
		return 1;
	}
	//El alfabeto del archivo
	char alfabeto[1024];
	//Patron que se puede formar del alfabeto
	char patron[1024];
	while(fgets(alfabeto, 1024, (FILE*) flujo) && fgets(patron, 1024, (FILE*) flujo))
	{
		//int n = strlen(alfabeto)
		//caracter = fgetc(flujo);
		//fscanf(flujo,"%c%s", &alfabeto, &patron);
		printf("Alfabeto del archivo: %s\n", alfabeto);
		printf("Patron: %s\n", patron);
		try = regcomp(&regex, alfabeto, 0);
		if (try)
		 {
		 	fprintf(stderr, "No se pudo compilar\n");
		 	exit(1);
		 }
		 try = regexec(&regex, patron,0,NULL,0);
		 if (!try)
		  {
		  	printf("Pertenece al alfabeto: %s\n", alfabeto);
		  	puts(patron);
		  } 
		  else if (try == REG_NOMATCH)
		  {
		  	puts("No match");
		  	printf("No pertenece al alfabeto\n");
		  	exit(1);
		  } else 
		  {
		  	regerror(try,&regex,msgbuf,sizeof(msgbuf));
		  	fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		  	exit(1);
		  }
		  regfree(&regex);

	}
	printf("\n");
	fclose(flujo);
	printf("Se ha leido el archivo correctamente\n");
	return 0;
}
