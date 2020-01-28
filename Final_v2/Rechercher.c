void rechercherFromReads(char** sequence, int n, int nbrReads){
    //rechercherFromReads(sequence,read,n);
    char* motif ;
    int i = 0;
    motif  = malloc((n+1)*sizeof(char));
    printf("Entrer un motif : \n");
    scanf("%s", motif);
    while(strstr(sequence[i],motif) == NULL && i < nbrReads-1){
        //printf("%d\n",strstr(sequence[i],motif) );
        //printf("i=%d,", i)
        i++ ;
    }
    if(i < nbrReads-1 || strstr(sequence[i],motif) != NULL ){
        printf("TROUVEE dans le read num %d",i);

         //Motif trouve
    }
    else{
        printf("Motif non trouve");
        //Motif non trouve
    }
}
