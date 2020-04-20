//
// Created by Moyne on 11/12/2019.
//

#include "invArray.h"

struct tabInv_s
{
    inventario_t *invArray;
    int nInv;
    int maxInv;
};
tabInv_t leggiInventario()
{
    FILE *fi;
    int i,numeroO,maxInv;
    fi=fopen("inventario.txt","r");
    fscanf(fi,"%d",&numeroO);
    inventario_t temp;
    tabInv_t tabInv=malloc(sizeof(*tabInv));
    tabInv->nInv=numeroO;
    printf("Qual'e' il numero massimo di oggetti ammissibili nell'inventario di un pg?  ");
    scanf("%d",&maxInv);
    tabInv->maxInv=maxInv;
    tabInv->invArray=initInv(numeroO);
    printf("\n\n");
    for(i=0;i<tabInv->nInv;i++)
    {
        fscanf(fi,"%s %s %d %d %d %d %d %d",temp.nome,temp.tipologia,&temp.stat.hp,&temp.stat.mp,&temp.stat.atk,&temp.stat.def,&temp.stat.mag,&temp.stat.spr);
        (tabInv->invArray[i])=temp;
    }
    fclose(fi);
    return tabInv;
}
void liberaInventario(tabInv_t tabInv)
{
    freeInv(tabInv->invArray);
    free(tabInv);
}
void stampaInventario(tabInv_t tabInv)
{
    int i;
    printf("Inventario:\n\n");
    for(i=0;i<tabInv->nInv;i++)
    {
        printf("%s %s %d %d %d %d %d %d",tabInv->invArray[i].nome,tabInv->invArray[i].tipologia,tabInv->invArray[i].stat.hp,tabInv->invArray[i].stat.mp,tabInv->invArray[i].stat.atk,tabInv->invArray[i].stat.def,tabInv->invArray[i].stat.mag,tabInv->invArray[i].stat.spr);
        printf("\n\n");
    }
    return;
}
int cmpInv(char oggettoCercato[Nmax],tabInv_t tabInv)
{
    int i;
    for(i=0;i<tabInv->nInv;i++)
    {
        if(strcmp(tabInv->invArray[i].nome,oggettoCercato)==0)
        {
            return i;
        }
    }
    return -1;
}
int statHp(int i,tabInv_t tabInv)
{
    return tabInv->invArray[i].stat.hp;
}
int statMp(int i,tabInv_t tabInv)
{
    return tabInv->invArray[i].stat.mp;
}
int statAtk(int i,tabInv_t tabInv)
{
    return tabInv->invArray[i].stat.atk;
}
int statDef(int i,tabInv_t tabInv)
{
    return tabInv->invArray[i].stat.def;
}
int statMag(int i,tabInv_t tabInv)
{
    return tabInv->invArray[i].stat.mag;
}
int statSpr(int i,tabInv_t tabInv)
{
    return tabInv->invArray[i].stat.spr;
}
void printEquip(int i,tabInv_t tabInv)
{
    printf("  %s  ",tabInv->invArray[i].nome);
}
int getMaxInv(tabInv_t tabInv)
{
    return tabInv->maxInv;
}
