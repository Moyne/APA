#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int si,fi;
}att_t;

att_t *leggiAtt(int *nAtt)
{
    FILE* fatt;
    fatt=fopen("att.txt","r");
    fscanf(fatt,"%d",nAtt);
    att_t *att=malloc(*nAtt*sizeof(att_t));
    for(int i=0;i<*nAtt;i++)
        fscanf(fatt,"%d %d",&att[i].si,&att[i].fi);
    return att;
}
int fine(int pos,att_t **sol,att_t *att,int nAtt)
{
    if(pos==0)  return 0;
    for(int j=0;j<nAtt;j++)
    {
        if((*sol)[pos-1].fi<=att[j].si) return 0;
    }
    return 1;
}
void poss(att_t **sol,att_t *att,int pos,int *mark,int nAtt,int *max,att_t **solMax,int *nMax)
{
    int i;
    if(fine(pos,sol,att,nAtt))
    {
        int dist=0;
        for(i=0;i<pos;i++)  dist+=((*sol)[i].fi-(*sol)[i].si);
        if(dist>=*max)
        {
            (*max)=dist;
            *nMax=pos;
            for(i=0;i<pos;i++)  (*solMax)[i]=(*sol)[i];
        }
        return;
    }
    for(i=0;i<nAtt;i++){
        if(pos==0)
        {
            (*sol)[pos]=att[i];
            mark[i]=1;
            poss(sol,att,pos+1,mark,nAtt,max,solMax,nMax);
            mark[i]=0;
        }
        else
        {
            if(mark[i]==0 && (((att)[i].si)>=((*sol)[pos-1].fi)))
            {
                (*sol)[pos]=att[i];
                mark[i]=1;
                poss(sol,att,pos+1,mark,nAtt,max,solMax,nMax);
                mark[i]=0;
            }
        }
    }
    return;
}
void attSel(int N,att_t *v)
{
    int pos=0,max=0,nMax;
    int *mark=calloc(N, sizeof(int));
    att_t *sol=malloc(N*sizeof(*sol));
    att_t *solMax=malloc(N*sizeof(*solMax));
    poss(&sol,v,pos,mark,N,&max,&solMax,&nMax);
    free(sol);
    free(mark);
    printf("Soluzione con dist. %d :\n",max);
    for(int i=0;i<nMax;i++) printf("%d %d\n\n",solMax[i].si,solMax[i].fi);
    free(solMax);
}
int main()
{
    int nAtt;
    att_t *att=leggiAtt(&nAtt);
    attSel(nAtt,att);
    free(att);
    return 0;
}
