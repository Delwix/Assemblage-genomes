#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>



void adj_matrix(int *p, char** sequence, int n, int read);
int num_of_overlap(char *a,char *b);
int nbre_lignes(char* file_dir);
char** extract_file(char* file_dir);
int nbre_read(char* file_dir);
int taille_read(char* file_dir);
void concatenate(char *r1, char *r2, int best_olen);

/*int main(){
	char reads[4][10]={"AAB","BAA","ABA","BAB"};
	int mat[20];
	adj_matrix(mat,reads,4);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("%s,%s,%d \n",reads[i],reads[j],mat[4*i+j]);
		}
	}
	
}*/
void  main()
{
    char** sequence;
    int n,read ;
    int *p;
    n = nbre_read("C:\\Users\\abdou\\Desktop\\Project\\genome.fq");
    read = taille_read("C:\\Users\\abdou\\Desktop\\Project\\genome.fq");
    sequence = malloc(n*sizeof(char*));
    for(int i=0; i < n; i++)
        sequence[i] = malloc(read*sizeof(char));
    sequence = extract_file("C:\\Users\\abdou\\Desktop\\Project\\genome.fq");
    /*for(int i=0; i < n; i++)
        printf("%s \n", sequence[i]);*/
    adj_matrix(p,sequence,n,read);
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

void adj_matrix(int *p, char** sequence, int n, int read){
	int n2 = n*n;
	int olen,best_olen = 0;
	char *r1,*r2;
	r1,r2 = (char *)malloc(read * sizeof(char));
	p = calloc(n2, sizeof(int) );
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			//printf("%d,",num_of_overlap(sequence[i],sequence[j]));
			*(p+n*i+j) = num_of_overlap(sequence[i],sequence[j]);
			olen = num_of_overlap(sequence[i],sequence[j]);
			if(olen > best_olen && i!=j){
				r1=sequence[i];
				r2=sequence[j];
				best_olen = olen;
			}
		}
	}
	concatenate(r1,r2,best_olen);
}

int num_of_overlap(char *a,char *b){
	int na,nb;
	int j=0;
	int i=0;
	int boo=1; //boolean
	na=strlen(a);
	nb=strlen(b);
	//char a1[100] ;char b1[100] ;strcpy(a1,a);strcpy(b1,b);

	while(i<na){
		if(b[j]==a[i]){
			j=j+1;
			i=i+1;
			boo = 0;
		}
		else if (boo==0){
			j=0;
			boo=1;
		}
		else {	
			j=0;
			i=i+1;
			boo = 1;
		}
	}
	//printf("%s,%s,%d \n",a,b,j);
	return j;
}

void concatenate(char *r1, char *r2, int best_olen)
{
	int len1 = strlen(r1);
	int len2 = strlen(r2);
	char *temp = malloc(len1 + 1);
	strcpy(temp,r1);
	for (int i=0; i< (len2 - best_olen); i++){
		r1[len1 + i] = r2[best_olen + i];
	}
	r1[len1 + best_olen] = '\0';
	strcpy(r2,"xx");
	//printf("%d \n %s \n %s \n %s ",best_olen,r1,r2);
	//free(r1);
	//free(r2);

}
