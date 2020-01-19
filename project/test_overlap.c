#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_overlap(char **a,char **b){
	int na,nb;
	int j=0;
	int i=0;
	int boo=1; //boolean
	na=strlen(*a);
	nb=strlen(*b);
	char a1[10] ;
	char b1[10] ;
	strcpy(a1,*a);
	strcpy(b1,*b);
	//for(int j=0;j<na;j++)
	//	printf("%c",a1[j]);
	while(i<na){
		//printf("a(%d)=%c,b(%d)=%c \n",i,a1[i],j,b1[j]);
		if(b1[j]==a1[i]){
			j=j+1;
			i=i+1;
			boo = 0;
		}
		else if (boo==0){
			j=0;
			//printf("x");
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

/*char overlap(char** s,int n){
	for(int i=1;i<n;i++){
		int noo = number_of_overlap(&s[0],&s[i]);
		for(int j=0;j<n;j++){		//fusionner deux strings
			s[0][n+j]=s[i+1][noo+j];
		}
	}
	return *s[0];
}
*/
int main(){
	char *str[] = {"ABBAC","BACDA","AEFAA","XXXXX"};
	int n = sizeof(str)/sizeof(str[0]);
	int len = 5;
	int noo;
	char final[100];
	strcpy(final,str[0]);
	/*char overlappedString[100] = overlap(str,n);*/
	for(int i=0;i<n-1;i++){
		noo = number_of_overlap(&str[i],&str[i+1]);
		printf("noo = %d ",noo);
		strcat(final,&str[i+1][noo]);
	}
	printf("%s \n",final);
}