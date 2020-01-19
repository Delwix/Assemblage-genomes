#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
 

/* Function to swap values at two pointers */
void swap(char** x, char** y) 
{ 
    char *temp= *x; 
    *x = *y; 
    *y = temp; 
}
/* Function to print the permutations of an array using Heap's algorithm */
void permute(char **a, int l, int r,int n,char T[100][100][100],int *p) 
{  
    if(l == r){
        for(int i=0;i<n;i++){
            //printf("%s",a[i]);
            strcpy(T[*p][i],a[i]);
            //printf("%s,",T[*p][i]);
        }
        //printf("\n");
        *p += 1;
    }
    else { 
        for (int i = l; i <= r; i++) { 
            swap(&a[l], &a[i]); 
            permute(a, l + 1, r,n,T,p); 
            swap(&a[l], &a[i]);
        } 
    }
    //printf("%d",*p); 
} 

/* Driver program to test above functions */
/*int main() 
{    
    int k = 0;
    int *p = &k;
    char T[100][100][100];
    char *str[]={"ACGGATGATC","GATCAAGT","TTCACGGA"}; 
    int n = sizeof(str)/sizeof(str[0]); 
    permute(str, 0, n - 1,n,T,p);
    for(int i=0;i<6;i++){
        for(int j=0;j<3;j++)
            printf("%s ,",T[i][j]);
        printf("\n");
    }
    system("pause");
    return 0; 
} */