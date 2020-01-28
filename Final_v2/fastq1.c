#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fastq.h"

char** extract_file(char* file_dir,char** sequence)
{
    int n , read , i , m , nbre_read ;
    char c , **copie ;
    FILE *fichier;
    //nombre de reads
    n = nbre_lignes(file_dir);
    m=n*2;
    //taille d'un read
    fichier = fopen(file_dir,"r");
    c = getc(fichier);
    while (c!= '\n')
        c = getc(fichier);
    read = 0 ;
    c = getc(fichier);
    while (c!= '\n')
    {
         c = getc(fichier);
         read++;
    }

    copie = malloc(m*sizeof(char*));
    for (int i=0; i < m ; i++)
        copie[i] = malloc(read*sizeof(char));

    i=0;
    rewind(fichier);
    while (fgets(copie[i],101,fichier)!= NULL)
    {
        i++;
    }
    nbre_read = n/4 ;
    strcpy(sequence[0],copie [1]);
    for (int i=0; i < nbre_read; i++)
    {
        strcpy(sequence[i],copie[1+6*i]);
    }
    fclose(fichier);
    free(copie);
    return sequence;
}

int nbre_lignes(char* file_dir)
{
	FILE *fichier;
	int count = 0;
	char c;

    fichier = fopen(file_dir ,"r");

	if (fichier == NULL)
	{
		printf("Could not open file");
		return 0;
	}

	for (c = getc(fichier); c != EOF; c = getc(fichier))
		if (c == '\n')
			count = count + 1;

	fclose(fichier);

	return count;
}


int nbre_read(char* file_dir)
{
    int n;
    n = nbre_lignes(file_dir);
    return n/4;
}

int taille_read(char* file_dir)
{
    FILE* fichier;
    int c,read;
    fichier = fopen(file_dir,"r");
    c = getc(fichier);
    while (c!= '\n')
        c = getc(fichier);
    read = 0 ;
    c = getc(fichier);
    while (c!= '\n')
    {
         c = getc(fichier);
         read++;
    }
    return read;
}


