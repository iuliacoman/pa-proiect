#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SYM 8

typedef struct StockList {
    char symbol[MAX_SYM];
    struct StockList *next;
} StockList;

 typedef struct TreeNode {
    StockList *stocks;
    struct TreeNode *left; // aici se duc actiunile care scad
    struct TreeNode *right; // aici se duc actiunile care cresc
    int depth;
} TreeNode;

TreeNode* createNode(int depth);
void addStockToList(StockList **head, const char *symbol);
double** citireActiuni( FILE *fin, int *z, char s[10][MAX_SYM] );
void construireArbore(TreeNode *root, double **prices, int nrZile, char s[10][MAX_SYM]);
void freeTree(TreeNode *root);
int index_actiune(const char *symbol, const char s[10][MAX_SYM]);
void rezolvareTask3(const char *f1, const char *f2);
