#include "task3.h"

TreeNode* createNode(int depth) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) return NULL;
    node->stocks = NULL; 
    node->left = NULL;
    node->right = NULL;
    node->depth = depth; 
    return node;
}

void addStockToList(StockList **head, const char *symbol) {
    StockList *newNode = (StockList*)malloc(sizeof(StockList));
    strcpy(newNode->symbol, symbol);
    newNode->next = *head;
    *head = newNode;
}

double** citireActiuni( FILE *fin, int *z, char s[10][MAX_SYM] ){
    char line[256];
    //char s[10][MAX_SYM]; // aici vor fi stocate datele citite de la tastatura
    if( fgets(line, sizeof(line), fin) ){
        const char *p = strtok(line, ", \n");
        int i=0;
        while(p!=NULL && i < 10){
            strncpy(s[i], p, MAX_SYM - 1);
            s[i][MAX_SYM - 1] = '\0';
            p = strtok(NULL, ", \n");
            i++;
        }
    }
    int nrZile=0;
    int cap=10;
    double **prices = malloc( 10 * sizeof(double*));
    while (1) {
        if (nrZile >= cap) {
            cap *= 2;
            double **temp = realloc(prices, cap * sizeof(double*));
            if (temp == NULL) {
                for(int i = 0; i < nrZile; i++) 
                    free(prices[i]);
                free(prices);
                return NULL; 
    }
            prices = temp;
        
        }
    double *row = malloc( 10 * sizeof(double));
    int k=0;
    //citim preturile de pe randul curent
    for(int i=0; i<10; i++){
        if(fscanf(fin, "%lf", &row[i]) == 1){
            k++;
            fgetc(fin);
        }
    }
    if(k==10){
        prices[nrZile] = row;
        nrZile++;
    }
    else{
        free(row);
        break;
    }
}
    *z = nrZile;
    return prices;
}


void construireArbore(TreeNode *root, double **prices, int nrZile, char s[10][MAX_SYM]) {
    //parcurgem fiecare coloana (actiune)
    for (int j = 0; j < 10; j++) { 
        TreeNode *current = root;
        for (int i = 1; i < nrZile; i++) {
            if (prices[i][j] < prices[i-1][j]) { 
                if (!current->left) current->left = createNode(i);
                current = current->left;
            } else { 
                if (!current->right) current->right = createNode(i);
                current = current->right;
            }
            addStockToList(&(current->stocks), s[j]); 
        }
    }
}

void oglindit (double **prices, int nrZile, const char s[10][MAX_SYM], TreeNode *root, FILE *fout){
    for(int i = 0; i < 10; i++){
        TreeNode *current  =root;
        int gasit = 1;
        for( int j=1; j < nrZile; j++){
            if(prices[j][i] < prices[j-1][i]){
                if(current->right != NULL)
                    current=current->right;
                else{
                    gasit=0;
                    break;
                }
            }
            else{
                if(current->left != NULL)
                    current=current->left;
                else{
                    gasit=0;
                    break;
                }
            }
        }
        if(gasit == 1 && current->stocks != NULL){
            StockList *t = current->stocks;
            while(t!=NULL){
                fprintf(fout, "%s-%s\n", s[i], t->symbol);
                t=t->next;
            }
        }

    }

}


void freeTree(TreeNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    StockList *it = root->stocks;
    while (it) {
        StockList *tmp = it;
        it = it->next;
        free(tmp);
    }
    free(root);
}

void rezolvareTask3(const char *f1, const char *f2){
    FILE *fin = fopen(f1, "r");
    FILE *fout = fopen(f2, "w");
    if(fin == NULL || fout == NULL){
        printf("Eroare la deschiderea fisierelor pentru task 3 \n");
        return;
    }

    char s[10][MAX_SYM];
    int nrZile = 0;
    double **prices = citireActiuni(fin, &nrZile, s);
    TreeNode *root = createNode(0);
    construireArbore(root, prices, nrZile, s);
    oglindit(prices, nrZile, s, root, fout);
    for(int i=0; i<nrZile; i++)
        free(prices[i]);
    free(prices);
    freeTree(root);
    fclose(fin);
    fclose(fout);
}