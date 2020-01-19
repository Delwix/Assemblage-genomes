//wrong
int number_of_overlap(char *a,char *b){
	int na,nb;
	int j=0;
	na=strlen(a);
	nb=strlen(b);
	for(int i=0;i<na;i++){
		if(b[j]==a[i])
			j=j+1;
		else	
			j=0;
	}
	return j;
}