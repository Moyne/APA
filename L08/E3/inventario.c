#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"

Inventario *leggiInventario(int *numeroO)
{
    FILE *fi;
    int i;
    fi=fopen("inventario.txt","r");
    if(fi==NULL)
    {
        printf("\n\nErrore nell'apertura del file.\n");
        return -1;
    }
    fscanf(fi,"%d",numeroO);
    Inventario temp;
    Inventario *oggetti=malloc((*numeroO)*sizeof(Inventario));
    for(i=0;i<(*numeroO);i++)
    {
        fscanf(fi,"%s %s %d %d %d %d %d %d",temp.nome,temp.tipologia,&temp.stat.hp,&temp.stat.mp,&temp.stat.atk,&temp.stat.def,&temp.stat.mag,&temp.stat.spr);
        oggetti[i]=temp;
    }
    fclose(fi);
    return oggetti;
}
void liberaInventario(Inventario *oggetti)
{
    free(oggetti);
}
void stampaInv(Inventario *oggetti,int numeroO)
{
    printf("Gli oggetti nell'inventario sono i seguenti:\n\n");
    for(int i=0;i<numeroO;i++)
    {
        printf("%s %s %d %d %d %d %d %d",oggetti[i].nome,oggetti[i].tipologia,oggetti[i].stat.hp,oggetti[i].stat.mp,oggetti[i].stat.atk,oggetti[i].stat.def,oggetti[i].stat.mag,oggetti[i].stat.spr);
        printf("\n\n");
    }
    printf("\n\n");
}
