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

int isEmpty(Node *top);
void push(Node **top, double val);
double pop(Node **top);
Queue *createQueue();
void enqueue(Queue *q, int zi, double dif, char *nume);
void verificare(int zi, double p1, double p2, double p3, char *nume1, char *nume2, char *nume3, Queue *q);
void citirePiata(FILE *fin, Node **top, char *nume);
void rezolvareTask2(char *inputFile, char *outputFile);