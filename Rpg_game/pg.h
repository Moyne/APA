//
// Created by Moyne on 10/12/2019.
//

#ifndef ES02LAB09_PG_H
#define ES02LAB09_PG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "invArray.h"
#include "equipArray.h"


typedef struct
{
    char codice[7],nome[Nmax],classe[Nmax];
    tabEquip equip;
    stat_t stat;
} personaggio;


void stampaPg(personaggio pg,tabInv_t tabInv);
void aggStatPg(personaggio *pg,tabInv_t tabInv,int aggiungo,int oggetto);

#endif //ES02LAB09_PG_H
