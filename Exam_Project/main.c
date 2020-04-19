#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define MAXC 30
int main() {
    char filename[MAXC];
    printf("\nSi scriva il nome del file: ");
    scanf("%s",filename);
    FILE* fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("\nErrore nell'apertura del file.");
        return 0;
    }
    Graph g=GRAPHload(fp);
    kcore(g);
    jEdge(g);
    GRAPHfree(g);
    return 0;
}