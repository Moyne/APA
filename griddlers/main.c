#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nGroups;
    int *nCells;
}group_t;
typedef struct{
    int r,c;
    group_t *groupR;
    group_t *groupC;
}griddler_t;
griddler_t *readFile(){
    int i;
    griddler_t *griddler=malloc(sizeof(*griddler));
    FILE* fp=fopen("inf.txt","r");
    fscanf(fp,"%d",&griddler->r);
    (griddler->groupR)=malloc(griddler->r*sizeof(*griddler->groupR));
    for(i=0;i<griddler->r;i++){
        fscanf(fp,"%d",&griddler->groupR[i].nGroups);
        griddler->groupR[i].nCells=malloc(griddler->groupR[i].nGroups* sizeof(int));
        for (int j = 0; j < griddler->groupR[i].nGroups; ++j) {
            fscanf(fp,"%d",&griddler->groupR[i].nCells[j]);
        }
    }
    fscanf(fp,"%d",&griddler->c);
    (griddler->groupC)=malloc(griddler->c*sizeof(*griddler->groupC));
    for(i=0;i<griddler->c;i++){
        fscanf(fp,"%d",&griddler->groupC[i].nGroups);
        griddler->groupC[i].nCells=malloc(griddler->groupC[i].nGroups* sizeof(int));
        for (int j = 0; j < griddler->groupC[i].nGroups; ++j) {
            fscanf(fp,"%d",&griddler->groupC[i].nCells[j]);
        }
    }
    fclose(fp);
    return griddler;
}

int check(int **sol,griddler_t *griddler){
    int r=0,c=0;
    for(int i=0;i<griddler->r;i++){
        r=0;
        for (int j = 0; j < griddler->c; j++) {
            if(j>0){
            if(sol[i][j]==1 && sol[i][j-1]!=1){
                for (int k = j; k < j+griddler->groupR[i].nCells[r]; k++) {
                    if(sol[i][k]==0)    return 0;
                }
                r++;
            }}
            else{
                if(sol[i][j]==1 ){
                    for (int k = j; k < j+griddler->groupR[i].nCells[r]; k++) {
                        if(sol[i][k]==0)    return 0;
                    }
                    r++;
                }
            }
        }
        if(r<griddler->groupR[i].nGroups)   return 0;
    }
    for(int i=0;i<griddler->c;i++){
        c=0;
        for (int j = 0; j < griddler->r; j++) {
            if(j>0){
            if(sol[j][i]==1 && sol[j-1][i]!=1){
                for (int k = j; k < j+griddler->groupC[i].nCells[c]; k++) {
                    if(sol[k][i]==0)    return 0;
                }
                c++;
            }}
            else{
                if(sol[j][i]==1 ){
                    for (int k = j; k < j+griddler->groupC[i].nCells[c]; k++) {
                        if(sol[k][i]==0)    return 0;
                    }
                    c++;
                }
            }
        }
        if(c<griddler->groupC[i].nGroups)   return 0;
    }
    return 1;
}
void poss(griddler_t *griddler,int **sol,int pos){
    if(pos>=griddler->r*griddler->c)
    {
        if(check(sol,griddler))
        {
            for (int i = 0; i < griddler->r; i++) {
                for (int j = 0; j < griddler->c; j++) {
                    printf("%d ",sol[i][j]);
                }
                printf("\n\n");
            }
        }
    }

    for(int i=0;i<griddler->r;i++){
        for(int j=0;j<griddler->c;j++){
            if(griddler->groupR[i].nGroups!=0 && griddler->groupC[j].nGroups!=0)
            {
                sol[i][j]=1;
                poss(griddler,sol,pos+1);
                sol[i][j]=0;
            }
            else{
                sol[i][j]=0;
                poss(griddler,sol,pos+1);
            }
        }
    }
}
int main() {
    griddler_t *griddler=readFile();
    int **sol;
    sol=malloc(griddler->r*sizeof(int *));
    for(int i=0;i<griddler->r;i++)  sol[i]=calloc(griddler->c, sizeof(int));
    FILE* fsol;
    fsol=fopen("solposs.txt","r");
    for(int i=0;i<griddler->r;i++){
        for (int j = 0; j < griddler->c; j++) {
            fscanf(fsol,"%d",&sol[i][j]);
        }
    }
    if(check(sol,griddler)) printf("SOLUZIONE CORRETTA");
    else    printf("SOLUZIONE SBAGLIATA");
    /*poss(griddler,sol,0);*/
    return 0;
}