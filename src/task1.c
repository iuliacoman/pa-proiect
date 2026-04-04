#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Node{
    double valoare;
    double randament;
    struct Node *next;
}Node;

//cream un nod si il adaugam in lista
void addAtEnd ( Node ** head , double val){
Node *aux = * head ;
Node * newNode = ( Node *) malloc ( sizeof ( Node ));
newNode->valoare = val; 
newNode->next=NULL;
newNode->randament=0.0;
if (* head == NULL ) {
    *head = newNode;
}
else { 
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
    return suma/N;
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
    return sqrt(suma/N);
}

void freeList(Node *head)
{
    Node *aux;
    while(head!=NULL) {
        aux=head;
        head=head->next;
        free(aux);
    }
}

int main(int argc, char *argv[])
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

    fprintf(fout, "%.3f\n", mu);
    fprintf(fout, "%.3f\n", sigma);
    fprintf(fout, "%.3f\n", sharpeRatio);

    freeList(head);
    fclose(fin);
    fclose(fout);
    return 0;
}