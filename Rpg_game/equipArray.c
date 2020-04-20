//
// Created by Moyne on 11/12/2019.
//

#include "equipArray.h"


struct tabEquip_t
{
    int *vettEq;
    int inUso;
};

tabEquip initEquip(tabInv_t tabInv)
{
    tabEquip equip=malloc(sizeof( *equip ));
    equip->vettEq=malloc(getMaxInv(tabInv)* sizeof(int ));
    equip->inUso=0;
    return equip;
}
void freeEquip(tabEquip equip)
{
    free(equip->vettEq);
    free(equip);
}
void stampaEquip(tabEquip equip,tabInv_t tabInv)
{
    int i;
    if((equip->inUso)>0)
    {
        printf("\nOggetti in uso:  ");
        for(i=0;i<equip->inUso;i++) printEquip(equip->vettEq[i],tabInv);
    }
    return;
}

int scanRimEquip(tabEquip equip,int oggetto)
{
    for(int i=0;i<equip->inUso;i++)
    {
        if(equip->vettEq[i]==oggetto)
        {
            equip->vettEq[i]=equip->vettEq[equip->inUso-1];
            return 1;
        }
    }
    return 0;
}

void aggNequip(tabEquip equip,int aggiungo,int oggetto)
{
    if(aggiungo==1)
    {
        (equip->vettEq)[equip->inUso]=oggetto;
        equip->inUso++;
        printf("\nOggetti in uso nel seguente personaggio:    %d\n\n",equip->inUso);
    }
    if(aggiungo==0)
    {
        equip->inUso--;
        printf("\nOggetti in uso nel seguente personaggio:    %d\n\n",equip->inUso);
    }
}
int troppiOgg(tabEquip equip,tabInv_t tabInv)
{
    if(equip->inUso>=getMaxInv(tabInv))
    {
        printf("\nIl seguente pg ha troppi oggetti nell'inventario\n");
        return 1;
    }
    return 0;
}
int inUso(tabEquip equip)
{
    return equip->inUso;
}
