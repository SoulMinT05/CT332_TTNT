#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// #include <conio.h>
#include <unistd.h>

#define BLOCK 3
#define SIZE 9
#define EMPTY 0
#define COOLING_FACTOR 0.999
#define MIN_TEMPERATURE 0.001

void seedRandomGenerator(){
    srand( time(NULL) * getpid() );
}

int inputsudoku[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

typedef struct {
    int grid[SIZE][SIZE];
    int fixedValueCells[SIZE][SIZE];
}Sudoku;

void printSoduku(int grid[SIZE][SIZE]) {
    printf("=========================\n");
    for (int row = 0; row < SIZE; row++) {
        if (row > 0 && row % BLOCK == 0) {
            printf("------------------------\n");
        } printf("| ");
        
        for (int col = 0; col < SIZE; col++) {
            printf("%d ", grid[row][col]);
            if ((col + 1) % BLOCK == 0) {
                printf("| ");
            }   
        }
        printf("\n");
    }
    printf("=========================\n");
}

// Kiểm tra xem value có tồn tại trong khối 3x3 hiện tại hay chưa?
int isValidInBlock(int grid[SIZE][SIZE], int row, int col, int value) {
    int startRow = row - row % BLOCK;
    int startCol = col - col % BLOCK;

    for (int i = startRow; i < startRow + BLOCK; i++) {
        for (int j = startCol; j < startCol + BLOCK; j++) {
            if (grid[i][j] == value) {
                return 1; // Giá trị đã tồn tại trong khối
            }
        }
    }
    return 0; // Giá trị không tồn tại trong khối
}

// Khởi tạo ngẫu nhiên sao cho trong mỗi khối 3x3 không có giá trị lặp lại
void initializeSudoku(Sudoku *sudoku, int inputGrid[SIZE][SIZE]) {
    int row, col;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            sudoku->grid[row][col] = inputGrid[row][col];
            sudoku->fixedValueCells[row][col] = inputGrid[row][col];   
        }
    }
    
    int value;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (sudoku->grid[row][col] == EMPTY) {
                value = rand() % SIZE + 1;
                while (isValidInBlock(sudoku->grid, row, col, value)) {
                    value = rand() % SIZE + 1;
                } 
                sudoku->grid[row][col] = value;
            }
        }
    }
}

//Hoán đổi
void swapTwoCells(Sudoku *sudoku, int cell1Row, int cell1Col, int cell2Row, int cell2Col) {
    int temp = sudoku->grid[cell1Row][cell1Col];
    sudoku->grid[cell1Row][cell1Col] = sudoku->grid[cell2Row][cell2Col];
    sudoku->grid[cell2Row][cell2Col] = temp;
}

// Khi các giá trị trên dòng hoặc cột trùng nhau thì sẽ biến conflict sẽ + 1
int cost(Sudoku sudoku){
    int conflicts = 0;
    int num, i, j, k;
    for(i = 0; i < 9; i++){
        //tinh conflicts theo hang`
        for(j = 0; j < 9; j++){
            int num = sudoku.grid[i][j];
            for(k = j+1; k < 9; k++){
                if(num == sudoku.grid[i][k]){
                    conflicts++;
                    break;
                }
            }
        }
        //tinh conflicts theo cot
        for(j = 0; j < 9; j++){
            int num = sudoku.grid[j][i];
            for(k = j+1; k < 9; k++){
                if(num == sudoku.grid[k][i]){
                    conflicts++;
                    break;
                }
            }
        }
    }
    return conflicts;     
}
//Lấy ngẫu nhiên 1 khối và trả về hàng và cột của ô đầu tiên trong khối
void getRandomBlock(int *row, int *col){
    int block = rand() % SIZE;
    *row = block / BLOCK * BLOCK;
    *col = block % BLOCK * BLOCK;
}
//Lấy ngẫu nhiên hàng và cột của 1 ô trong khối đã cho
void getRandomCell(Sudoku sudoku, int blockRow, int blockCol, int *row, int *col){
    do {
        *row = rand() % BLOCK + blockRow;
        *col = rand() % BLOCK + blockCol;
    }while (sudoku.fixedValueCells[*row][*col] != 0);
}

int AverageInitCost(int input[SIZE][SIZE]) {
    int i, sum = 0;
    Sudoku sudoku;
    for(i = 0; i < 200; i++) {
        initializeSudoku(&sudoku, input);
        sum += cost(sudoku);
    }
    return sum/200;
}

void simulatedAnnealing(Sudoku *sudoku) {
    int iteration = 0;
    double temperature = (double)AverageInitCost(inputsudoku);
    while (temperature > MIN_TEMPERATURE) {
        iteration++;
        //Lấy ngẫu nhiên 1 khối con 3x3
        int randomBlockRow, randomBlockCol;
        getRandomBlock(&randomBlockRow, &randomBlockCol);
        //Lấy ngẫu nhiên 2 ô trong khối con 3x3 vừa tìm 
        int cell1Row, cell1Col, cell2Row, cell2Col;
        getRandomCell(*sudoku, randomBlockRow, randomBlockCol, &cell1Row, &cell1Col);
        getRandomCell(*sudoku, randomBlockRow, randomBlockCol, &cell2Row, &cell2Col);
        //Tính cost của trạng thái hiện tại
        int oldCost = cost(*sudoku);
        //Sinh ra trạng thái mới bằng cách đổi giá trị 2 ô vừa chọn ở trên
        swapTwoCells(sudoku, cell1Row, cell1Col, cell2Row, cell2Col);
        //Tính cost của trạng thái mới
        int newCost = cost(*sudoku);
        //deltaE
        int delta = newCost - oldCost;
        // Chấp nhận trạng thái mới nếu nó tốt hơn hoặc chấp nhận với 1 tỷ lệ nào đó nếu nó tệ hơn
        if (delta <= 0 || exp(-delta / temperature) > ((double)rand() / RAND_MAX)) {
            // Chấp nhận
        } else {
            // Không chấp nhận => chuyển về trạng thái cũ
            swapTwoCells(sudoku, cell1Row, cell1Col, cell2Row, cell2Col);
        }
        //Cập nhật lại nhiệt độ dựa vào COOLING_FACTOR
        temperature *= COOLING_FACTOR;
        //In khối Sudoku và các đơn vị liên quan trên từng bước lặp
        system("cls");
        printSoduku(sudoku->grid);
        printf("Iteration: %d\n", iteration);
        printf("Cost: %d\n", cost(*sudoku));
        printf("Temperature: %f\n", temperature);
        if(cost(*sudoku) == 0) break;
    }
}

int main() {
    seedRandomGenerator();

    //Initialize Sudoku
    Sudoku sudoku;
    initializeSudoku(&sudoku, inputsudoku);

    //Solve Sudoku using simulated annealing
    simulatedAnnealing(&sudoku);
    
    if(cost(sudoku) == 0) {
        printf("\nSudoku Puzzle After Simulated Annealing:\n");
        printSoduku(sudoku.grid);
        printf("Sudoku Solved!!!\n");
    } else printf("Cannot Solve!\n");
    return 0;
}