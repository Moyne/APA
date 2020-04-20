#ifndef PG_H
#define PG_H

#include "inventario.h"


typedef struct
{
    Inventario  *vettEq[8];
    int inUso;
}tabEquip_t;
typedef struct
{
    char codice[7],nome[Nmax],classe[Nmax];
    tabEquip_t equip;
    stat_t stat;
} personaggio;

typedef struct node
{
    personaggio pg;
    struct node *next;
}node_t,*link;
typedef struct{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

link newNode(personaggio pg,link next);
link listInsHead(link h,personaggio pg);

void leggiPg(int *k,tabPg_t* tabPg);
void stampaPg(tabPg_t* tabPg);
void creazionePg(tabPg_t* tabPg);
void rimozionePg(tabPg_t* tabPg);
void equip(tabPg_t* tabPg,Inventario* oggetti,int numeroO);
#endif
