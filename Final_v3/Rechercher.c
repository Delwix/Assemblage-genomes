#include <stdio.h>
#include <stdlib.h>
#include "Rechercher.h"
#include "fastq.h"
#include <stdbool.h>


bool rechercherFromReads(char* motif, char* file_dir){
    bool d;
    int i = 0;
    char** sequence;
    int nbrReads = nbre_read(file_dir);
    int n = taille_read(file_dir);
    sequence = malloc(nbrReads*sizeof(char*));
    for(int i=0; i < nbrReads; i++)
        sequence[i] = malloc(n*sizeof(char));
    extract_file(file_dir,sequence);
    //rechercherFromReads(sequence,read,n);
    while(strstr(sequence[i],motif) == NULL && i < nbrReads-1){
        //printf("%d\n",strstr(sequence[i],motif) );
        //printf("i=%d,", i)
        i++ ;
    }
    if(i < nbrReads-1 || strstr(sequence[i],motif) != NULL ){
        printf("TROUVEE dans le read num %d",i);
        d = true;

         //Motif trouve
    }
    else{
        printf("Motif non trouve");
        d = false;
        //Motif non trouve
    }
    return d;
}
