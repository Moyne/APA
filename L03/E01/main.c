#include <stdio.h>
#include <stdlib.h>
#define N 50
FILE* fp;


void LeggiMatrice(int M [N][N],int *nr,int *nc){                                    //FUNZIONE PER LEGGERE LA MATRICE E MEMORIZZARLA
    int n;
    fscanf(fp,"%d %d",nr,nc);
    for(int r=0;r<(*nr);r++){
        for(int c=0;c<(*nc);c++){
            fscanf(fp,"%d",&n);
            M[r][c]=n;
            if(n==1)
                printf("%c",219);
            else
                printf(" ");
        }
        printf("\n");
    }
}

int RiconosciRegione(int M [N][N],int nr,int nc,int r,int c,int *b,int *h){         //FUNZIONE PER RICONOSCERE IL RETTANGOLO OTTENUTO, TROVANDO BASE ED AREA
    (*h)=0;
    (*b)=0;
    int k,z;
    for(k=r;k<nr;k++){                                                              //CALCOLO ALTEZZA
        if(M[k][c]==1)
            (*h)++;
        else
            k=N;
        }
    for(z=c;z<nc;z++){                                                              //CALCOLO BASE
        if(M[r][z]==1)
            (*b)++;
        else
            z=N;}
    if((*b)>0)                                                                      //SE IL RETTANGOLO NON E' NULLO LA FUNZIONE RESTITUISCE 1
        return 1;
    else                                                                            //SE IL RETTANGOLO E' NULLO LA FUNZIONE RESTITUISCE 0
        return 0;
    }


int main()
{
    int nr,nc,b,h;
    int M[N][N],areamax=0,bmax=0,hmax=0;
    int essarea,essharea,esshh,essh,essbase,esshbase;
    fp=fopen("quadratini.txt","r");
    if(fp==NULL){                                                                   //CONTROLLO CHE IL FILE SIA STATO APERTO IN MODO CORRETTO
        printf("errore nell'apertura del file");
        return -1;
    }
    LeggiMatrice(M,&nr,&nc);                                                        //CHIAMO LA FUNZIONE PER LEGGERE LA MATRICE
    for(int r=0;r<nr;r++){
        for(int c=0;c<nc;c++){
                if(RiconosciRegione(M,nr,nc,r,c,&b,&h)){                            //SE ESISTE IL RETTANGOLO
                    printf("\nbase: %d   -- altezza: %d    -- area: %d",b,h,b*h);
                    if((b*h)>areamax){                                              //CONTROLLO CHE TALE RETTANGOLO ABBIA LA BASE MASSIMA
                        areamax=(b*h);
                        essarea=r+1;                                                  //SEGNO GLI ESTREMI DELL'AREA MASSIMA
                        essharea=r+h;
                    }
                    if(b>bmax){                                                     //CONTROLLO CHE TALE RETTANGOLO ABBIA LA BASE MASSIMA
                        bmax=b;
                        essbase=r+1;                                                  //SEGNO GLI ESTREMI DELLA BASE MASSIMA
                        esshbase=r+h;
                    }
                    if(h>hmax){                                                     //CONTROLLO CHE TALE RETTANGOLO ABBIA LA BASE MASSIMA
                        hmax=h;
                        essh=r+1;                                                     //SEGNO GLI ESTREMI DELL'ALTEZZA MASSIMA
                        esshh=r+h;
                    }
                }
}}
    printf("\n\n\n-->base max: %d e ha estremi <%d , %d>",bmax,essbase,esshbase);
    printf("\n-->altezza max: %d e ha estremi <%d , %d>",hmax,essh,esshh);
    printf("\n-->area max: %d e ha estremi <%d , %d>",areamax,essarea,essharea);
    fclose(fp);
    return 0;
}
