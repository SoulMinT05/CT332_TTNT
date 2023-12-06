#include <stdio.h>

#define MAX_N 100
#define NO_COLOR 0
#define RED 1
#define GREEN 2
#define BLUE 3

const char *state[] = {" ", "WA", "NT", "Q", "NSW", "V", "SA", "T"};
const char *color[] = {" ", "RED", "GREEN", "BLUE"};

typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
    int color[MAX_N];
}Graph;

void initGraph(Graph *G, int n) {
    G->n=n;
    G->m=0;
    for(int i=1; i<=G->n; i++) {
        G->color[i] = NO_COLOR;
        for(int j=1; j<=G->n; j++) {
            G->A[i][j] = 0;
        }
    }
}

void addEdge(Graph *G, int u, int v) {
    G->A[u][v] = 1;
    G->A[v][u] = 1;
    G->m++;
}

void input(Graph *G) {
    //format file
    //dong dau tien chua 2 so nguyen n va m tuong ung la so dinh va so dung
    //m dong tiep theo, moi dong chua 2 son nguyen u v mo ta rang dinh u ke voi dinh v
    FILE *f;
    f = fopen("input.txt", "r");
    if(f == NULL) {
        printf("Cannot open the file!");
    }
    int n,m,u,v;
    fscanf(f, "%d%d", &n, &m);
    initGraph(G, n);
    for(int i=1; i<=m; i++) {
        fscanf(f, "%d%d", &u, &v);
        addEdge(G, u, v);
    }
    fclose(f);
}
void print(Graph G) {
    for(int i=1; i<=G.n; i++) {
        for(int j=1; j<=G.n; j++) {
            printf("%d ", G.A[i][j]);
        }
        printf("\n");
    }
}
int isValidColor(Graph G, int u, int c) {
    for(int v=1; v<=G.n; v++) {
        if((G.A[v][u] == 1 || G.A[u][v] == 1) && G.color[v] == c)
            return 0;
    }
    return 1;
}

int colorize(Graph *G) {
    for(int c=1; c<=3; c++) {
        for(int u=1; u<=G->n; u++) {
            if(G->color[u] == NO_COLOR && isValidColor(*G, u, c)) {
                G->color[u] = c;
            }
        }
    }
    for(int u=1; u<= G->n; u++) {
        if(G->color[u] == NO_COLOR) return 0;
    }
    return 1;
}

int main() {
    Graph G;
    input(&G);
    if(colorize(&G)) {
        for(int i=1; i<=G.n; i++) {
            printf("%s - %s\n", state[i], color[G.color[i]]);
        }
    }
    else printf("Cannot colorize this graph\n");
    return 0;
}