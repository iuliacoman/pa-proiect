#include "task4.h"


long cmmdc (long a, long b){
    a = labs(a);
    b = labs(b);
    while(b != 0){
        long r = a%b;
        a = b;
        b = r;

    }
    return a;
}

fractie simplificare(fractie f){
    if (f.numarator == 0) {
        f.numitor = 1;
        return f;
    }
    long div = cmmdc(f.numarator, f.numitor);
    f.numarator /= div;
    f.numitor /= div;
    return f;
}

fractie adunare(fractie f1, fractie f2){
    fractie s;
    s.numitor = f1.numitor * f2.numitor;
    s.numarator = f1.numarator * f2.numitor + f2.numarator * f1.numitor;
    return simplificare(s);
}

fractie inmultire(fractie f1, fractie f2){
    fractie i;
    i.numitor = f1.numitor * f2.numitor;
    i.numarator = f1.numarator * f2.numarator;
    return simplificare(i);
}

// Funcție care gaseste indexul unei stări în vectorul de stări sau returneaza -1 dacă e complet nouă
int cautaStare(const int vector_stari[], int nr_stari, int id_cautat) {
    for (int i = 0; i < nr_stari; i++) {
        if (vector_stari[i] == id_cautat) {
            return i;
        }
    }
    return -1;
}


//Sortare crescătoare în vectorul de stări pentru ca ele să fie ordonate în matrice
void sorteazaStari(int vector_stari[], int nr_stari) {
    for (int i = 0; i < nr_stari - 1; i++) {
        for (int j = i + 1; j < nr_stari; j++) {
            if (vector_stari[i] > vector_stari[j]) {
                int aux = vector_stari[i];
                vector_stari[i] = vector_stari[j];
                vector_stari[j] = aux;
            }
        }
    }
}


//Construirea matricei de adiacență pentru a stoca numărul de tranziții
Graph * create_graph (int nrVf) {
    int i;
    Graph *g = ( Graph *) malloc ( sizeof ( Graph ));
    if (g== NULL ) {
    printf (" memerror "); return NULL ;}
    g->V = nrVf;
    //alocăm liniile matricei de adiacență
    g->a = ( int **) malloc (g->V* sizeof (int *));
    for (i=0;i<g->V;i++)
    g->a[i] = (int *) calloc (g->V, sizeof (int ));
    if (g->a== NULL ) {
    printf (" memerror "); return NULL ;}
    g->E = 0;
    return g;
}


// Funcția de populare a grafului
int tranzitii(const double preturi[], int N, double d, int stari_unice[], Graph *g, int id_start, int id_target) {
    int nr_stari = 0;
    // Gasim toate starile distincte (intervalele)
    for (int i = 0; i < N; i++) {
        int id_stare = (int)floor(preturi[i] / d);
        if (cautaStare(stari_unice, nr_stari, id_stare) == -1) {
            stari_unice[nr_stari++] = id_stare;
        }
    }

    // Ne asigurăm că stările de start și target sunt incluse în vector
    if (cautaStare(stari_unice, nr_stari, id_start) == -1) {
        stari_unice[nr_stari++] = id_start;
    }
    if (cautaStare(stari_unice, nr_stari, id_target) == -1) {
        stari_unice[nr_stari++] = id_target;
    }

    // Sortăm vectorul pentru ca indicii din matrice să aibă o ordine crescătoare
    sorteazaStari(stari_unice, nr_stari);

    //Numărăm tranzițiile consecutive din istoric
    for (int i = 0; i < N - 1; i++) {
        int stCurenta = (int)floor(preturi[i] / d);
        int stUrm = (int)floor(preturi[i + 1] / d);

        // Aflăm poziția lor în matricea sortată
        int x1 = cautaStare(stari_unice, nr_stari, stCurenta);
        int  x2 = cautaStare(stari_unice, nr_stari, stUrm);

        if (g->a[x1][x2] == 0) {
            g->E++; 
        // Am descoperit o legătură nouă între două stări
        }
        g->a[x1][x2]++;
    // Incrementăm numărul de tranziții pe această relație 
    }
    // Returnăm numărul total de stări unice găsite
    return nr_stari;
}

void simulareMarkov(Graph *g, int stari_unice[], int nr_stari, int K, int idx_start, int idx_target, FILE *fout) {
    // Alocăm doi vectori de fracții
    fractie *prob_ieri = (fractie *)malloc(nr_stari * sizeof(fractie));
    fractie *prob_azi = (fractie *)malloc(nr_stari * sizeof(fractie));

    // Starea initiala (Ziua 0)
    for (int i = 0; i < nr_stari; i++) {
        if (i == idx_start) 
            prob_ieri[i].numarator = 1;
        else 
            prob_ieri[i].numarator = 0;
        prob_ieri[i].numitor = 1;
    }

    // Parcurgerea celor K zile
    for (int zi = 1; zi <= K; zi++) {
        //adăugăm linie nouă doar între zile
        if(zi > 1)
            fprintf(fout,"\n");

        // Afișăm probabilitatea curentă de a fi în starea target în ziua analizată
        if (idx_target != -1 && prob_ieri[idx_target].numarator > 0) {
            if (prob_ieri[idx_target].numarator == prob_ieri[idx_target].numitor) {
                fprintf(fout, "1");
            } else {
                fprintf(fout, "%ld/%ld", prob_ieri[idx_target].numarator, prob_ieri[idx_target].numitor);
            }
        } else {
            fprintf(fout, "0");
            //Dacă numărătorul e 0 sau starea e invalidă, probabilitatea e 0
        }

        // Resetăm vectorul zilei curente (prob_azi) cu 0 înainte de a calcula noile propagări
        for (int i = 0; i < nr_stari; i++) {
            prob_azi[i].numarator = 0;
            prob_azi[i].numitor = 1;
        }

        // Propagarea probabilitatilor folosind liniile si coloanele matricei
        for (int i = 0; i < nr_stari; i++) {
            if (prob_ieri[i].numarator > 0) {
                // Calculam totalul iesirilor din nodul curent i (suma liniei i)
                int total_iesiri_nod = 0;
                for (int j = 0; j < nr_stari; j++) {
                    total_iesiri_nod += g->a[i][j];
                }

                if (total_iesiri_nod > 0) {
                    // Pentru fiecare stare vecină j în care se putea pleca din i
                    for (int j = 0; j < nr_stari; j++) {
                        if (g->a[i][j] > 0) { // Daca exista muchie de la i la j
                            fractie prob_muchie;
                            prob_muchie.numarator = g->a[i][j];
                            prob_muchie.numitor = total_iesiri_nod;

                            // Șansa de a fi fost ieri în i * Șansa de a trece din i în j
                            fractie drum = inmultire(prob_ieri[i], prob_muchie);
                            //Adunam acest drum la probabilitatea totală a stării j pentru azi
                            prob_azi[j] = adunare(prob_azi[j], drum);
                        }
                    }
                }else
                    prob_azi[i] = adunare(prob_azi[i], prob_ieri[i]);
                    //Dacă din starea i nu mai pleacă nicio tranziție în istoric, probabilitatea rămâne în starea i
            }
        }
        
        // Rotirea vectorilor pentru urmatoarea zi
        //Datele calculate pentru azi devin baza de plecare pentru ieri în următoarea zi
        for (int i = 0; i < nr_stari; i++) {
            prob_ieri[i] = prob_azi[i];
        }
    }

    free(prob_ieri);
    free(prob_azi);
}


void rezolvareTask4(const char *f1, const char *f2) {
    FILE *fin = fopen(f1, "r");
    FILE *fout = fopen(f2, "w");

    if (!fin || !fout) {
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return;
    }

    int N, K;
    double d, P_start, P_target;

    //Citirea parametrilor
    if (fscanf(fin, "%d", &N) != 1) { fclose(fin); fclose(fout); return; }
    if (fscanf(fin, "%lf", &d) != 1) { fclose(fin); fclose(fout); return; }
    if (fscanf(fin, "%d", &K) != 1) { fclose(fin); fclose(fout); return; }
    if (fscanf(fin, "%lf", &P_start) != 1) { fclose(fin); fclose(fout); return; }
    if (fscanf(fin, "%lf", &P_target) != 1) { fclose(fin); fclose(fout); return; }

    // Alocarea și citirea vectorului cu cele N prețuri istorice din piață
    double *preturi = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%lf", &preturi[i]);
    }

    // Calculăm ID-urile stărilor de start și target
    int id_start = (int)floor(P_start / d);
    int id_target = (int)floor(P_target / d);

    // Initializăm structurile
    // Alocăm N+2 spații în cel mai rău caz (N prețuri din istoric + stările start/target)
    int *stari_unice = (int *)malloc((N+2) * sizeof(int));
    Graph *g = create_graph(N+2); // In cel mai rau caz avem N+2 stari distincte

    // Populăm graful cu numărul de tranziții reale și aflăm numărul final de stări unice ordonate
    int nr_stari = tranzitii(preturi, N, d, stari_unice, g, id_start, id_target);

    // Identificăm indicii pe care s-au așezat stările respective în matricea sortată
    int idx_start = cautaStare(stari_unice, nr_stari, id_start);
    int idx_target = cautaStare(stari_unice, nr_stari, id_target);

    simulareMarkov(g, stari_unice, nr_stari, K, idx_start, idx_target, fout);

    // Eliberare memorie si curatare matrice
    for (int i = 0; i < g->V; i++) {
        free(g->a[i]);
    }
    free(g->a);
    free(g);
    free(stari_unice);
    free(preturi);
    
    fclose(fin);
    fclose(fout);
}

