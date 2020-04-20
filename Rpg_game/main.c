#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invArray.h"
#include "pg.h"
#include "pgList.h"

void selezione(tabPg_t tabPg,tabInv_t tabInv)
{
    int selezione,fine=0;
    stampaInventario(tabInv);
    stampa(tabPg,tabInv);
    while(fine==0)
    {
        printf("\n\nSelezionare l'azione da fare\n  -1 per aggiunta di personaggio\n  -2 per rimozione\n  -3 per equipaggiamento o rimozione di un oggetto\n  -4 per stampa\n  -5 per chiudere\n  : ");
        scanf("%d",&selezione);
        if(selezione==1)
        {
            creazione(tabPg,tabInv);
        }
        if(selezione==2)
        {
            rimozionePg(tabPg);
        }
        if(selezione==3)
        {
            equip(tabPg,tabInv);
        }
        if(selezione==4)    stampa(tabPg,tabInv);
        if(selezione==5)    fine=1;
    }
}

int main() {
    tabInv_t tabInv=leggiInventario();
    tabPg_t tabPg = init();
    leggiPg(tabPg,tabInv);
    selezione(tabPg,tabInv);
    freeTabPg(tabPg);
    liberaInventario(tabInv);
    return 0;
}