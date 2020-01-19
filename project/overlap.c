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