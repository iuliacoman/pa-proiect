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