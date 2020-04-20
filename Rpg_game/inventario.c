//
// Created by Moyne on 10/12/2019.
//


#include "inventario.h"
inventario_t *initInv(int n)
{
    inventario_t *inv=malloc(n* sizeof(inventario_t ));
    return inv;
}
void freeInv(inventario_t *inv)
{
    free(inv);
}