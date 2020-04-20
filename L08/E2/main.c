#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char colore;
    int n;
}tubo;

typedef struct
{
    tubo a;
    tubo b;
}tessera;
typedef struct
{
    int numeroTile;
    int rotazione;
}scacchiera;
typedef struct
{
    int r,c;
    scacchiera **tess;
}board_t;

tessera *leggiTiles(int *nTiles)
{
    FILE* fTiles;
    int i;
    fTiles=fopen("tiles.txt","r");
    fscanf(fTiles,"%d",nTiles);
    tessera *tiles=malloc((*nTiles)*sizeof(tessera ));
    printf("Abbiamo n.%d tiles\n\n",*nTiles);
    for(i=0;i<(*nTiles);i++)
    {
        fscanf(fTiles,"\n%c %d %c %d", &(tiles[i].a.colore), &(tiles[i].a.n), &(tiles[i].b.colore), &(tiles[i].b.n));
    }
    fclose(fTiles);
    return tiles;
}

board_t leggiBoard(int *nonAssegnati)
{
    FILE* fBoard;
    fBoard=fopen("board.txt","r");
    board_t board;
    fscanf(fBoard,"%d %d",&(board.r),&(board.c));
    (board.tess)=malloc((board.r)*sizeof(scacchiera *));
    char tess[6];
    for(int i=0;i<board.r;i++)  board.tess[i]=malloc((board.c)*sizeof(scacchiera));
    for(int i=0;i<board.r;i++)
    {
        for(int j=0;j<(board.c);j++)
        {
            fscanf(fBoard,"%s",tess);
            sscanf(tess,"%d/%d",&board.tess[i][j].numeroTile,&board.tess[i][j].rotazione);
            if(board.tess[i][j].numeroTile==(-1)) (*nonAssegnati)++;
        }
    }
    fclose(fBoard);
    return board;
}


int calcoloPunti(scacchiera *solR,board_t board,tessera *tiles)
{
    int k=0,flag=0,punti=0,i,j;
    board_t boardNew;
    (boardNew.tess)=malloc((board.r)*sizeof(scacchiera *));
    for(int i=0;i<board.r;i++)  boardNew.tess[i]=malloc((board.c)*sizeof(scacchiera));
    for(i=0;i<board.r;i++)
    {
        for(j=0;j<board.c;j++)
        {
            if((board.tess[i][j].numeroTile==(-1))&&(board.tess[i][j].rotazione==(-1)))
            {
                boardNew.tess[i][j].numeroTile=solR[k].numeroTile;
                boardNew.tess[i][j].rotazione=solR[k].rotazione;
                k++;
            }
            else
            {
                boardNew.tess[i][j].numeroTile=board.tess[i][j].numeroTile;
                boardNew.tess[i][j].rotazione=board.tess[i][j].rotazione;
            }
        }
    }
    for(i=0;i<board.r;i++)
    {
        for(j=0;j<(board.c-1);j++)
        {
            if(boardNew.tess[i][j].rotazione==1)
            {
                if(boardNew.tess[i][j+1].rotazione==1)
                {
                    if((tiles[boardNew.tess[i][j].numeroTile].b.colore)!=(tiles[boardNew.tess[i][j+1].numeroTile].b.colore))   flag=1;
                }
                else
                {
                    if((tiles[boardNew.tess[i][j].numeroTile].b.colore)!=(tiles[boardNew.tess[i][j+1].numeroTile].a.colore))   flag=1;
                }
            }
            else
            {
                if(boardNew.tess[i][j+1].rotazione==1)
                {
                    if((tiles[boardNew.tess[i][j].numeroTile].a.colore)!=(tiles[boardNew.tess[i][j+1].numeroTile].b.colore))   flag=1;
                }
                else
                {
                    if((tiles[boardNew.tess[i][j].numeroTile].a.colore)!=(tiles[boardNew.tess[i][j+1].numeroTile].a.colore))   flag=1;
                }
            }
            if(flag==1) break;
        }
        if(flag==0)
        {
            for(j=0;j<board.c;j++)
            {
                if(boardNew.tess[i][j].rotazione==1)
                    punti=punti+tiles[boardNew.tess[i][j].numeroTile].b.n;
                else
                    punti=punti+tiles[boardNew.tess[i][j].numeroTile].a.n;
            }
        }
    }
    flag=0;
    for(i=0;i<board.c;i++)
    {
        for(j=0;j<(board.r-1);j++)
        {
            if(boardNew.tess[j][i].rotazione==1)
            {
                if(boardNew.tess[j+1][i].rotazione==1)
                {
                    if((tiles[boardNew.tess[j][i].numeroTile].a.colore)!=(tiles[boardNew.tess[j+1][i].numeroTile].a.colore))   flag=1;
                }
                else
                {
                    if((tiles[boardNew.tess[j][i].numeroTile].a.colore)!=(tiles[boardNew.tess[j+1][i].numeroTile].b.colore))   flag=1;
                }
            }
            else
            {
                if(boardNew.tess[j+1][i].rotazione==1)
                {
                    if((tiles[boardNew.tess[j][i].numeroTile].b.colore)!=(tiles[boardNew.tess[j+1][i].numeroTile].a.colore))   flag=1;
                }
                else
                {
                    if((tiles[boardNew.tess[j][i].numeroTile].b.colore)!=(tiles[boardNew.tess[j+1][i].numeroTile].b.colore))   flag=1;
                }
            }
            if(flag==1) break;
        }
        if(flag==0)
        {
            for(j=0;j<board.r;j++)
            {
                if(boardNew.tess[j][i].rotazione==1)
                    punti=punti+tiles[boardNew.tess[j][i].numeroTile].a.n;
                else
                    punti=punti+tiles[boardNew.tess[j][i].numeroTile].b.n;
            }
        }
    }

    for(i=0;i<board.r;i++)  free(boardNew.tess[i]);
    free(boardNew.tess);
    return punti;
}

void princ_molt(scacchiera *sol,scacchiera *solR,int pos2,int pos,board_t board,tessera *tiles,int *maxPunti,scacchiera *solMax)
{
    int i;
    if(pos2>=pos)
    {
        int punti=calcoloPunti(solR,board,tiles);
        if(punti>(*maxPunti))
        {
            (*maxPunti)=punti;
            for(int i=0;i<pos;i++)
            {
                solMax[i].numeroTile=solR[i].numeroTile;
                solMax[i].rotazione=solR[i].rotazione;
            }
        }
        return;
    }
    for(i=0;i<=1;i++)
    {
        solR[pos2].numeroTile=sol[pos2].numeroTile;
        solR[pos2].rotazione=i;
        princ_molt(sol,solR,pos2+1,pos,board,tiles,maxPunti,solMax);
    }
    return ;
}
int disp(scacchiera *sol,int *mark,int count,int nTiles,int pos,int nonAssegnati,int assegnati[6],int k,board_t board,tessera *tiles,int *maxPunti,scacchiera *solMax)
{
    int i,flag=0;
    if(pos>=nonAssegnati)
    {
        int pos2=0;
        scacchiera *solR=malloc(nonAssegnati*sizeof(scacchiera));
        princ_molt(sol,solR,pos2,pos,board,tiles,maxPunti,solMax);
        free(solR);
        return count+1;
    }
    for(i=0;i<nTiles;i++)
    {
        for(int j=0;j<k;j++)
        {
            if(i==assegnati[j]) flag++;
        }
        if(mark[i]==0 && flag==0)
        {
            mark[i]=1;
            (sol[pos]).numeroTile=i;
            (sol[pos]).rotazione=0;
            count=disp(sol,mark,count,nTiles,pos+1,nonAssegnati,assegnati,k,board,tiles,maxPunti,solMax);
            mark[i]=0;
        }
        flag=0;
    }
    return count;
}
int main()
{
    int nTiles,k=0,nonAssegnati=0,maxPunti=0,count=0,pos=0;
    tessera *tiles=leggiTiles(&nTiles);
    board_t board= leggiBoard(&nonAssegnati);
    int *assegnati=malloc((board.r*board.c-nonAssegnati)*sizeof(int));
    for(int i=0;i<board.r;i++)
    {
        for(int j=0;j<board.c;j++)
        {
            printf("%d/%d ",board.tess[i][j].numeroTile,board.tess[i][j].rotazione);
            if(board.tess[i][j].numeroTile!=(-1))
            {
                assegnati[k]=board.tess[i][j].numeroTile;
                k++;
            }
        }
        printf("\n\n");
    }
    scacchiera *sol=malloc(nonAssegnati*sizeof(scacchiera));
    scacchiera *solMax=malloc(nonAssegnati*sizeof(scacchiera));
    int mark[nTiles];
    for(int i=0;i<nTiles;i++)   mark[i]=0;
    count=disp(sol,mark,count,nTiles,pos,nonAssegnati,assegnati,k,board,tiles,&maxPunti,solMax);
    free(sol);
    free(assegnati);
    for(int i=0;i<board.r;i++)  free(board.tess[i]);
    free(board.tess);
    free(tiles);
    printf("\n\n--> La soluzione migliore ha n.%d punti ed e' la seguente:\n\n",maxPunti);
    for(int i=0;i<(nonAssegnati);i++)
    {
        printf("%d/%d ",solMax[i].numeroTile,solMax[i].rotazione);
    }
    free(solMax);
    printf("\n\n");
    return 0;
}
