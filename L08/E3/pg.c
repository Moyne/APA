#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"

link newNode(personaggio pg,link next)
{
    link x=malloc(sizeof *x);
    for(int i=0;i<8;i++)
        (x->pg.equip.vettEq)[i]=malloc(sizeof(Inventario *));
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

void leggiPg(int *k,tabPg_t *tabPg)
{
    FILE *fp;
    fp=fopen("pg.txt","r");
    if(fp==NULL)
    {
        printf("\n\nErrore apertura file.\n");
        return -1;
    }
    personaggio temp;
    int j=0;
    tabPg->headPg=NULL;
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",temp.codice,temp.nome,temp.classe,&temp.stat.hp,&temp.stat.mp,&temp.stat.atk,&temp.stat.def,&temp.stat.mag,&temp.stat.spr)!=EOF)
    {
        j++;
        temp.equip.inUso=0;
        tabPg->headPg=listInsHead(tabPg->headPg,temp);
    }
    *k=j;
    fclose(fp);
    return;
}

void stampaPg(tabPg_t *tabPg)
{
    int i;
    printf("I personaggi sono i seguenti:\n\n");
    for(tabPg->tailPg=tabPg->headPg;tabPg->tailPg!=NULL;tabPg->tailPg=tabPg->tailPg->next)
    {
        printf("%s %s %s %d %d %d %d %d %d",tabPg->tailPg->pg.codice,tabPg->tailPg->pg.nome,tabPg->tailPg->pg.classe,tabPg->tailPg->pg.stat.hp,tabPg->tailPg->pg.stat.mp,tabPg->tailPg->pg.stat.atk,tabPg->tailPg->pg.stat.def,tabPg->tailPg->pg.stat.mag,tabPg->tailPg->pg.stat.spr);
        if(tabPg->tailPg->pg.equip.inUso>0)
        {
            printf("\nOggetti in uso:  ");
            for(i=0;i<tabPg->tailPg->pg.equip.inUso;i++) printf("%s ",tabPg->tailPg->pg.equip.vettEq[i]->nome);
        }
        printf("\n\n");
    }
}

void creazionePg(tabPg_t *tabPg)
{
    personaggio temp;
    printf("\nCodice del pg:   ");
    scanf("%s",temp.codice);
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
    temp.equip.inUso=0;
    tabPg->headPg=listInsHead(tabPg->headPg,temp);
    return;
}

void rimozionePg(tabPg_t *tabPg)
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
            free(x);
            printf("\n");
            return;
        }
    }
    printf("\n\nPg non trovato\n\n");
    return;
}

void equip(tabPg_t *tabPg,Inventario *oggetti,int numeroO)
{
    int aggiungo,flag=0;
    printf("\nSelezionare\n  -1 se si vuole assegnare un oggetto\n  -0 se si vuole rimuovere un oggetto\n :    ");
    scanf("%d",&aggiungo);
    printf("\nScrivere il nome dell'ogetto che si vuole assegnare/rimuovere:    ");
    char oggettoCercato[Nmax],personaggioCercato[Nmax];
    scanf("%s",oggettoCercato);
    int oggetto,i;
    link x,h=tabPg->headPg;
    for(i=0;i<numeroO;i++)
    {
        if(strcmp(oggetti[i].nome,oggettoCercato)==0)
        {
            oggetto=i;
            break;
        }
        else    oggetto=(-1);
    }
    if(oggetto==(-1))
    {
        printf("\nOggetto non trovato\n");
        return;
    }
    printf("\nOggetto:  %s   da assegnare/rimuovere al seguente personaggio:    ",oggetti[oggetto].nome);
    scanf("%s",personaggioCercato);
    for(x=h;x!=NULL;x=x->next)
    {
        if(strcmp(personaggioCercato,x->pg.nome)==0)
        {
            if(aggiungo==1)
            {
                if(x->pg.equip.inUso>=8)
                {
                    printf("\nIl seguente pg ha troppi oggetti nell'inventario\n");
                    return;
                }
                (x->pg.equip.vettEq)[x->pg.equip.inUso]=&oggetti[oggetto];
                x->pg.stat.hp=x->pg.stat.hp+oggetti[oggetto].stat.hp;
                if(x->pg.stat.hp<1) x->pg.stat.hp=1;
                x->pg.stat.mp=x->pg.stat.mp+oggetti[oggetto].stat.mp;
                if(x->pg.stat.mp<1) x->pg.stat.mp=1;
                x->pg.stat.atk=x->pg.stat.atk+oggetti[oggetto].stat.atk;
                if(x->pg.stat.atk<1) x->pg.stat.atk=1;
                x->pg.stat.def=x->pg.stat.def+oggetti[oggetto].stat.def;
                if(x->pg.stat.def<1) x->pg.stat.def=1;
                x->pg.stat.mag=x->pg.stat.mag+oggetti[oggetto].stat.mag;
                if(x->pg.stat.mag<1) x->pg.stat.mag=1;
                x->pg.stat.spr=x->pg.stat.spr+oggetti[oggetto].stat.spr;
                if(x->pg.stat.spr<1) x->pg.stat.spr=1;
                x->pg.equip.inUso++;
                printf("\nOggetti in uso nel seguente personaggio:    %d\n\n",x->pg.equip.inUso);
                return;
            }
            if(aggiungo==0)
            {
                for(int i=0;i<x->pg.equip.inUso;i++)
                {
                    if(strcmp(x->pg.equip.vettEq[i]->nome,oggetti[oggetto].nome)==0)
                    {
                        flag=1;
                        x->pg.equip.vettEq[i]=x->pg.equip.vettEq[x->pg.equip.inUso-1];
                        break;
                    }
                }
                if(flag==0)
                {
                    printf("\nIl seguente oggetto non e' stato trovato nell'inventario del pg selezionato\n");
                    return;
                }
                if(flag==1)
                {
                    (x->pg.equip.inUso)--;
                    printf("\nOggetti in uso nel seguente personaggio:    %d\n\n",x->pg.equip.inUso);
                    x->pg.stat.hp=x->pg.stat.hp-oggetti[oggetto].stat.hp;
                    if(x->pg.stat.hp<1) x->pg.stat.hp=1;
                    x->pg.stat.mp=x->pg.stat.mp-oggetti[oggetto].stat.mp;
                    if(x->pg.stat.mp<1) x->pg.stat.mp=1;
                    x->pg.stat.atk=x->pg.stat.atk-oggetti[oggetto].stat.atk;
                    if(x->pg.stat.atk<1) x->pg.stat.atk=1;
                    x->pg.stat.def=x->pg.stat.def-oggetti[oggetto].stat.def;
                    if(x->pg.stat.def<1) x->pg.stat.def=1;
                    x->pg.stat.mag=x->pg.stat.mag-oggetti[oggetto].stat.mag;
                    if(x->pg.stat.mag<1) x->pg.stat.mag=1;
                    x->pg.stat.spr=x->pg.stat.spr-oggetti[oggetto].stat.spr;
                    if(x->pg.stat.spr<1) x->pg.stat.spr=1;
                    return;
                }
            }
        }
    }
    printf("\nPersonaggio non trovato\n");
    return;
}
