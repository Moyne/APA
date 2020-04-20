#include <stdio.h>
#include <stdlib.h>
FILE* fp;

int *malloc2dp(int nr,int nc)
{
    int *v=malloc(nr*nc*(sizeof(int)));
    for(int i=0;i<nr;i++)
    {
        for(int j=0;j<nc;j++)
        {
            fscanf(fp,"%d",&v[nc*i+j]);
        }
    }
    return v;
}

int main()
{
    int nr,nc,N=1,B=1,i,bianchi=0,neri=0;
    fp=fopen("mat.txt","r");
    if(fp==NULL)    return -1;
    fscanf(fp,"%d %d",&nr,&nc);
    int *v=malloc2dp(nr,nc);
    int *vBianchi=malloc(B*sizeof(int));
    int *vNeri=malloc(N*sizeof(int));
    for(int k=0;k<(nc*nr);k++)
    {
        if(((k%2)==0) ||(k==0)      )         //se è pari
        {
            bianchi++;
            if(bianchi==B)
            {
                B++;
                vBianchi=realloc(vBianchi,(B*sizeof(int)));
            }
            vBianchi[bianchi]=v[k];
        }
        else
        {
            neri++;
            if(neri==N)
            {
                N++;
                vNeri=realloc(vNeri,(N*sizeof(int)));
            }
            vNeri[neri]=v[k];
        }
    }
    printf("Scacchiera bianca:\n");
    for(i=1;i<B;i++)
    {
        printf("-%d",vBianchi[i]);
    }
    printf("\n\nScacchiera nera:\n");
    for(i=1;i<N;i++)
    {
        printf("-%d",vNeri[i]);
    }
    free(v);
    free(vNeri);
    free(vBianchi);
    fclose(fp);
    return 0;
}
