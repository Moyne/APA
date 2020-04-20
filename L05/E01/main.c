#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef struct
{
    int numerocasi;
    char **canzoni;
} Item;

Item *letturaCanzoni(int Namici,FILE* fp)
{
    int k,l,i=0,j,songs;
    Item *brani=malloc(Namici*sizeof(Item));
    for( k=0;k<Namici;k++)
    {
        brani[k].canzoni=malloc(Namici*sizeof(char *));
        for(l=0;l<Namici;l++)
        {
            brani[k].canzoni[l]=malloc(255*sizeof(char));
        }
    }
    for(i=0;i<Namici;i++){
        fscanf(fp,"%d",&brani[i].numerocasi);
        for(j=0;j<brani[i].numerocasi;j++)
        {
            fscanf(fp,"%s",brani[i].canzoni[j]);
        }
    }
    return brani;
}
void stampaBrani(Item *brani,int Namici)
{
    int i,j;
    for(i=0;i<Namici;i++)
    {
        printf("\nCanzoni amico n.%d:\n",i+1);
        for(j=0;j<brani[i].numerocasi;j++)
        {
            printf("\n%s\n",brani[i].canzoni[j]);
        }
        printf("\n");
    }
}
int princ_molt(int pos,Item *brani, char sol[N][N], int n, int count)
{
    int i;
    if (pos >= n)
    {
        for (i = 0; i < n; i++) printf("%s ", sol[i]);
        printf("\n\n");
        return count+1;
        free(brani);
    }
    for (i = 0; i < brani[pos].numerocasi; i++)
    {
        strcpy(sol[pos],brani[pos].canzoni[i]);
        count = princ_molt(pos+1, brani, sol, n, count);
    }
    return count;
}

int main()
{
    printf("kek!");
    int Namici,count=0,pos=0;
    char sol[N][N];
    FILE* fp;
    fp=fopen("brani.txt","r");
    if(fp==NULL)
    {
        printf("ERRORE NELL'APERTURA DEL FILE");
        return -1;
    }
    fscanf(fp,"%d",&Namici);
    Item *brani=letturaCanzoni(Namici,fp);
    stampaBrani(brani,Namici);
    printf("\n\nStampa delle possibilita':\n\n");
    int numero_possibilita=princ_molt(pos,brani,sol,Namici,count);
    printf("\n\nCi sono state %d possibilita'",numero_possibilita);
    return 0;

}

