//
// Created by Moyne on 11/12/2019.
//

#include "pgList.h"
typedef struct node_s *link;
struct node_s
{
    personaggio pg;
    link next;
};

struct tabPg_s
{
    link headPg;
    link tailPg;
    int nPg;
};
tabPg_t init()
{
    tabPg_t tabPg=malloc(sizeof(*tabPg));
    tabPg->headPg=NULL;
    tabPg->nPg=0;
    return tabPg;
}
void freeTabPg(tabPg_t tabPg)
{
    for(tabPg->tailPg=tabPg->headPg;tabPg->tailPg!=NULL;tabPg->tailPg=tabPg->tailPg->next)
    {
        freeEquip(tabPg->tailPg->pg.equip);
        free(tabPg->tailPg);
    }
    free(tabPg);
}
link newNode(personaggio pg,link next)
{
    link x=malloc(sizeof *x);
    if(x==NULL) return NULL;
    else
    {
        x->pg=pg;
        x->next=next;
    }
    return x;
}

link listInsHead(link h,personaggio pg)
{
    h=newNode(pg,h);
    return h;
}

void leggiPg(tabPg_t tabPg,tabInv_t tabInv)
{
    FILE *fp;
    fp=fopen("pg.txt","r");
    personaggio temp;
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",temp.codice,temp.nome,temp.classe,&temp.stat.hp,&temp.stat.mp,&temp.stat.atk,&temp.stat.def,&temp.stat.mag,&temp.stat.spr)!=EOF)
    {
        tabPg->headPg=listInsHead(tabPg->headPg,temp);
        tabPg->headPg->pg.equip=initEquip(tabInv);
        tabPg->nPg++;
    }
    fclose(fp);
    return;
}

void stampa(tabPg_t tabPg,tabInv_t tabInv)
{
    int i;
    printf("I personaggi sono i seguenti:\n\n");
    link x,h=tabPg->headPg;
    for(x=h;x!=NULL;x=x->next)
    {
        stampaPg(x->pg,tabInv);
        printf("\n\n");
    }
}
int searchByCode(char codice[7],tabPg_t tabPg)
{
    link x,p,h;
    h=tabPg->headPg;
    for(x=h,p=NULL;x!=NULL;p=x,x=x->next) {
        if (strcmp(codice, x->pg.codice) == 0) {
            return 1;
        }
    }
    return 0;
}
void creazione(tabPg_t tabPg,tabInv_t tabInv)
{
    personaggio temp;
    printf("\nCodice del pg:   ");
    scanf("%s",temp.codice);
    if(searchByCode(temp.codice,tabPg))
    {
        printf("\n\nCodice gia' presente.\n\n");
        return;
    }
    printf("\nNome del pg:   ");
    scanf("%s",temp.nome);
    printf("\nClasse del pg:   ");
    scanf("%s",temp.classe);
    printf("\nHp del pg:   ");
    scanf("%d",&temp.stat.hp);
    printf("\nMp del pg:   ");
    scanf("%d",&temp.stat.mp);
    printf("\nAtk del pg:   ");
    scanf("%d",&temp.stat.atk);
    printf("\nDef del pg:   ");
    scanf("%d",&temp.stat.def);
    printf("\nMag del pg:   ");
    scanf("%d",&temp.stat.mag);
    printf("\nSpr del pg:   ");
    scanf("%d",&temp.stat.spr);
    tabPg->headPg=listInsHead(tabPg->headPg,temp);
    tabPg->headPg->pg.equip=initEquip(tabInv);
    return;
}

void rimozionePg(tabPg_t tabPg)
{
    char ricerca[Nmax];
    printf("Selezionare il nome del pg da rimuovere:    ");
    scanf("%s",ricerca);
    link x,p,h;
    h=tabPg->headPg;
    for(x=h,p=NULL;x!=NULL;p=x,x=x->next)
    {
        if(strcmp(ricerca,x->pg.nome)==0)
        {
            printf("\nIl personaggio da rimuovere e' il seguente:\n\n");
            printf("%s %s %s %d %d %d %d %d %d\n\n",x->pg.codice,x->pg.nome,x->pg.classe,x->pg.stat.hp,x->pg.stat.mp,x->pg.stat.atk,x->pg.stat.def,x->pg.stat.mag,x->pg.stat.spr);
            if(h==x)    tabPg->headPg=x->next;
            else    p->next=x->next;
            freeEquip(x->pg.equip);
            free(x);
            printf("\n");
            return;
        }
    }
    printf("\n\nPg non trovato\n\n");
    return;
}

void equip(tabPg_t tabPg,tabInv_t tabInv)
{
    int aggiungo,flag=0;
    printf("\nSelezionare\n  -1 se si vuole assegnare un oggetto\n  -0 se si vuole rimuovere un oggetto\n :    ");
    scanf("%d",&aggiungo);
    printf("\nScrivere il nome dell'ogetto che si vuole assegnare/rimuovere:    ");
    char oggettoCercato[Nmax],personaggioCercato[Nmax];
    scanf("%s",oggettoCercato);
    int oggetto,i;
    link x,h=tabPg->headPg;
    oggetto=cmpInv(oggettoCercato,tabInv);
    if(oggetto==(-1))
    {
        printf("\nOggetto non trovato\n");
        return;
    }
    printf("\nOggetto:  %s   da assegnare/rimuovere al seguente personaggio:    ",oggettoCercato);
    scanf("%s",personaggioCercato);
    for(x=h;x!=NULL;x=x->next)
    {
        if(strcmp(personaggioCercato,x->pg.nome)==0)
        {
            if(aggiungo==1)
            {
                if(troppiOgg(x->pg.equip,tabInv)) return;
                aggStatPg(&(x->pg),tabInv,aggiungo,oggetto);
                aggNequip(x->pg.equip,aggiungo,oggetto);
                return;
            }
            if(aggiungo==0)
            {
                flag=scanRimEquip(x->pg.equip,oggetto);
                if(flag==0)
                {
                    printf("\nIl seguente oggetto non e' stato trovato nell'inventario del pg selezionato\n");
                    return;
                }
                if(flag==1)
                {
                    aggNequip(x->pg.equip,aggiungo,oggetto);
                    aggStatPg(&(x->pg),tabInv,aggiungo,oggetto);
                    return;
                }
            }
        }
    }
    printf("\nPersonaggio non trovato\n");
    return;
}