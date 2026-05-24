#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Node{
    double valoare;
    double randament;
    struct Node *next;
}Node;

void addAtEnd ( Node ** head , double val);
double randamentMediu ( Node *head, int N );
double volat (Node *head, int N, double mu);
void freeList(Node *head);
void rezolvareTask1(const char *f1, const char *f2);