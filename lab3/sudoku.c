#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define NB_ROWS 9
#define NB_COLUMNS 9
#define MAX_VALUE 10
#define EMPTY 0
#define AREA_QUARE_SIZE 3
#define INF 999999

// x va y co gia tri tu 0 den 8
typedef struct {
    int x, y;
}Coord;

typedef struct {
    Coord data[MAX_LENGTH];
    int size;
}ListCoord;
//tao listcord rong
void init_ListCoord(ListCoord *list) {
    list->size = 0;
}
//them coord vao listcoord
void append_ListCoord(ListCoord *list, Coord coord) {
    list->data[list->size++] = coord;
}

typedef struct {
    int data[MAX_VALUE];
    int size;
}List;
//tao danh sach rong
void init_List(List *list) {
    list->size = 0;
}
//them phan tu vao danh sach
void append_List(List *list, int n) {
    list->data[list->size++] = n;
}

typedef struct {
    int data[NB_ROWS*NB_COLUMNS][NB_ROWS*NB_COLUMNS];
    int n;
}Constrains;
//khoi tao rang buoc rong
void init_Constrains(Constrains* constrains) {
    int i, j;
    for(i = 0; i<NB_ROWS*NB_COLUMNS; i++)
        for(j = 0; j<NB_ROWS*NB_COLUMNS; j++)
            constrains->data[i][j] = 0;
    constrains->n = NB_ROWS*NB_COLUMNS;
}
//tim chi so dinh khi biet toa do
//mot o trong Sudoku chuyen thanh mot dinh trong do thi rang buoc
int indexOf(Coord coord) {
    return NB_ROWS*coord.x + coord.y;
}
//tim toa do khi biet chi so sinh
//mot dinh trong do thi rang buoc chuyen thanh mot o trong Sudoku
Coord positionOf_Vertex(int vertex) {
    Coord coord;
    coord.x = vertex / NB_ROWS;
    coord.y = vertex % NB_COLUMNS;
    return coord;
}
//them rang buoc
int add_Constrain(Constrains* constrains, Coord soure, Coord target) {
    int u = indexOf(soure);
    int v = indexOf(target);
    if(constrains->data[u][v] == 0) {
        constrains->data[u][v] = 1;
        constrains->data[v][u] = 1;
        return 1;
    }
    return 0;
}
//tao rang buoc mot dinh
ListCoord get_Constrains(Constrains constrains, Coord coord) {
    int i;
    int v = indexOf(coord);
    ListCoord result;
    init_ListCoord(&result);
    for(i = 0; i<constrains.n; i++) {
        if(constrains.data[v][i] == 1) {
            append_ListCoord(&result, positionOf_Vertex(i));
        }
    }
    return result;
}
//contrains
void clear_Constrains(Constrains *contrains) {
    contrains = 0;
}

typedef struct {
    int cells[NB_ROWS][NB_COLUMNS];
    Constrains constrains;
}Sudoku;
//khoi tao bang Sudoku rong
void init_Sudoku(Sudoku* sudoku) {
    int i, j;
    for(i = 0; i<NB_ROWS; i++)
        for(j = 0; j<NB_COLUMNS; j++) {
            sudoku->cells[i][j] = EMPTY;
        }
    init_Constrains(&sudoku->constrains);
}
//khoi tao bang Sudoku co gia tri
void init_Sudoku_WithValues(Sudoku* sudoku, int inputs[NB_ROWS][NB_COLUMNS]) {
    int i, j;
    for(i = 0; i<NB_ROWS; i++)
        for(j = 0; j<NB_COLUMNS; j++) {
            sudoku->cells[i][j] = inputs[i][j];
        }
    init_Constrains(&sudoku->constrains);
}
//in bang Sudoku
void printSudoku(Sudoku sudoku) {
    int i, j;
    printf("Sudoku: ");
    for(i = 0; i<NB_ROWS; i++) {
        if(i%AREA_QUARE_SIZE == 0)
            printf("                    \n");
        for(j = 0; j<NB_COLUMNS; j++) {
            if(j%AREA_QUARE_SIZE == 0)
            printf("| ");
            printf("%d ", sudoku.cells[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------\n");
}
//kiem tra trang thai ket thuc
int isFilled_Sudoku(Sudoku sudoku) {
    int i, j;
    for(i = 0; i<NB_ROWS; i++)
        for(j = 0; j<NB_COLUMNS; j++) {
            if(sudoku.cells[i][j] == EMPTY)
                return 0;
        }
    return 1;
}
//tao rang buoc tu vi tri cho truoc
void spread_ConstrainsFrom(Coord position, Constrains* constrains, ListCoord* changeds) {
    int row = position.x, column = position.y;
    int i, j;
    //tao rang buoc theo cot
    for(i = 0; i<NB_ROWS; i++) {
        if(i != row) {
            Coord pos = {i, column};
            if(add_Constrain(constrains, position, pos))
                append_ListCoord(changeds, pos);
        }
    }
    //tao rang buoc theo hang
     for(i = 0; i<NB_COLUMNS; i++) {
        if(i != column) {
            Coord pos = {row, i};
            if(add_Constrain(constrains, position, pos))
                append_ListCoord(changeds, pos);
        }
     }
     //truyen rang buoc theo khoi
     for(i = 0; i<AREA_QUARE_SIZE; i++){
        for(j = 0; j<AREA_QUARE_SIZE; j++) {
            int area_X = (row/AREA_QUARE_SIZE) * AREA_QUARE_SIZE;
            int area_Y = (column/AREA_QUARE_SIZE) * AREA_QUARE_SIZE;
            if(area_X+i != row || area_Y+j != column) {
                Coord pos = {area_X+i, area_Y+j};
                if(add_Constrain(constrains, position,pos))
                    append_ListCoord(changeds, pos);
            }
        }
     }
}
//tim mien gia tri cua o trong
List get_AvailableValues(Coord position, Sudoku sudoku) {
    ListCoord posList = get_Constrains(sudoku.constrains, position);
    int availables[MAX_VALUE]; // 0>0 array, just use 1>0
    int i;
    for(i = 1; i<MAX_VALUE; i++)
        availables[i] = 1;
    for(i = 0; i<posList.size; i++) {
        Coord pos = posList.data[i];
        if(sudoku.cells[pos.x][pos.y] != EMPTY) { //dang mang gia tri
            availables[sudoku.cells[pos.x][pos.y]] = 0;
        }
    }
    List result;
    init_List(&result);
    for(i = 1; i<MAX_VALUE; i++) {
        if(availables[i])
            append_List(&result, i);
    }
    return result;
}
//xac dinh o nao uu tien duoc dien truoc
//cach 1 do lat luot, o nao trong thi chon
Coord get_NextEmptyCell(Sudoku sudoku) {
    int i ,j;
    for(i = 0; i<NB_ROWS; i++) {
        for(j = 0; j<NB_COLUMNS; j++){
            Coord pos = {i, j};
            if(sudoku.cells[i][j] == EMPTY)
                return pos;
        }
    }
//    return 0;
}
//cach 2 uu tien o co mien gia tri it nhat
Coord get_NextMinDomainCell(Sudoku sudoku) {
    int minLength = INF;
    int i, j;
    Coord result;
    for(i = 0; i < NB_ROWS; i++) {
        for(j = 0; j < NB_COLUMNS; j++) {
            if(sudoku.cells[i][j] == EMPTY) {
                Coord pos = {i, j};
                int availableLength = get_AvailableValues(pos, sudoku).size;
                if( availableLength < minLength) {
                    minLength = availableLength;
                    result = pos;
                }
            }
        }
    }
    return result;
}
//thuat toan
int exploredCounter = 0;

int sudokuBackTracking(Sudoku* sudoku) {
    if(isFilled_Sudoku(*sudoku))
        return 1;
    //Coord position = get_NextEmptyCell(*sudoku);
    Coord position = get_NextMinDomainCell(*sudoku);
    List availables = get_AvailableValues(position, *sudoku);
    if(availables.size == 0) {
        //neu nhu mien gia tri rong nhung o van chua duoc dien
        return 0;
    }
    int j;
    for(j = 0; j<availables.size; j++) {
        int value = availables.data[j];
        sudoku->cells[position.x][position.y] = value;
        exploredCounter++;
        if(sudokuBackTracking(sudoku))
            return 1;
        sudoku->cells[position.x][position.y] = EMPTY;
    }
    return 0;
}
//lan truyen rang buoc tu de bai cho truoc va ket thuc bai toan
Sudoku solveSudoku(Sudoku sudoku) {
    int i, j;
    clear_Constrains(&sudoku.constrains);
    for(i = 0; i<NB_ROWS; i++) {
        for(j = 0; j<NB_COLUMNS; j++) {
            if(sudoku.cells[i][j] != EMPTY) {
                ListCoord history;
                init_ListCoord(&history);
                Coord pos = {i, j};
                spread_ConstrainsFrom(pos, &sudoku.constrains, &history);
            }
        }
    }
    exploredCounter = 0;
    if(sudokuBackTracking(&sudoku))
        printf("\nSolve\n");
    else
        printf("\nCan not solve\n");
    printf("Explore %d states\n", exploredCounter);
    return sudoku;
}
int inputs1[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8 ,0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0 ,0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9},
};
//int inputs2[9][9] = {
//    {0, 6, 1, 0, 0, 7, 0, 0, 3},
//    {0, 9, 2, 0, 0, 3, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 0, 8, 5, 3, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0, 5, 0, 4},
//    {5, 0, 0, 0, 0, 8, 0, 0, 0},
//    {0, 4, 0, 0, 0, 0, 0, 0, 1},
//    {0, 0, 0, 1, 6, 0, 8, 0, 0},
//    {6, 0, 0, 0, 0, 0, 0, 0, 0}
//};
int main(int argc, const char * argv[]) {
    Sudoku sudoku;
    init_Sudoku_WithValues(&sudoku, inputs1);
    printSudoku(sudoku);
    Sudoku result = solveSudoku(sudoku);
    printSudoku(result);
}
