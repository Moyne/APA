//
// Created by Moyne on 10/12/2019.
//

#ifndef ES02LAB09_INVENTARIO_H
#define ES02LAB09_INVENTARIO_H
#include <stdio.h>
#include <stdlib.h>
#define Nmax 50

typedef struct
{
    int hp,mp,atk,def,mag,spr;
}stat_t;
typedef struct
{
    char nome[Nmax],tipologia[Nmax];
    stat_t stat;
}inventario_t;
inventario_t *initInv(int n);
void freeInv(inventario_t *inv);
#endif //ES02LAB09_INVENTARIO_H
