#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm> 

using namespace std;

#define ROWS 3
#define COLS 3
#define EMPTY 0
#define MAX_OPERATOR 4
#define Maxlength 500

const char*  action[] = {"First State", "Move cell EMPTY to UP","Move cell EMTPY to DOWN",
                        "move cell EMPTY to LEFT","move cell EMPTY to RIGHT"};
//khai bao cau truc trang thai cua 8_puzzle
typedef struct{
    int eightPuzzle[ROWS][COLS];
    int emptyRow;
    int emptyCol;
}State;
//in trang thai
void printState(State state) {
    int row, col;
    printf("\n---------\n");
    for(row = 0; row<ROWS; row++) {
        for(col = 0; col<COLS; col++)
            printf("|%d ", state.eightPuzzle[row][col]);
        printf("|\n");
        }
    printf("\n---------\n");
    }
//so sanh hai trang thai
int compareStates(State state1, State state2) {
    if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
        return 0;
    int row, col;
    for(row=0; row<ROWS; row++) 
        for(col=0; col<COLS; col++)
            if(state1.eightPuzzle[row][col] != state2.eightPuzzle[row][col])
                return 0;
    return 1;
}
//kiem tra trang thai muc tieu
int goalCheck(State state, State goal) {
    return compareStates(state, goal);
}
//ham chuyen o trong len tren
int upOperator(State state, State *result) {
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if(empRowCurrent > 0) {
        result->emptyRow = empRowCurrent - 1;
        result->emptyCol = empColCurrent;
        result->eightPuzzle[empRowCurrent][empColCurrent] =state.eightPuzzle[empRowCurrent - 1][empColCurrent];
        result->eightPuzzle[empRowCurrent - 1][empColCurrent] = EMPTY;
        return 1;
    }
    return 0;
}
//ham chuyen o torng xuong duoi
int downOperator(State state, State *result) {
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if(empRowCurrent < 2) {
        result->emptyRow = empRowCurrent + 1;
        result->emptyCol = empColCurrent;
        result->eightPuzzle[empRowCurrent][empColCurrent] =state.eightPuzzle[empRowCurrent + 1][empColCurrent];
        result->eightPuzzle[empRowCurrent + 1][empColCurrent] = EMPTY;
        return 1;
    }
    return 0;
}
//ham chuyen o trong sang phai
int leftOperator(State state, State *result) {
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if(empColCurrent > 0) {
        result->emptyRow = empRowCurrent;
        result->emptyCol = empColCurrent - 1;
        result->eightPuzzle[empRowCurrent][empColCurrent] =state.eightPuzzle[empRowCurrent][empColCurrent - 1];
        result->eightPuzzle[empRowCurrent][empColCurrent - 1] = EMPTY;
        return 1;
    }
    return 0;
}
//ham chuyen o trong sang trai
int rightOperator(State state, State *result) {
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if(empColCurrent < 2) {
        result->emptyRow = empRowCurrent;
        result->emptyCol = empColCurrent + 1;
        result->eightPuzzle[empRowCurrent][empColCurrent] =state.eightPuzzle[empRowCurrent][empColCurrent + 1];
        result->eightPuzzle[empRowCurrent][empColCurrent + 1] = EMPTY;
        return 1;
    }
    return 0;
}
//ham goi cac hanh dong chuyen o trong
int callOperators(State state, State *result, int opt) {
    switch(opt) {
        case 1: return upOperator(state, result);
        case 2: return downOperator(state, result);
        case 3: return leftOperator(state, result);
        case 4: return rightOperator(state, result);
        default: printf("Cannot call operators");
            return 0;
    }
}
//ham heuristic 1
//dem so o sai khac voi trang thai muc tieu
int heuristic1(State state, State goal) {
    int row, col, count = 0;
    for(row=0; row<ROWS; row++)
        for(col=0; col<COLS; col++)
            if(state.eightPuzzle[row][col] != goal.eightPuzzle[row][col])
                count++;
    return count;
}
//ham heuristic 2
//dem so buoc chuyen o sai ve dung cua trang thai muc tieu
int heuristic2(State state, State goal) {
    int count = 0;
    int row, col, row_g, col_g;
    for(row=0; row<ROWS; row++) 
        for(col=0; col<COLS; col++) 
            if(state.eightPuzzle[row][col] != EMPTY) {
                for(row_g = 0; row_g<ROWS; row_g++)
                    for(col_g = 0; col_g<COLS; col_g++)
                        if(state.eightPuzzle[row][col] == goal.eightPuzzle[row_g][col_g]) {
                            count += abs(row - row_g) + abs(col - col_g);
                            col_g = COLS;
                            row_g = ROWS;
                        }
            }
    return count;
}
//khai bao cau truc Node de dung cay tim kiem
typedef struct Node {
    State state;
    struct Node* parent;
    int no_function;
    int heuristic;
}Node;
//tim trang thai State co thuoc Open hay Close hay ko?
//luu vi tri tim duoc vao bien *position
Node* find_State(State state, vector<Node*> v, vector<Node*>::iterator *position) {
    vector<Node *>::iterator it = v.begin();
    if(v.size() == 0) 
        return NULL;
    //lap qua cac phan tu cho den khi bien it la gia tri cuoi cung
    while(it != v.end()) {
        if(compareStates((*it)->state, state)) {
            *position = it;
            return *it;
        }
        it = v.erase(it);
    }
    return NULL;
}
//sap xep danh sach theo trong so heuristic
//tieu chi de sort trong mot vector
//phan tu trong vector se duoc truyen lan luot va Node* a va Node* b de so sanh
bool compareHeuristic(Node* a, Node* b) {
    return a->heuristic > b->heuristic;
}
//thuat toan tim kiem tot nhat dau tien
//ham f = h
Node* best_first_search(State state, State goal) {
    vector<Node*> Open_BFS(Maxlength);
    Open_BFS.clear(); //lam rong Open_BFS
    vector<Node*> Close_BFS(Maxlength);
    Close_BFS.clear(); //lam trong Close_BFS
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    root->heuristic = heuristic1(root->state, goal);
    Open_BFS.push_back(root);
    while (!Open_BFS.empty()) {
        Node* node = Open_BFS.back();
        Open_BFS.pop_back();
        Close_BFS.push_back(node);
        if(goalCheck(node->state, goal)) {
            printf("Goal\n");
            return node;
        }
        int opt;
        for(opt=1; opt<=MAX_OPERATOR; opt++) {
            State newstate;
            newstate = node->state;
            if(callOperators(node->state, &newstate, opt)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->parent = node;
                newNode->no_function = opt;
                newNode->heuristic = heuristic1(newstate, goal);
                //kiem tra trang thai moi sinh ra co thuoc Open_BFS/ Close_BFS
                vector<Node*>::iterator pos_Open, pos_Close;
                Node* nodeFoundOpen = find_State(newstate, Open_BFS, &pos_Open);
                Node* nodeFoundClose = find_State(newstate, Close_BFS, &pos_Close);
                if(nodeFoundOpen == NULL && nodeFoundClose == NULL) 
                    Open_BFS.push_back(newNode);
                else if(nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic) {
                    Open_BFS.erase(pos_Open);
                    Open_BFS.push_back(newNode);
                }
                else if(nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic) {
                    Close_BFS.erase(pos_Close);
                    Open_BFS.push_back(newNode);
                }
            }
        }
        sort(Open_BFS.begin(), Open_BFS.end(), compareHeuristic);
    }
    return NULL;
}
//ham in ket qua cua thuat toan BFS
void print_WayToGetGoal(Node* node) {
    vector<Node*> vectorPrint;
    //duyet nguoc ve nut parent
    while (node->parent != NULL) {
        vectorPrint.push_back(node);
        node = node->parent;
    }
    vectorPrint.push_back(node);
    //in ra thu tu hanh dong di chuyen o trong
    int no_action = 0, i;
    for(i=vectorPrint.size()-1; i>=0; i--) {
        printf("\nAction %d: %s", no_action, action[vectorPrint.at(i)->no_function]);
        printState(vectorPrint.at(i)->state);
        no_action++;
    }
}
int main() {
    State state; //, result
        state.emptyRow = 1;
        state.emptyCol = 1;
        state.eightPuzzle[0][0] = 3;
        state.eightPuzzle[0][1] = 4;
        state.eightPuzzle[0][2] = 5;
        state.eightPuzzle[1][0] = 1;
        state.eightPuzzle[1][1] = 0;
        state.eightPuzzle[1][2] = 2;
        state.eightPuzzle[2][0] = 6;
        state.eightPuzzle[2][1] = 7;
        state.eightPuzzle[2][2] = 8;
    State goal;
        goal.emptyRow = 0;
        goal.emptyCol = 0;
        goal.eightPuzzle[0][0] = 0;
        goal.eightPuzzle[0][1] = 1;
        goal.eightPuzzle[0][2] = 2;
        goal.eightPuzzle[1][0] = 3;
        goal.eightPuzzle[1][1] = 4;
        goal.eightPuzzle[1][2] = 5;
        goal.eightPuzzle[2][0] = 6;
        goal.eightPuzzle[2][1] = 7;
        goal.eightPuzzle[2][2] = 8;
    Node* p = best_first_search(state, goal);
    print_WayToGetGoal(p);
    return 0;
}