#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

//implementare stiva
struct Elem{
    double pret;
    struct Elem * next;
};
typedef struct Elem Node;

int isEmpty(Node *top){
    return top==NULL;
}

//adaugare element in stiva
void push ( Node ** top , double val) {
    Node * newNode =( Node *) malloc ( sizeof ( Node ));
    newNode->pret=val;
    newNode->next = *top;
    *top= newNode ;
}

//eliminare element din stiva
double pop( Node ** top) {
if ( isEmpty (* top )) return INT_MIN ;
Node * temp =(* top );
double aux=temp->pret;
*top =(* top)->next;
free ( temp );
return aux;
}

//creare coada pentru oportunitatile de arbitraj
typedef struct{
    int zi;
    double dif;
    char nume[30];
}Data;

struct qElem {
    Data val;
    struct qElem * next ;
};
typedef struct qElem qNode ;

struct Q{
    qNode *front ,* rear ;
};
typedef struct Q Queue ;

Queue * createQueue (){
    Queue *q;
    q=( Queue *) malloc ( sizeof ( Queue ));
    if (q== NULL ) return NULL ;
    q->front =q->rear = NULL ;
    return q;
}

void enqueue (Queue *q, int zi, double dif, char *nume)
{
    qNode *newNode=(qNode*)malloc(sizeof(qNode));
    newNode->val.zi=zi;
    newNode->val.dif=dif;
    strcpy(newNode->val.nume,nume);
    newNode->next=NULL;
    if(q->rear==NULL){
        q->front=q->rear=newNode;
    }
    else {
        q->rear->next=newNode;
        q->rear=newNode;
    }
}

//verificam cele trei cazuri de oportunitate de arbitraj
void verificare(int zi, double p1, double p2, double p3, char *nume1, char *nume2, char *nume3, Queue *q){
    if(p1==p2 && p1!=p3)
        enqueue(q,zi,fabs(p3-p1),nume3);
    else if(p1==p3 && p1!=p2)
        enqueue(q,zi,fabs(p2-p1),nume2);
    else if(p2==p3 && p1!=p2) 
        enqueue(q,zi,fabs(p1-p2),nume1);
}

int main(int argc, char *argv[])
{
    if(argc<3) return 1;

    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen(argv[2],"w");
    if(!fin || !fout) return 1;

    char nume1[30], nume2[30], nume3[30];
    fscanf(fin, "%s %s %s", nume1, nume2, nume3);

    Node *s1=NULL, *s2=NULL, *s3=NULL;
    double p1, p2, p3;
    int totZile=0;

    while(fscanf(fin,"%lf %lf %lf", &p1, &p2, &p3)==3){
        push(&s1,p1);
        push(&s2,p2);
        push(&s3,p3);
        totZile++;
    }

    Queue q={NULL,NULL};

    //parcurgem stiva de la ultima zi pana la prima zi
    for(int i=totZile;i>=1;i--){
        double v1=pop(&s1);
        double v2=pop(&s2);
        double v3=pop(&s3);
        verificare(i,v1,v2,v3,nume1,nume2,nume3,&q);
    }

    //afisam rezultatele in coada
    while(q.front!=NULL){
        fprintf(fout, "ziua %d - %.0f - %s\n", q.front->val.zi, q.front->val.dif, q.front->val.nume);
        qNode *temp=q.front;
        q.front=q.front->next;
        free(temp);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}