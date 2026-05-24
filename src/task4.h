#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    long numarator;
    long numitor;
}fractie;

typedef struct{
    int nr;
    int iesiri;
    int vecini[100];
    int cost[100];
}stare;

typedef struct{
    int V;
    int E;
    int **a;
}Graph;

long cmmdc(long a, long b);
fractie simplificare(fractie f);
fractie adunare(fractie f1, fractie f2);
fractie inmultire(fractie f1, fractie f2);
int cautaStare(const int vector_stari[], int nr_stari, int id_cautat);
Graph * create_graph (int nrVf);
int tranzitii(const double preturi[], int N, double d, int stari_unice[], Graph *g, int id_start, int id_target);
void simulareMarkov(Graph *g, int stari_unice[], int nr_stari, int K, int idx_start, int idx_target, FILE *fout);
void rezolvareTask4(const char *f1, const char *f2);

