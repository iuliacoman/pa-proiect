#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
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

void citirePiata(FILE *fin, Node **top, char *nume){
    char buffer[50];
    while(fscanf(fin,"%s",buffer)!=EOF){
        if(isdigit(buffer[0]))
            push(top,atof(buffer));
        else
            {
                strcpy(nume,buffer);
                return;
            }
    }
    nume[0]='\0';
}

int main(int argc, char *argv[])
{
    if(argc<3) return 1;

    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen(argv[2],"w");
    if(!fin || !fout) return 1;

    char nume1[30], nume2[30], nume3[30], temp[30];

    Node *s1=NULL, *s2=NULL, *s3=NULL;
    //double p1, p2, p3;

    //citire piata 1
    if(fscanf(fin,"%s",nume1)!=EOF)
        citirePiata(fin,&s1,nume2);
    //citire piata 2 si 3
    citirePiata(fin,&s2,nume3);
    citirePiata(fin,&s3,temp);

    /*while(fscanf(fin,"%lf %lf %lf", &p1, &p2, &p3)==3){
        push(&s1,p1);
        push(&s2,p2);
        push(&s3,p3);
        totZile++;
    }*/

    Queue q={NULL,NULL};

    int zi=1;
    //parcurgem stiva 
    while(s1!=NULL && s2!=NULL && s3!=NULL){
        double p1=pop(&s1);
        double p2=pop(&s2);
        double p3=pop(&s3);
        verificare(zi,p1,p2,p3,nume1,nume2,nume3,&q);
        zi++;
    }

    //afisam rezultatele in coada
    while(q.front!=NULL){
        fprintf(fout, "ziua %d  %.3f  %s\n", q.front->val.zi, q.front->val.dif, q.front->val.nume);
        qNode *temp=q.front;
        q.front=q.front->next;
        free(temp);
    }

    fclose(fin);
    fclose(fout);
    while(s1) pop(&s1);
    while(s2) pop(&s2);
    while(s3) pop(&s3);
    return 0;
}