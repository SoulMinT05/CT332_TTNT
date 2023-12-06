#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NB_ROWS 8
#define NB_COLUMNS 8
#define MAX_LENGTH NB_ROWS*NB_COLUMNS
#define EMPTY 0
#define MAX_VALUE 8
typedef struct {
    int x, y;
}Coord;
typedef struct {
    Coord data[MAX_LENGTH];
    int size;
}ListCoord;
void init_ListCoord(ListCoord *list) {
    list->size = 0;
}
void append_ListCoord(ListCoord *list, Coord coord) {
    list->data[list->size++] = coord;
}
typedef struct {
    int data[MAX_VALUE];
    int size;
}List;
void init_List(List *list) {
    list->size = 0;
}
void append_List(List *list, int n) {
    list->data[list->size++] = n;
}
typedef struct {
    int data[NB_ROWS*NB_COLUMNS][NB_ROWS*NB_COLUMNS];
    int n;
}Constrains;
void init_Constrains(Constrains* constrains) {
    int i, j;
    for(i = 0; i<NB_ROWS*NB_COLUMNS; i++)
        for(j = 0; j<NB_ROWS*NB_COLUMNS; j++)
            constrains->data[i][j] = 0;
    constrains->n = NB_ROWS*NB_COLUMNS;
}
int indexOf(Coord coord) {
    return NB_ROWS*coord.x + coord.y;
}
Coord positionOf_Vertex(int vertex) {
    Coord coord;
    coord.x = vertex / NB_ROWS;
    coord.y = vertex % NB_COLUMNS;
    return coord;
}
int add_Constrain(Constrains* constrains, Coord source, Coord target) {
    int u = indexOf(source);
    int v = indexOf(target);
    if(constrains->data[u][v] == 0) {
        constrains->data[u][v] = 1;
        constrains->data[v][u] = 1;
        return 1;
    }
    return 0;
}
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
typedef struct {
    int cells[NB_ROWS][NB_COLUMNS];
    Constrains constrains;
}Chess;
void init_Chess(Chess* chess) {
    int i, j;
    for(i = 0; i<NB_ROWS; i++) 
        for(j = 0; j<NB_COLUMNS; j++) {
            chess->cells[i][j] = EMPTY;
        }
    init_Constrains(&chess->constrains);
}
void init_Chess_WithValues(Chess* chess, int inputs[NB_ROWS][NB_COLUMNS]) {
    int i, j;
    for(i = 0; i<NB_ROWS; i++) 
        for(j = 0; j<NB_COLUMNS; j++) {
            chess->cells[i][j] = inputs[i][j];
        }
    init_Constrains(&chess->constrains);
}
void printChess(Chess chess) {
    int i, j;
    printf("Chess:\n");
    printf("-------------------------------------------------\n");
    for(i = 0; i<NB_ROWS; i++){
        for(j = 0; j<NB_COLUMNS; j++){
            printf("| ");
            printf(" %2d ", chess.cells[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------------------------------\n");
}
int isFilled_Chess(Chess chess) {
    int i, j;
    int count = 0;
    for(i = 0; i<NB_ROWS; i++) 
        for(j = 0; j<NB_COLUMNS; j++) {
            if (chess.cells[i][j] != EMPTY)
                count++;
        }
    return count == NB_ROWS;
}
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
    //rang buoc theo duong cheo
    for(i = 0; i<NB_ROWS; i++)
        for(j = 0; j<NB_COLUMNS; j++) {
            if(i != row && j != column && abs(row-i) == abs(column-j)) {
                Coord pos = {i, j};
                if(add_Constrain(constrains, position, pos))
                    append_ListCoord(changeds, pos);
            }
        }
}
int getAvailableValues(Coord position, Chess chess){
	ListCoord posList = get_Constrains(chess.constrains, position);
	int k;
	for (k = 0;k < posList.size; k++)
		if (chess.cells[posList.data[k].x][posList.data[k].y] != EMPTY)
			return 0;
	int availables[MAX_VALUE+1];
	int i, j;
	for(i = 1; i<=MAX_VALUE; i++)
		availables[i] = 1;
	for(i = 0; i<NB_ROWS; i++)
		for (j = 0;j < NB_COLUMNS;j++)
			if (chess.cells[i][j] != EMPTY)
				availables[chess.cells[i][j]] = 0;
	for(i = 1; i<=MAX_VALUE; i++)
		if (availables[i])
			return i;
}
ListCoord getAvailabeCells(Chess chess){
	int i, j;
	ListCoord result;
	init_ListCoord(&result);
	for(i = 0; i<NB_ROWS; i++)
		for(j = 0; j<NB_COLUMNS; j++)
			if(chess.cells[i][j] == EMPTY){
				Coord pos = {i, j};
				ListCoord posList = get_Constrains(chess.constrains, pos);
				int k, flag = 0;
				for (k = 0;k < posList.size;k++)
					if (chess.cells[posList.data[k].x][posList.data[k].y] != EMPTY)
						flag = 1;
				if(flag)
					continue;
				append_ListCoord(&result, pos);
			}
	return result;
}
int exploreCounter = 0;
int Chess_BackTracking(Chess *chess){
	if(isFilled_Chess(*chess))
		return 1;
	ListCoord position = getAvailabeCells(*chess);
	if (position.size == 0)
		return 0;
	int i, j;
	for (i = 0;i < position.size;i++){
		int value = getAvailableValues(position.data[i], *chess);
		chess->cells[position.data[i].x][position.data[i].y] = value;
		exploreCounter++;
		if (Chess_BackTracking(chess))
			return 1;
		chess->cells[position.data[i].x][position.data[i].y] = EMPTY;
	}
	return 0;
}
Chess solveChess(Chess chess) {
    int i, j;
    init_Constrains(&chess.constrains);
    for(i = 0; i<NB_ROWS; i++) {
        for(j = 0; j<NB_COLUMNS; j++) {
            ListCoord history;
            init_ListCoord(&history);
            Coord pos = {i, j};
            spread_ConstrainsFrom(pos, &chess.constrains, &history);
        }
    }
    exploreCounter = 0;
    if(Chess_BackTracking(&chess))
        printf("Solve\n");
    else 
        printf("Can not solve\n");
    printf("Explore %d chesss\n", exploreCounter);
    return chess;
}
int main() {
    Chess chess;
    init_Chess(&chess);
    printChess(chess);
    Chess result = solveChess(chess);
    printChess(result);
}