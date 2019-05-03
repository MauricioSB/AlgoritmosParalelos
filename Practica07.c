#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <omp.h>
#include <math.h>
#include <regex.h>

void witness()
{

}

void fuerzaBruta(char* patron)
{

}

void duelo(char* patron)
{

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
