#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>



void adj_matrix(char** sequence, int n, int read, int max_size);
int num_of_overlap(char *a,char *b);
int nbre_lignes(char* file_dir);
char** extract_file(char* file_dir);
int nbre_read(char* file_dir);
int taille_read(char* file_dir);
char* concatenate(char *r1, char *r2, int best_olen, int max_size);


void  main()
{
    char** sequence;
    int n,read ;
    int max_size;
    int i = 0;
    n = nbre_read("C:\\Users\\abdou\\Desktop\\Project\\genome.fq");
    read = taille_read("C:\\Users\\abdou\\Desktop\\Project\\genome.fq");
    max_size = read * n;
    sequence = malloc(n*sizeof(char*));
    for(int i=0; i < n; i++)
        sequence[i] = malloc(max_size*sizeof(char));
    sequence = extract_file("C:\\Users\\abdou\\Desktop\\Project\\genome.fq");
    /*for(int i=0; i < n; i++)
        printf("%s \n", sequence[i]);*/
    adj_matrix(sequence,n,read,max_size);
    system("pause");

}

char** extract_file(char* file_dir)
{
    int n , read , i , m , nbre_read ;
    char c , **sequence, **copie ;
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
    sequence = malloc(nbre_read*sizeof(char*));
    for(int i=0; i < nbre_read; i++)
        sequence[i] = malloc(read*sizeof(char));
    sequence[0] = copie [1];
    for (int i=0; i < nbre_read; i++)
    {
        sequence[i] = copie[1+6*i];
    }
    fclose(fichier);
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

void adj_matrix(char** sequence, int n, int read, int max_size){
	int n2 = n*n;
	int olen,best_olen = 0;
	char *r1,*r2,*temp;
	int c,d;
	int cnt = 0;
	r1,r2 = (char *)malloc(max_size * sizeof(char));
	best_olen = 1;
	printf("%d \n",best_olen);
	while(cnt <= n)
	{
		best_olen = 0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if (strcmp(sequence[i],"y") != 0 && strcmp(sequence[i],"y") != 0)
				{
					olen = num_of_overlap(sequence[i],sequence[j]);
					if(olen >= best_olen && i!=j)
					{
						r1=sequence[i];
						r2=sequence[j];
						best_olen = olen;
						c = i;
						d = j;

					}
				}
			}
		}
		strcpy(sequence[c],concatenate(r1,r2,best_olen,max_size));
		free(temp);
		strcpy(sequence[d],"y");
		printf("%s \n best_olen %d i=%d, j=%d \n",sequence[c],best_olen,c,d);
		cnt += 1;
		printf("cnt = %d \n",cnt);
	}
	
}

int num_of_overlap(char *a,char *b){
	int na,nb;
	int j=0;
	int i=0;
	int boo=1; //boolean
	na=strlen(a);
	nb=strlen(b);

	while(i<na)
	{
		if(b[j]==a[i])
		{
			j=j+1;
			i=i+1;
			boo = 0;
		}
		else if (boo==0)
		{
			j=0;
			boo=1;
		}
		else 
		{	
			j=0;
			i=i+1;
			boo = 1;
		}
	}
	return j;
}

char* concatenate(char *r1, char *r2, int best_olen, int max_size)
{
	int len1 = strlen(r1);
	int len2 = strlen(r2);
	char *temp;
	temp = (char *)malloc(max_size * sizeof(char));
	strcpy(temp,r1);
	for (int i=0; i< (len2 - best_olen); i++){
		temp[len1 + i] = r2[best_olen + i];
	}
	temp[len1 + best_olen] = '\0';
	return temp;
}