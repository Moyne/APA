#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

#define MAXC 11

struct graph {int V; int E; int **madj; ST tab; };
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static int   pathR(Graph G, int v, int w, int *visited);
static int   pathRH(Graph G, int v, int w, int d, int *visited);
static void  bfs(Graph G, Edge e, int *time, int *pre, int *st);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2);
  }
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
  G->madj[w][v] = 1;
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w));

}

int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] == 1)
    G->E--;
  G->madj[v][w] = 0;
  G->madj[w][v] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
}


int cntrlKcore(Graph g,int *sol,int k){
    int i,j,cnt;
    for(i=0;i<g->V;i++){
        cnt=0;
        if(sol[i]==1){
            for(j=0;j<g->V;j++){
                if(sol[j]==1 && g->madj[i][j]==1)    cnt++;
            }
            if(cnt<k)   return 0;
        }
    }
    return 1;
}

void kcoreR(Graph g,int k,int pos,int* sol,int* best,int *max,int *degree){
    int i;
    if(pos>=g->V){
        int cnt=0;
        if(cntrlKcore(g,sol,k)){
            for(i=0;i<g->V;i++) if(sol[i]==1)   cnt++;
            if(cnt>*max){
                *max=cnt;
                for(i=0;i<g->V;i++) best[i]=sol[i];
            }
        }
        return;
    }
    if(degree[pos]>=k) {
        sol[pos] = 1;
        kcoreR(g, k, pos + 1, sol, best, max,degree);
    }
    sol[pos]=0;
    kcoreR(g,k,pos+1,sol,best,max,degree);
}


void kcore(Graph g){
    int k,max=0,pos=0;
    printf("\nSi scriva il grado ricercato:");
    scanf("%d",&k);
    int *sol=malloc(g->V* sizeof(int));
    int *best=malloc(g->V*sizeof(int));
    int *degree=calloc(g->V,sizeof(int));
    for(int i=0;i<g->V;i++){
        for(int z=0;z<g->V;z++) if(g->madj[i][z]==1)    degree[i]++;
    }
    kcoreR(g,k,pos,sol,best,&max,degree);
    if(max==0)  printf("\nNon esiste un %d -core nel seguente grafo.\n",k);
    else {
        printf("\nUn %d -core di %d elementi e' il seguente:\n", k, max);
        for (int i = 0; i < g->V; i++) if (best[i] == 1) printf("%s ", STsearchByIndex(g->tab, i));
    }
    free(degree);
    free(sol);
    free(best);
}


void cntrlEdgeR(Graph g,int v,int* visited,int*touched,Edge* solEdges,int j){
    int i;
    for(i=0;i<g->E-j;i++){
        if(solEdges[i].v==v && touched[solEdges[i].w]==0 && visited[solEdges[i].w]==0){
            touched[solEdges[i].w]=1;
            cntrlEdgeR(g,solEdges[i].w,visited,touched,solEdges,j);
        }
        if(solEdges[i].w==v && touched[solEdges[i].v]==0 && visited[solEdges[i].v]==0){
            touched[solEdges[i].v]=1;
            cntrlEdgeR(g,solEdges[i].v,visited,touched,solEdges,j);
        }
    }
    visited[v]=1;
}


int cntrlEdge(int j,Edge* solEdges,Graph g){
    int i,flag=0;
    int *visited=calloc(g->V, sizeof(int));
    int *touched=calloc(g->V, sizeof(int));
    touched[0]=1;
    cntrlEdgeR(g,j,visited,touched,solEdges,j);
    for(i=0;i<g->V;i++) if(visited[i]==0) flag=1;
    free(visited);
    free(touched);
    if(flag)    return 0;
    return 1;

}


int jEdgeR(Graph g,int j,Edge* solEdges,int* markEdges,int pos,Edge* Edges,int start){
    int i;
    if(pos>=g->E-j){
        if(!cntrlEdge(j,solEdges,g)){
            printf("\n\nUn sottoinsieme di n. %d archi che sconnette il grafo originale",j);
            for(i=0;i<g->E;i++){
                if(markEdges[i]==0) printf("\nARCO: %s - %s",STsearchByIndex(g->tab,Edges[i].v),STsearchByIndex(g->tab,Edges[i].w));
            }
            return 1;
        }
        return 0;
    }
    for(i=start;i<g->E;i++){
        solEdges[pos].v=Edges[i].v;
        solEdges[pos].w=Edges[i].w;
        markEdges[i]=1;
        if(jEdgeR(g,j,solEdges,markEdges,pos+1,Edges,i+1)) return 1;
        markEdges[i]=0;
    }
    return 0;
}


void jEdge(Graph g){
    Edge *Edges=malloc(g->E*sizeof(*Edges));
    GRAPHedges(g,Edges);
    int j,temp;
    printf("\n\nInserire il valore j di archi da rimuovere:");
    scanf("%d",&j);
    Edge *solEdges=malloc((g->E-j)*sizeof(*solEdges));
    int *markEdges=calloc(g->E, sizeof(int));
    temp=jEdgeR(g,j,solEdges,markEdges,0,Edges,0);
    free(markEdges);
    free(Edges);
    free(solEdges);
    if(temp==0)   printf("\n\nNon esiste un sottoinsieme con n. %d archi che sconnettono il grafo",j);
}