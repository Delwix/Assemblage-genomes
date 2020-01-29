#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fastq.h"
#include "Greedy_Algo.h"

char* assemblage()
{
	clock_t tic = clock();
    char** sequence;
    char* shortest_common_superstring;
    int n,read;
    int max_size;
    int recherche;
    n = nbre_read("C:\\Users\\hp\\Desktop\\genome\\genome.fq");
    read = taille_read("C:\\Users\\hp\\Desktop\\genome\\genome.fq");
    max_size = read * n;
    sequence = malloc(n*sizeof(char*));
    for(int i=0; i < n; i++)
        sequence[i] = malloc(max_size*sizeof(char));
    shortest_common_superstring = malloc(max_size * sizeof(char));
    strcpy(shortest_common_superstring,"");
    extract_file("C:\\Users\\hp\\Desktop\\genome\\genome.fq",sequence);
    greedy(sequence,n,read,max_size);
    //for(int i=0; i < n; i++)
    //    printf("%s,", sequence[i]);
    printf("\n \n");
    clock_t toc = clock();
    printf(" \nElapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return shortest_common_superstring;
}

char* greedy(char** sequence, int n, int read, int max_size)
{
    int olen,best_olen = 0;
    //char *no = "no";
    char *temp,*temp2;
    int* p;
    int c,d;
    int check = 0;
    int cnt = 0;
    best_olen = 1;
    p = graph(sequence,n);
    temp = (char *)malloc(max_size * sizeof(char));
    temp2 = (char *)malloc(max_size * sizeof(char));
    while(cnt < n){
        best_olen = 0;
        check = 0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j)
                {
                    olen = *(p + n * i + j);
                    if(olen >= best_olen)
                    {
                        best_olen = olen;
                        c = i;
                        d = j;
                        check = 1;
                    }
                }
            }
        }
        if (check == 1){
            concatenate(sequence[c],sequence[d],best_olen,max_size,temp);
            strcpy(sequence[c],temp);
            remove_edge(p,c,d,n);
        }
        cnt += 1;
        printf("cnt = %d, BO = %d \n",cnt,best_olen);
        
    }
    printf("le genome original est = %s",sequence[c]);
    return sequence[c];
}
int num_of_overlap(char *a,char *b)
{
    int na,nb;
    int j=0;
    int i=0;
    int boo=1; //boolean
    na=strlen(a);
    nb=strlen(b);

    while(i<na){
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

char* concatenate(char *r1, char *r2, int best_olen, int max_size, char *temp)
{
    int len1 = strlen(r1);
    int len2 = strlen(r2);
    strcpy(temp,r1);
    for (int i=0; i< (len2 - best_olen); i++){
        temp[len1 + i] = r2[best_olen + i];
    }
    temp[len1 + len2 - best_olen] = '\0';
}

int* graph( char** sequence, int n)
{
    int n2 = n*n;
    int *p;
    //int *adj_mat = (int *)malloc(n2 * sizeof(int)); 
    p = calloc(n2, sizeof(int) );
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                *(p+n*i+j) = -1;
            }
            //printf("%d,",num_of_overlap(sequence[i],sequence[j]));
            else
            {
                *(p+n*i+j) = num_of_overlap(sequence[i],sequence[j]);
                //printf("%d, ",*(p+n*i+j)); //TO PRINT ADJACENCY MATRIX
            }
        }
    }
    printf("Construction du graphe terminee \n");
    return p;
}

void remove_edge(int *p, int i1,int j1, int n)
{
    for (int j = 0; j < n; j++)
    {
        *(p + n*i1 + j ) = *(p + n*j1 + j);
    }
    for (int i = 0; i < n; i++)
    {
        *(p + n*i + j1) = -1;
        *(p + n*j1 + i) = -1;
    }
    
}
