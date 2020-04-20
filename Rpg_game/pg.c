//
// Created by Moyne on 10/12/2019.
//

#include "pg.h"



void  stampaPg(personaggio pg,tabInv_t tabInv)
{
    printf("%s %s %s ",pg.codice,pg.nome,pg.classe);
    if(pg.stat.hp<1)    printf("1 ");
    else    printf("%d ",pg.stat.hp);
    if(pg.stat.mp<1)    printf("1 ");
    else    printf("%d ",pg.stat.mp);
    if(pg.stat.atk<1)    printf("1 ");
    else    printf("%d ",pg.stat.atk);
    if(pg.stat.def<1)    printf("1 ");
    else    printf("%d ",pg.stat.def);
    if(pg.stat.mag<1)    printf("1 ");
    else    printf("%d ",pg.stat.mag);
    if(pg.stat.spr<1)    printf("1 ");
    else    printf("%d ",pg.stat.spr);
    stampaEquip(pg.equip,tabInv);
}



void aggStatPg(personaggio *pg,tabInv_t tabInv,int aggiungo,int oggetto)
{
    if(aggiungo==1)
    {
        pg->stat.hp=pg->stat.hp+statHp(oggetto,tabInv);
        pg->stat.mp=pg->stat.mp+statMp(oggetto,tabInv);
        pg->stat.atk=pg->stat.atk+statAtk(oggetto,tabInv);
        pg->stat.def=pg->stat.def+statDef(oggetto,tabInv);
        pg->stat.mag=pg->stat.mag+statMag(oggetto,tabInv);
        pg->stat.spr=pg->stat.spr+statSpr(oggetto,tabInv);
    }
    if(aggiungo==0)
    {
        pg->stat.hp=pg->stat.hp-statHp(oggetto,tabInv);
        pg->stat.mp=pg->stat.mp-statMp(oggetto,tabInv);
        pg->stat.atk=pg->stat.atk-statAtk(oggetto,tabInv);
        pg->stat.def=pg->stat.def-statDef(oggetto,tabInv);
        pg->stat.mag=pg->stat.mag-statMag(oggetto,tabInv);
        pg->stat.spr=pg->stat.spr-statSpr(oggetto,tabInv);
    }
}
