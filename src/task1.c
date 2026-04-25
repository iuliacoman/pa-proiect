#include "task1.h"

/*int main_t1(int argc, char *argv[])
{
    if(argc<3) return 1;
    FILE *fin = fopen(argv[1],"r");
    FILE *fout = fopen(argv[2],"w");
    if(!fin || !fout) return 1;

    int N;
    if(fscanf(fin,"%d",&N)!=1) return 1;

    Node *head=NULL;

    //citim valorile si le adaugam in lista
    for(int i=0;i<N;i++)
    {
        double val;
        if(fscanf(fin, "%lf", &val)==1)
            addAtEnd(&head, val);

    }

    double mu=randamentMediu(head,N);
    double sigma=volat(head, N, mu);
    double sharpeRatio = mu/sigma;

    fprintf(fout, "%.3f\n", (double)((long)(mu*1000))/1000.0);
    fprintf(fout, "%.3f\n", (double)((long)(sigma*1000))/1000.0);
    fprintf(fout, "%.3f\n", (double)((long)(sharpeRatio*1000))/1000.0);


    freeList(head);
    fclose(fin);
    fclose(fout);
    return 0;
}*/