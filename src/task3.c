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
    if (!newNode) return;
    strncpy(newNode->symbol, symbol, MAX_SYM - 1);
    newNode->symbol[MAX_SYM - 1] = '\0';
    newNode->next = NULL;

    // Inserăm mereu la FINAL pentru a păstra ordinea naturală din input
    if (*head == NULL) {
        *head = newNode;
    } else {
        StockList *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

double** citireActiuni(FILE *fin, int *z, char s[10][MAX_SYM]) {
    char line[256];
    if (fgets(line, sizeof(line), fin)) {
        const char *p = strtok(line, ", \n\r\t");
        int i = 0;
        while (p != NULL && i < 10) {
            strncpy(s[i], p, MAX_SYM - 1);
            s[i][MAX_SYM - 1] = '\0';
            p = strtok(NULL, ", \n\r\t");
            i++;
        }
    } else {
        *z = 0;
        return NULL;
    }

    int nrZile = 0;
    int cap = 10;
    double **prices = (double**)malloc(10 * sizeof(double*));
    if (!prices) { *z = 0; return NULL; }

    for (;;) {
        if (nrZile >= cap) {
            cap *= 2;
            double **temp = (double**)realloc(prices, cap * sizeof(double*));
            if (!temp) {
                for (int i = 0; i < nrZile; i++) free(prices[i]);
                free(prices);
                *z = 0;
                return NULL; 
            }
            prices = temp;
        }

        double *row = (double*)malloc(10 * sizeof(double));
        if (!row) {
            for (int i = 0; i < nrZile; i++) free(prices[i]);
            free(prices);
            *z = 0;
            return NULL;
        }

        int k = 0;
        for (int i = 0; i < 10; i++) {
            if (fscanf(fin, "%lf", &row[i]) == 1) {
                k++;
                int c = fgetc(fin);
                if (c == EOF) break;
            } else {
                break;
            }
        }

        if (k == 10) {
            prices[nrZile] = row;
            nrZile++;
        } else {
            free(row);
            break;
        }
    }
    *z = nrZile;
    return prices;
}

void construireArbore(TreeNode *root, double **prices, int nrZile, char s[10][MAX_SYM]) {
    if (!root || nrZile <= 1) return;
    
    for (int j = 0; j < 10; j++) { 
        TreeNode *current = root;
        for (int i = 1; i < nrZile; i++) {
            double d = prices[i][j] - prices[i-1][j];
            if (d <= 0) {
                if (!current->left) current->left = createNode(i);
                current = current->left;
            } else {
                if (!current->right) current->right = createNode(i);
                current = current->right;
            }
        }
        // Salvăm acțiunea DOAR în nodul frunză final
        addStockToList(&(current->stocks), s[j]); 
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

int index_actiune(const char *symbol, const char s[10][MAX_SYM]) {
    for (int i = 0; i < 10; i++) {
        if (strncmp(symbol, s[i], MAX_SYM) == 0) {
            return i;
        }
    }
    return -1;
}


void rezolvareTask3(const char *f1, const char *f2) {
    FILE *fin = fopen(f1, "r");
    FILE *fout = fopen(f2, "w");
    if (fin == NULL || fout == NULL) {
        printf("Eroare la deschiderea fisierelor pentru task 3 \n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return;
    }

    char s[10][MAX_SYM];
    int nrZile = 0;
    double **prices = citireActiuni(fin, &nrZile, s);
    if (!prices || nrZile <= 1) {
        if (prices) {
            for (int i = 0; i < nrZile; i++) free(prices[i]);
            free(prices);
        }
        fclose(fin);
        fclose(fout);
        return;
    }

    TreeNode *root = createNode(0);
    construireArbore(root, prices, nrZile, s);

    // Variabilă flag pentru a controla enter-urile dintre linii
    int prima_linie = 1;

    // ====================================================================
    // DETERMINAREA OGLINDITULUI FĂRĂ ENTER LA FINAL
    // ====================================================================
    for (int j = 0; j < 10; j++) {
        TreeNode *current = root;
        int gasit_opus = 1;

        for (int i = 1; i < nrZile; i++) {
            double d = prices[i][j] - prices[i-1][j];
            
            if (d == 0.0) {
        // Dacă prețul a stagnat, ambele acțiuni (și cea originală, și cea opusă) 
        // trebuie să meargă pe aceeași ramură (stânga), pentru că stagnarea este simetrică.
        if (current->left) {
            current = current->left;
        } else {
            gasit_opus = 0;
            break;
        }
    } else if (d < 0.0) {
        // Scădere pură -> Mergem la dreapta pentru a găsi opusul (creșterea)
        if (current->right) {
            current = current->right;
        } else {
            gasit_opus = 0;
            break;
        }
    } else {
        // Creștere pură -> Mergem la stânga pentru a găsi opusul (scăderea)
        if (current->left) {
            current = current->left;
        } else {
            gasit_opus = 0;
            break;
        }
    }

        }

        if (gasit_opus && current && current->stocks) {
            StockList *it = current->stocks;
            while (it != NULL) {
                int idx_opus = index_actiune(it->symbol, s);
                
                if (j < idx_opus) {
                    // Dacă NU este prima linie pe care o scriem în fișier, 
                    // punem un enter înaintea ei ca să o separăm de cea precedentă
                    if (!prima_linie) {
                        fprintf(fout, "\n");
                    }
                    
                    // Scriem perechea fără '\n' la sfârșit
                    fprintf(fout, "%s-%s", s[j], it->symbol);
                    
                    // Din acest moment, orice altă linie scrisă va avea nevoie de enter înainte
                    prima_linie = 0;
                }
                it = it->next;
            }
        }
    }
    // ====================================================================

    for (int i = 0; i < nrZile; i++) free(prices[i]);
    free(prices);
    freeTree(root);
    fclose(fin);
    fclose(fout);
}
