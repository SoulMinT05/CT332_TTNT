#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY 0
#define SIZE 9
#define BLOCK_SIZE 3
#define POPULATION_SIZE 1500
#define MAX_GENERATIONS 2000
#define SELECTION_RATE 0.5
#define MUTATION_RATE 0.25

typedef struct {
    int grid[SIZE][SIZE];
    int fixedValueCells[SIZE][SIZE]; // Lưu các ô có sẵn giá trị
    int fitness; // Độ thích nghi
} Individual;

typedef struct {
    Individual individual[POPULATION_SIZE];
} Population;

void loadFile(int grid[SIZE][SIZE]) {
    FILE *f = fopen("./input.txt", "r");
    if (f == NULL) {
        printf("Cannot open the file.\n");
    }
    else {
        int x;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                fscanf(f, "%d", &x);
                grid[row][col] = x;
            }
        }
    }
}

void printGrid(int grid[SIZE][SIZE]) {
    printf("=======================\n");

    for (int row = 0; row < SIZE; row++) {
        if (row > 0 && row % BLOCK_SIZE == 0) {
                printf("----------------------\n");
            }
        for (int col = 0; col < SIZE; col++) {
            printf("%d ", grid[row][col]);
            if ((col + 1) % BLOCK_SIZE == 0) {
                printf("| ");
            }   
        }
        printf("\n");
    }
    printf("=======================\n");
}

int valueExistInBlock(int grid[SIZE][SIZE], int row, int col, int value) {
    // Xác định xem value có tồn tại trong subgrid hiện tại hay chưa
    int startRow = row - row % BLOCK_SIZE;
    int startCol = col - col % BLOCK_SIZE;

    for (int i = startRow; i < startRow + BLOCK_SIZE; i++) {
        for (int j = startCol; j < startCol + BLOCK_SIZE; j++) {
            if (grid[i][j] == value) {
                return 1; // Giá trị đã tồn tại trong subgrid
            }
        }
    }
    return 0; // Giá trị không tồn tại trong subgrid
}


void initializeIndividual(Individual *individual, int inputGrid[SIZE][SIZE]) {
    // Khởi tạo ngẫu nhiên cá thể sao cho trong mỗi block 3x3 không có giá trị lặp lại
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            individual->grid[row][col] = inputGrid[row][col];
            individual->fixedValueCells[row][col] = inputGrid[row][col];
        }
    }
    int value;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (individual->grid[row][col] == EMPTY) {
                //khúc naytf chưa hiểu lắm
                value = rand() % SIZE + 1;
                while (valueExistInBlock(individual->grid, row, col, value)) {
                    value = rand() % SIZE + 1;
                } 
                individual->grid[row][col] = value;
            }
        }
    }
}

void initializePopulation(Population *population) {
    // Khởi tạo quần thể
    int inputGrid[SIZE][SIZE];
    loadFile(inputGrid);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        initializeIndividual(&population->individual[i], inputGrid);
    }
}

int containsValue(int array[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return 1;
        }
    }
    return 0;
}

int *generateRandomNumbers(int n, int min, int max) {

    int* randomNumbers = (int*)malloc(n * sizeof(int));

    int count = 0;

    while (count < n) {
        int randomNumber = rand() % (max - min + 1) + min;
        int isDuplicate = 0;

        // Kiểm tra xem số ngẫu nhiên đã tồn tại trong mảng chưa
        for (int i = 0; i < count; i++) {
            if (containsValue(randomNumbers, count, randomNumber)) {
                isDuplicate = 1;
                break;
            }
        }

        // Nếu số ngẫu nhiên chưa tồn tại, thêm vào mảng
        if (!isDuplicate) {
            randomNumbers[count] = randomNumber;
            count++;
        }
    }

    return randomNumbers;
}

void crossover(Individual *father, Individual *mother, Individual *child) {
    // Lai tạo
    int numOfBlocks = rand() % (SIZE - 1) + 1;
    int *randomBlocks = generateRandomNumbers(numOfBlocks, 0, SIZE - 2);

    for (int block = 0; block < SIZE; block++) {
        int startRow = block / BLOCK_SIZE * BLOCK_SIZE;
        int startCol = block % BLOCK_SIZE * BLOCK_SIZE;
        for (int row = startRow; row < startRow + BLOCK_SIZE; row++) {
            for (int col = startCol; col < startCol + BLOCK_SIZE; col++) {
                    if (containsValue(randomBlocks, numOfBlocks, block)) {
                        child->grid[row][col] = mother->grid[row][col];
                    }    
                    else child->grid[row][col] = father->grid[row][col];
            }
        }
    }
    free(randomBlocks);
}

void evaluateFitness(Individual *individual) {
    int conflicts = 0;

    // Kiểm tra xung đột trong hàng
    for (int row = 0; row < SIZE; row++) {
        int count[SIZE + 1] = {0};
        for (int col = 0; col < SIZE; col++) {
            int value = individual->grid[row][col];
            count[value]++;
        }
        for (int i = 1; i <= SIZE; i++) {
            if (count[i] > 1)
                conflicts += count[i] - 1;
        }
    }

    // Kiểm tra xung đột trong cột
    for (int col = 0; col < SIZE; col++) {
        int count[SIZE + 1] = {0};
        for (int row = 0; row < SIZE; row++) {
            int value = individual->grid[row][col];
            count[value]++;
        }
        for (int i = 1; i <= SIZE; i++) {
            if (count[i] > 1)
                conflicts += count[i] - 1;
        }
    }
    individual->fitness = conflicts;
}

void sortPopulation(Population *population) {
    for (int i = 0; i < POPULATION_SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < POPULATION_SIZE; j++) {
            if (population->individual[j].fitness < population->individual[minIndex].fitness) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Individual temp = population->individual[i];
            population->individual[i] = population->individual[minIndex];
            population->individual[minIndex] = temp;
        }
    }
}

Population selectFromPopulation(Population population) {
    Population selectedPopulation;
    int i;
    for (i = 0; i < POPULATION_SIZE * SELECTION_RATE; i++) {
        selectedPopulation.individual[i] = population.individual[i];
    }
    for (i; i < POPULATION_SIZE; i++) {
        selectedPopulation.individual[i] = population.individual[rand() % POPULATION_SIZE];
    }
    return selectedPopulation;
}

void swapTwoCells(Individual *individual) { 
    int block = rand() % SIZE; //block = 2
    int startRow = block / BLOCK_SIZE * BLOCK_SIZE; // 0
    int startCol = block % BLOCK_SIZE * BLOCK_SIZE; //6

    int cell1Row, cell1Col, cell2Row, cell2Col;
    
    do {
        cell1Row = rand() % BLOCK_SIZE + startRow;
        cell1Col = rand() % BLOCK_SIZE + startCol;
        cell2Row = rand() % BLOCK_SIZE + startRow;
        cell2Col = rand() % BLOCK_SIZE + startCol;
    }while (individual->fixedValueCells[cell1Row][cell1Col] != 0 || individual->fixedValueCells[cell2Row][cell2Col] != 0);

    int temp = individual->grid[cell1Row][cell1Col];
    individual->grid[cell1Row][cell1Col] = individual->grid[cell2Row][cell2Col];
    individual->grid[cell2Row][cell2Col] = temp;
}

void mutate(Population *population) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            swapTwoCells(&population->individual[i]);
        }
    }
}

void genetic(Population population, Individual *bestIndividual) {
    int generation = 0;
    while (generation < MAX_GENERATIONS) {
        for (int i = 0; i < POPULATION_SIZE; i++) {
            evaluateFitness(&population.individual[i]);

            if (population.individual[i].fitness == 0) {
                printf("\nFound\n");
                *bestIndividual = population.individual[i];
                printf("Solution found in generation: %d\n", generation);
                printf("Fitness: %d\n", bestIndividual->fitness);
                printf("Solution:\n");
                printGrid(bestIndividual->grid);
                return;
            }
        }

        sortPopulation(&population);
        Population selectedPopulation = selectFromPopulation(population);

        Population newPopulation;

        for (int i = 0; i < POPULATION_SIZE; i++) {
            Individual father = selectedPopulation.individual[rand() % POPULATION_SIZE];
            Individual mother = selectedPopulation.individual[rand() % POPULATION_SIZE];
            Individual child;
            crossover(&father, &mother, &child);
            population.individual[i] = child;
        }
        mutate(&population);
        generation++;
    }
    printf("Khong tim thay loi giai\n");
    return;
}

int main() {
    srand(time(NULL));
    Population population;
    initializePopulation(&population);
    Individual bestIndividual;
    genetic(population, &bestIndividual);
    return 0;
}