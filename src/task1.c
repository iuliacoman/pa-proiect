#include "task1.h"

//cream un nod si il adaugam in lista
void addAtEnd ( Node ** head , double val){
Node * newNode = ( Node *) malloc ( sizeof ( Node ));
newNode->valoare = val; 
newNode->next=NULL;
newNode->randament=0.0;
if (* head == NULL ) {
    *head = newNode;
}
else { 
Node *aux = * head ;
while (aux->next != NULL ) aux = aux->next ;
//calculam randamentul conform formulei
newNode->randament = (newNode->valoare - aux->valoare)/aux->valoare;
aux->next=newNode;
newNode->next=NULL; 
}
}


//calculam randamentul mediu
double randamentMediu ( Node *head, int N )
{
    if(head==NULL || N<1) return 0;
    double suma=0;
    Node *curent = head->next;
    while(curent!=NULL)
    {
        suma=suma+curent->randament;
        curent=curent->next;
    }
    return suma/(double)(N-1);
}

//calculam volatilitatea
double volat (Node *head, int N, double mu)
{
    if(head==NULL || N<1) return 0;

    double suma=0;
    Node *curent=head->next;
    //calculam suma patratelor diferentelor dintre Rt si mu
    while(curent!=NULL)
    {
        suma=suma + (curent->randament - mu)*(curent->randament - mu);
        curent=curent->next;
    }

    //calculam formula finala
    return sqrt(suma/(double)(N-1));
}

void freeList(Node *head)
{

    while(head!=NULL) {
        Node *aux=head;
        head=head->next;
        free(aux);
    }
}

void rezolvareTask1(const char *f1, const char *f2)
{
    FILE *fin = fopen(f1,"r");
    FILE *fout = fopen(f2,"w");
    if (!fin || !fout) return;

    int N;
    if (fscanf(fin,"%d",&N)!=1) {
        fclose(fin); 
        fclose(fout);
        return;
    }
    Node *head=NULL;

    //citim valorile si le adaugam in lista
    for (int i=0; i < N; i++)
    {
        double val;
        if (fscanf(fin, "%lf", &val)==1)
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
}