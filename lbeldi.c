#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_overlap(char *a,char *b){
	int na,nb;
	int j=0;
	int i=0;
	int boo=1; //boolean
	na=strlen(a);
	nb=strlen(b);
	char a1[10] ;
	char b1[10] ;
	strcpy(a1,a);
	strcpy(b1,b);

	while(i<na){
		if(b1[j]==a1[i]){
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
}//number_of_overlap works perfectly

void overlap(char str[100][100],int n,char sq[100]){
	int len = 5;
	int noo;
	char final[100];
	strcpy(final,str[0]);
	/*char overlappedString[100] = overlap(str,n);*/
	for(int i=0;i<n-1;i++){
		noo = number_of_overlap(str[i],str[i+1]);
		strcat(final,&str[i+1][noo]);
	}
	strcpy(sq,final);
}
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
void scs(char **str,int n){
	int shortestLen=100;
	char shortestS[100];
	char sq[100];
	char T[100][100][100];
	int k = 0;
    int *p = &k;
	permute(str, 0, n - 1,n,T,p);
	for(int i=0;i<6;i++){
		overlap(T[i],n,sq);
		printf("%s,",sq);
		if (strlen(sq)<shortestLen){	
			shortestLen=strlen(sq);
			strcpy(shortestS,sq);
		}
	}
	printf("\n %s",shortestS);
}
int main(){
	char *ss[]={"ACGGATGATC","GATCAAGT","AAGTCGGA"};
	int len_ss = sizeof(ss)/sizeof(ss[0]); 
	char sss[100];
	printf("Hello \n");
	scs(ss,len_ss);
	printf("\n");
	//printf("%s",sq);
	system("pause");
	return 0;
}
