#include "task2.h"
#include<ctype.h>


int isEmpty(const StackNode *top){
    return top==NULL;
}

//adaugare element in stiva
void push ( StackNode ** top , double val) {
    StackNode * newNode =( StackNode *) malloc ( sizeof ( StackNode ));
    newNode->pret=val;
    newNode->next = *top;
    *top= newNode ;
}

//eliminare element din stiva
double pop( StackNode ** top) {
if ( isEmpty (* top )) return INT_MIN ;
StackNode * temp =(* top );
double aux=temp->pret;
*top =(* top)->next;
free ( temp );
return aux;
}


/*Queue * createQueue (){
    Queue *q;
    q=( Queue *) malloc ( sizeof ( Queue ));
    if (q== NULL ) return NULL ;
    q->front =q->rear = NULL ;
    return q;
}*/

void enqueue (Queue *q, int zi, double dif, const char *nume)
{
    qNode *newNode=(qNode*)malloc(sizeof(qNode));
    newNode->val.zi=zi;
    newNode->val.dif=dif;
    strcpy(newNode->val.nume,nume);
    newNode->next=NULL;
    if (q->rear==NULL){
        q->front=q->rear=newNode;
    }
    else {
        q->rear->next=newNode;
        q->rear=newNode;
    }
}

//verificam cele trei cazuri de oportunitate de arbitraj
void verificare(int zi, double p1, double p2, double p3, const char *nume1, const char *nume2, const char *nume3, Queue *q){
    if (fabs(p1 - p2) < 0.001 && fabs(p1 - p3) > 0.001)
        enqueue(q,zi,fabs(p3-p1),nume3);
    else if (fabs(p1 - p3) < 0.001 && fabs(p1 - p2) > 0.001)
        enqueue(q,zi,fabs(p2-p1),nume2);
    else if (fabs(p2 - p3) < 0.001 && fabs(p1 - p2) > 0.001) 
        enqueue(q,zi,fabs(p1-p2),nume1);
}

void citirePiata(FILE *fin, StackNode **top){
    char buffer[50];
    while(1){
        long pos = ftell(fin);
        if (fscanf(fin,"%49s",buffer)==EOF) break;
        if (buffer[0] >= '0' && buffer[0] <= '9')
            push(top,atof(buffer));
        else
            {
                fseek(fin, pos, SEEK_SET);
                break;
            }
    }
}

void rezolvareTask2(const char *inputFile, const char *outputFile){
    FILE *fin=fopen(inputFile,"r");
    FILE *fout=fopen(outputFile,"a");
    if (!fin || !fout) {
        printf("eroare!!!!");
        return;}

    char nume1[30], nume2[30], nume3[30];
    StackNode *s1=NULL, *s2=NULL, *s3=NULL;
    //citire piata 1
    if (fscanf(fin," %29[^\n]",nume1)!=EOF)
        citirePiata(fin,&s1);
    //citire piata 2
    if (fscanf(fin," %29[^\n]",nume2)!=EOF)
        citirePiata(fin,&s2);
    //citire piata 3
    if (fscanf(fin," %29[^\n]",nume3)!=EOF)
        citirePiata(fin,&s3);

    Queue q={NULL,NULL};
    int zi=1;
    //parcurgem stiva 
    while (s1!=NULL && s2!=NULL && s3!=NULL){
        double p1=pop(&s1);
        double p2=pop(&s2);
        double p3=pop(&s3);
        verificare(zi,p1,p2,p3,nume1,nume2,nume3,&q);
        zi++;
    }

    //afisam rezultatele in coada
    while (q.front!=NULL){
        fprintf(fout, "ziua %d - %.2f - %s\n", q.front->val.zi, q.front->val.dif, q.front->val.nume);
        qNode *temp=q.front;
        q.front=q.front->next;
        free(temp);
    }

    while (s1) pop(&s1);
    while (s2) pop(&s2);
    while (s3) pop(&s3);
    fclose(fin);
    fclose(fout);

}

