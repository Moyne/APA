//
// Created by Moyne on 11/12/2019.
//

#ifndef ES02LAB09_INVARRAY_H
#define ES02LAB09_INVARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
typedef struct tabInv_s *tabInv_t;
tabInv_t leggiInventario();
void liberaInventario(tabInv_t tabInv);
void stampaInventario(tabInv_t tabInv);
int cmpInv(char oggettoCercato[Nmax],tabInv_t tabInv);
int statHp(int i,tabInv_t tabInv);
int statMp(int i,tabInv_t tabInv);
int statAtk(int i,tabInv_t tabInv);
int statDef(int i,tabInv_t tabInv);
int statMag(int i,tabInv_t tabInv);
int statSpr(int i,tabInv_t tabInv);
void printEquip(int i,tabInv_t tabInv);
int getMaxInv(tabInv_t tabInv);
#endif //ES02LAB09_INVARRAY_H
