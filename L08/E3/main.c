#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"

void selezione(tabPg_t *tabPg,Inventario *oggetti,int numeroO)
{
    int selezione,fine=0;
    while(fine==0)
    {
        printf("\n\nSelezionare l'azione da fare\n  -1 per aggiunta di personaggio\n  -2 per rimozione\n  -3 per equipaggiamento o rimozione di un oggetto\n  -4 per stampa\n  -5 per chiudere\n  : ");
        scanf("%d",&selezione);
        if(selezione==1)
        {
            creazionePg(tabPg);
        }
        if(selezione==2)
        {
            rimozionePg(tabPg);
        }
        if(selezione==3)
        {
            equip(tabPg,oggetti,numeroO);
        }
        if(selezione==4)    stampaPg(tabPg);
        if(selezione==5)    fine=1;
    }
}

int main()
{
    tabPg_t tabPg;
    int numPg,numeroO;
    Inventario *oggetti=leggiInventario(&numeroO);
    stampaInv(oggetti,numeroO);
    leggiPg(&numPg,&tabPg);
    stampaPg(&tabPg);
    selezione(&tabPg,oggetti,numeroO);
    liberaInventario(oggetti);
    return 0;
}
