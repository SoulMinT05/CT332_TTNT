
#include<stdio.h>

#define N 4
#define EMPTY 0

int abs(int x) {
    if (x <= 0) return (-1)*x;
    else return x;
} 

typedef struct {
	int x;
	int y;
}Cell;

int convertFromCellToVertex(Cell c) {
    return c.x * N + c.y;
}

typedef struct {
	int result;
	char operation;
	int numOfCells;
	Cell cells[N * N];
} Cage;

void initCage(Cage *c, int result, char operation, int numOfCells, Cell cells[]) {
	c->result = result;
	c->operation = operation;
	c->numOfCells = numOfCells;
	int i;
	for (i = 0; i < numOfCells; i++) {
		c->cells[i] = cells[i];
	}
}

typedef struct {
	int grid[N][N];
	int numOfCages;
	Cage cages[N * N];
}Kenken;

void initKenken(Kenken *k) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			k->grid[i][j] = EMPTY;
		}
	}
	k->numOfCages = 0;
}

void addCage(Kenken *k, Cage c) {
	k->cages[k->numOfCages] = c;
	k->numOfCages++;
}

// Format:
// 7                    Dong dau tien la so luong cage
// 6 + 3 0 0 0 1 0 2    KQ - Phep toan - So luong o - Toa do cac o
// 1 - 2 1 0 1 1        Neu  cage khong co phep toan thi nhap dau (.)
// 8 * 3 2 0 2 1 3 0
// 4 . 1 3 1
// 7 + 2 1 2 2 2
// 4 / 2 0 3 1 3
// 6 + 3 2 3 3 2 3 3
void input(Kenken *k) {
	int numOfCages;
	scanf("%d", &numOfCages);
	int i, j;
	int result, x, y, numOfCells;
	char operation;
	Cell cells[N * N];
	Cage cage;
	for (i = 1; i <= numOfCages; i++) {
		scanf("%d %c %d", &result, &operation, &numOfCells);
		for (j = 1; j <= numOfCells; j++) {
			scanf("%d %d", &x, &y);
			Cell c = {x, y};
			cells[j - 1] = c;
		}
		initCage(&cage, result, operation, numOfCells, cells);
		addCage(k, cage);
	}
}

void printKenken(Kenken k) {
	printf("\nKENKEN GRID:\n");
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d  ", k.grid[i][j]);
		}
		printf("\n");
	}
	
	printf("\nCAGES:\n");
	for (i = 0; i < k.numOfCages; i++) {
		printf("Cage %d: \n", i + 1);
		printf("Result: %d | Operation: %c | ", k.cages[i].result, k.cages[i].operation);
        printf("Cells: ");
		for (j = 0; j < k.cages[i].numOfCells; j++) {
			printf("(%d, %d) ", k.cages[i].cells[j].x, k.cages[i].cells[j].y);
		}
		printf("\n\n");
	}
}

int checkConstraints(Kenken k, int row, int col, int value) {
    for (int i = 0; i < N; i++) {
        if (k.grid[i][col] == value || k.grid[row][i] == value) return 0;
    }
    return 1;
}

int checkCage(Kenken k, int row, int col) {
    Cell c = {row, col};
    int vertex = convertFromCellToVertex(c);
    Cage findCage;
    for (int i = 0; i < k.numOfCages; i++) {
        for (int j = 0; j < k.cages[i].numOfCells; j++) {
            if (convertFromCellToVertex(k.cages[i].cells[j]) == vertex) findCage = k.cages[i];
            break;
        }
    }
    int numOfCells = findCage.numOfCells;
    // Neu co o chua dc dien thi return true (co kha nang day la phuong an dung)
    for (int i = 0; i < numOfCells; i++) {
        if (k.grid[findCage.cells[i].x][findCage.cells[i].y] == EMPTY) return 1;
    }

    // Neu cage da dc dien het
    int result, a, b;
    switch (findCage.operation)
    {
    case '+':
        result = 0;
        for (int i = 0; i < numOfCells; i++) {
            result += k.grid[findCage.cells[i].x][findCage.cells[i].y];
        }
        if (result != findCage.result) return 0;
        break;
    

    case '-':
        a = k.grid[findCage.cells[0].x][findCage.cells[0].y];
        b = k.grid[findCage.cells[1].x][findCage.cells[1].y];
        result = abs(a - b);
        if (result != findCage.result) return 0;
        break;

    case '*':
        result = 1;
        for (int i = 0; i < numOfCells; i++) {
            result *= k.grid[findCage.cells[i].x][findCage.cells[i].y];
        }
        if (result != findCage.result) return 0;
        break;

    case '/':
        a = k.grid[findCage.cells[0].x][findCage.cells[0].y];
        b = k.grid[findCage.cells[1].x][findCage.cells[1].y];
        if (a >= b) {
            if (a % b != 0) return 0;
            else result = a / b;
        }
        if (a < b) {
            if (b % a != 0) return 0;
            else result = b / a;
        }

        if (result != findCage.result) return 0;
        break;

    case '.':
        result = k.grid[findCage.cells[0].x][findCage.cells[0].y];
        if (result != findCage.result) return 0;
        break;
    
    default:
        break;
    }
}

int isFilledKenken (Kenken k) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (k.grid[i][j] == EMPTY) return 0;
        }
    }
    return 1;
}

int solveKenken(Kenken *k) {
    if (isFilledKenken(*k)) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (!checkCage(*k, row, col)) return 0;
            }
        }
        return 1;
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (k->grid[row][col] == EMPTY) {
                for (int value = 1; value <= N; value++) {
                    if (checkConstraints(*k, row, col, value)) {
                        k->grid[row][col] = value;

                        if (solveKenken(k)) return 1;

                        k->grid[row][col] = EMPTY;
                    }
                }
                return 0;
            }
        }
    }
    return 0;
}

int main() {
	Kenken k;
	initKenken(&k);
	input(&k);
    if (solveKenken(&k)) {
        printf("\n---- SOLVE SUCCESSFULLY ----\n");
    	printKenken(k);
    }
    else printf("Cannot solve.\n");
	return 0;
}
 

