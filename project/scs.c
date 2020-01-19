#include "permute.c"
#include "overlap.c"
/* Shortest common superstring w/ brute force*/
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