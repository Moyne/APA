#ifndef INVENTARIO_H
#define INVENTARIO_H

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
}Inventario;


void liberaInventario(Inventario* oggetti);
Inventario *leggiInventario(int *numeroO);
void stampaInv(Inventario* oggetti,int numeroO);
#endif
