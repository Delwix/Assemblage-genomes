#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scs.c"


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
