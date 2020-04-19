#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
int cntrlKcore(Graph g,int *sol,int k);
void kcoreR(Graph g,int k,int pos,int* sol,int* best,int *max,int* degree);
void kcore(Graph g);
void jEdge(Graph g);
#endif
