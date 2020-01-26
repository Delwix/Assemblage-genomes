#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nbre_lignes(char* file_dir);
void extract_file(char* file_dir, char** sequence);
int nbre_read(char* file_dir);
int taille_read(char* file_dir);
char* concatenate(char *r1, char *r2, int best_olen, int max_size,char* temp);
void adj_matrix(char** sequence, int n, int read, int max_size);
int num_of_overlap(char *a,char *b);
void join(char **sequence,char* shortest_common_superstring, int n);

void main()
{
    char** sequence;
    char* shortest_common_superstring;
    int n,read ;
    int max_size;
    n = nbre_read("C:\\Users\\hp\\Desktop\\genome\\genome.fq");
    read = taille_read("C:\\Users\\hp\\Desktop\\genome\\genome.fq");
    max_size = read * n;
    sequence = malloc(n*sizeof(char*));
    for(int i=0; i < n; i++)
        sequence[i] = malloc(max_size*sizeof(char));
    shortest_common_superstring = malloc(max_size * sizeof(char));
    strcpy(shortest_common_superstring,"");
    extract_file("C:\\Users\\hp\\Desktop\\genome\\genome.fq",sequence);
    adj_matrix(sequence,n,read,max_size);
    for(int i=0; i < n; i++)
        printf("%s,", sequence[i]);
    join(sequence, shortest_common_superstring,n);
    printf("\n \n");
    printf("shortest common superstring = %s",shortest_common_superstring);
    //free_mem(sequence,n);
    printf("\n");
    system("pause");

}

void extract_file(char* file_dir,char** sequence)
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
    char *no = "no";
    char *r1,*r2,*temp;
    int c,d;
    int check = 0;
    int cnt = 0;
    best_olen = 1;
    temp = (char *)malloc(max_size * sizeof(char));
    while(best_olen > 0){
        best_olen = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if (strcmp(sequence[i],no) !=0 && strcmp(sequence[j],no) !=0){
                    olen = num_of_overlap(sequence[i],sequence[j]);
                    if((olen >= best_olen) && (i!=j)){
                        best_olen = olen;
                        c = i;
                        d = j;
                        check = 1;
                    }
                }
            }
        }
        if (check == 1){
            printf("r1 = %s \n r2 = %s \n",sequence[c],sequence[d]);
            concatenate(sequence[c],sequence[d],best_olen,max_size,temp);
            strcpy(sequence[c],temp);
            strcpy(sequence[d],no);
            printf("R = %s \n best_olen %d i=%d, j=%d  \n",sequence[c],best_olen,c,d);
        }
        cnt += 1;
        printf("cnt = %d \n",cnt);
        if(best_olen == 0){
            free(temp);
            break;
        }
    }
}

int num_of_overlap(char *a,char *b){
    int na,nb;
    int j=0;
    int i=0;
    int boo=1; //boolean
    na=strlen(a);
    nb=strlen(b);

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
    return j;
}

char* concatenate(char *r1, char *r2, int best_olen, int max_size, char *temp)
{
    int len1 = strlen(r1);
    int len2 = strlen(r2);
    strcpy(temp,r1);
    for (int i=0; i< (len2 - best_olen); i++){
        temp[len1 + i] = r2[best_olen + i];
    }
    temp[len1 + len2 - best_olen] = '\0';
    //printf("%d \n %s \n %s \n %s ",best_olen,r1,r2);
    //free(r1);
    //printf("%s",temp);
}


void join(char **sequence,char* shortest_common_superstring, int n)
{   
    char *no = "no";
    for(int i=0; i<n; i++){
        if(strcmp(sequence[i],no) != 0)
            strcat(shortest_common_superstring,sequence[i]);
    }
}