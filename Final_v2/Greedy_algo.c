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
    char** finalscs;
    char* scs1;
    int n,read;
    int recherche;
    n = nbre_read("C:\\Users\\Msi\\Desktop\\genome.fq");
    read = taille_read("C:\\Users\\Msi\\Desktop\\genome.fq");
    scs1 = malloc(n*read*sizeof(char));
    sequence = malloc(n*sizeof(char*));
    for(int i=0; i < n; i++)
        sequence[i] = malloc(read*sizeof(char));
    finalscs = malloc(n*sizeof(char*));
    for(int i=0; i < n; i++)
        finalscs[i] = malloc(read*sizeof(char));
    extract_file("C:\\Users\\Msi\\Desktop\\genome.fq",sequence);
    //adj_matrix(sequence,n,read,max_size);
    //for(int i=0; i < n; i++)
    //    printf("%s,", sequence[i]);

    strcpy(scs1,chemin(sequence, n, read, finalscs));
    //join(sequence, shortest_common_superstring,n);
    printf("\n \n");
    //printf("shortest common superstring = %s",shortest_common_superstring);
    //printf("final = %s \n \n %s",sequence[0],sequence[1]);
    //rechercherFromReads(sequence,read,n);
    /*for (int i = 0; i < n; ++i)
    {
        printf("%s \n",finalscs[i]);
    }*/
    printf("\n");
    clock_t toc = clock();
    printf("le genome assemblé est: %s", scs1);
    printf(" \ntemps d'éxecution: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return scs1;
}


char* chemin(char** sequence, int n, int read, char** finalscs)
{
    int max,i1,j1,cnt;
    int *p;
    int c=0;
    char* scs;
    char* temp;
    int *indices = malloc(2*(n+1)*sizeof(int));
    scs = malloc(n*read*sizeof(char));
    temp = malloc(n*read*sizeof(char));
    strcpy(scs,"");
    p = graph(sequence,n);
    cnt = 0;
    while(cnt<n){
        max = 0;
        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (( *(p + n * i + j) >= 0 ) && (*( p + n * i + j) >= max))
                {
                    max = *( p + n * i + j);
                    i1 = i;
                    j1 = j;
                }
            }
        }
        remove_edge(p,i1,j1,n);
        printf("arc choisi %d-->%d \n",i1,j1);
        indices[2*cnt] = i1;
        indices[2*cnt+1] = j1;
        //printf("cnt = %d \n",cnt);
        cnt++;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d-->%d,",indices[2*i],indices[2*i+1]);
    }
    printf("\n DONE");
    strcpy(finalscs[0],sequence[indices[0]]);
    strcpy(finalscs[1],sequence[indices[1]]);
    for (int j = 1; j < n-1; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if(indices[2*i]==indices[2*c+1])
            {
                c=i;
                break;
            }
        }
        strcpy(finalscs[j+1],sequence[indices[2*c+1]]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("seq=%s \n",finalscs[i+1]);
    }
    strcat(scs,finalscs[0]);
    for (int i = 0; i < n-1; i++)
    {
        concatenate(scs,finalscs[i+1],temp);
        strcpy(scs,temp);
    }
    return scs;
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

void concatenate(char *r1, char *r2,char* temp)
{
    int len1 = strlen(r1);
    int len2 = strlen(r2);
    int olen = num_of_overlap(r1,r2);
    strcpy(temp,r1);
    for (int i=0; i< (len2 - olen); i++){
        temp[len1 + i] = r2[olen + i];
    }
    temp[len1 + len2 - olen] = '\0';
}


int* graph( char** sequence, int n){
    int n2 = n*n;
    int *p;
    //int *adj_mat = (int *)malloc(n2 * sizeof(int));
    p = calloc(n2, sizeof(int) );
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j){
                *(p+n*i+j) = -1;
            }
            //printf("%d,",num_of_overlap(sequence[i],sequence[j]));
            else{
                *(p+n*i+j) = num_of_overlap(sequence[i],sequence[j]);
                //printf("%d, ",*(p+n*i+j)); //TO PRINT ADJACENCY MATRIX
            }
        }
    }
    printf("building graph done \n");
    return p;
}

void remove_edge(int *p, int i1,int j1, int n)
{
    *(p + n*i1 + j1) = -1;
    *(p + n*j1 + i1) = -1;
    for (int i = 0; i < n; i++)
    {
        *(p + n*i + j1) = -1;
    }
    for (int j = 0; j < n; j++)
    {
        *(p + n*i1 + j ) = -1;
    }
}

