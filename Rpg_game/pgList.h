//
// Created by Moyne on 11/12/2019.
//

#ifndef ES02LAB09_PGLIST_H
#define ES02LAB09_PGLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"
typedef struct tabPg_s *tabPg_t;
tabPg_t init();
void freeTabPg(tabPg_t tabPg);
void leggiPg(tabPg_t tabPg,tabInv_t tabInv);
void stampa(tabPg_t tabPg,tabInv_t tabInv);
void creazione(tabPg_t tabPg,tabInv_t tabInv);
void rimozionePg(tabPg_t tabPg);
void equip(tabPg_t tabPg,tabInv_t tabInv);
#endif //ES02LAB09_PGLIST_H
