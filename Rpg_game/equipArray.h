//
// Created by Moyne on 11/12/2019.
//

#ifndef ES02LAB09_EQUIPARRAY_H
#define ES02LAB09_EQUIPARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include "invArray.h"
typedef struct tabEquip_t *tabEquip;

tabEquip initEquip(tabInv_t tabInv);
void freeEquip(tabEquip equip);
void stampaEquip(tabEquip equip,tabInv_t tabInv);
int scanRimEquip(tabEquip equip,int oggetto);
void aggNequip(tabEquip equip,int aggiungo,int oggetto);
int troppiOgg(tabEquip equip,tabInv_t tabInv);
int inUso(tabEquip equip);

#endif //ES02LAB09_EQUIPARRAY_H
