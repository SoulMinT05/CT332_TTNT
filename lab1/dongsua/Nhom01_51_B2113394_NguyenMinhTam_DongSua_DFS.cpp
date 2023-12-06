

#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

#define tankcapacity_X 10
#define tankcapacity_Y 5
#define tankcapacity_Z 6
#define Empty 0
#define goal 8
#define Maxlength 100

//Hang chuoi de in ra cac hanh dong
const char* action[] = {
     "First State", "pour Water X to Y", "pour Water X to Z", "pour Water Y to X", "pour Water Y to Z", "pour Water Z to X", "pour Water Z to Y"
};

//Khai bao cau truc trang thai
typedef struct {
    int x;
    int y;
    int z;
}State;

//Khoi tao trang thai binh X = 0 va binh Y = 0 (Trang thai bat dau)
void makeNullState(State *state) {
    state->x = 0;
    state->y=0;
    state->z =0;
}

//In
void print_State(State state) {
    printf("\n  X: %d  --- Y: %d --- Z: %d", state.x, state.y, state.z);
}
// Kiem tra muc tieu
int goalcheck(State state) {
    return (state.x == goal || state.y == goal || state.z == goal);
}


int max(int a, int b){
        if(a > b)
        return a;
    return b;
}

int min(int a, int b){
    if(a < b)
        return a;
    return b;
}

// Lam day binh X
int pourWaterFullX(State cur_state, State *result) {
    if(cur_state.x < tankcapacity_X) {
        result->x = tankcapacity_X;
        result->y = cur_state.y;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}

// Lam day binh Y
int pourWaterFullY(State cur_state, State *result) {
    if(cur_state.y < tankcapacity_Y) {
        result->y = tankcapacity_Y;
        result->x = cur_state.x;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}

int pourWaterFullZ(State cur_state, State *result) {
    if(cur_state.z < tankcapacity_Z) {
        result->z = tankcapacity_Z;
        result->x = cur_state.x;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}

// Lam rong binh X
int pourWaterEmptyX(State cur_state, State *result) {
    if(cur_state.x > 0 ) {
        result->x = Empty;
        result -> y = cur_state.y;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}

// Lam rong binh Y
int pourWaterEmptyY(State cur_state, State *result) {
    if(cur_state.y > 0 ) {
        result->y = 0;
        result->x = cur_state.x;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}

int pourWaterEmptyZ(State cur_state, State *result) {
    if(cur_state.z > 0 ) {
        result->z = 0;
        result->x = cur_state.x;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}

// Chuyen nuoc tu X sang Y
int pourWaterXY(State cuz_state, State*result) {
    if(cuz_state.x > 0 && cuz_state.y < tankcapacity_Y){
        result->x = max(cuz_state.x - (tankcapacity_Y - cuz_state.y), Empty);
        result ->y = min(cuz_state.x + cuz_state.y, tankcapacity_Y);
        result->z = cuz_state.z;
        return 1;
    }
    return 0;
}

int pourWaterXZ(State cuz_state, State*result) {
    if(cuz_state.x > 0 && cuz_state.z < tankcapacity_Z){
        result->x = max(cuz_state.x - (tankcapacity_Z - cuz_state.z), Empty);
        result ->z = min(cuz_state.x + cuz_state.z, tankcapacity_Z);
        result->y = cuz_state.y;
        return 1;
    }
    return 0;
}

// Chuyen nuoc tu Y sang X
int pourWaterYX(State cur_state, State *result){
    if(cur_state.y > 0 && cur_state.x < tankcapacity_X){
        result->y = max(cur_state.y - (tankcapacity_X - cur_state.x), Empty);
        result->x = min(cur_state.y + cur_state.x, tankcapacity_X);
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}

int pourWaterYZ(State cuz_state, State*result) {
    if(cuz_state.y > 0 && cuz_state.z < tankcapacity_Z){
        result->y = max(cuz_state.y - (tankcapacity_Z - cuz_state.z), Empty);
        result ->z = min(cuz_state.y + cuz_state.z, tankcapacity_Z);
        result->x = cuz_state.x;
        return 1;
    }
    return 0;
}


int pourWaterZX(State cuz_state, State*result) {
    if(cuz_state.z > 0 && cuz_state.x < tankcapacity_X){
        result->z = max(cuz_state.z - (tankcapacity_X - cuz_state.x), Empty);
        result ->x = min(cuz_state.z + cuz_state.x, tankcapacity_X);
        result->y = cuz_state.y;
        return 1;
    }
    return 0;
}

int pourWaterZY(State cuz_state, State*result) {
    if(cuz_state.z > 0 && cuz_state.y < tankcapacity_Y){
        result->z = max(cuz_state.z - (tankcapacity_Y - cuz_state.y), Empty);
        result ->y = min(cuz_state.z + cuz_state.y, tankcapacity_Y);
        result->x = cuz_state.x;
        return 1;
    }
    return 0;
}
//Goi cac hanh dong
int call_operator(State cuz_state, State*result, int option) {
    //    option = 0;
    switch(option){
//        case 1: return pourWaterFullX(cuz_state, result);
//        case 2: return pourWaterFullY(cuz_state, result);
//        case 3: return pourWaterFullZ(cuz_state, result);
//        case 4: return pourWaterEmptyX(cuz_state, result);
//        case 5: return pourWaterEmptyY(cuz_state, result);
//        case 6: return pourWaterEmptyZ(cuz_state, result);
//        case 7: return pourWaterXY(cuz_state, result);
//        case 8: return pourWaterXZ(cuz_state, result);
//        case 9: return pourWaterYX(cuz_state, result);
//        case 10: return pourWaterYZ(cuz_state, result);
//        case 11: return pourWaterZX(cuz_state, result);
//        case 12: return pourWaterZY(cuz_state, result);
        case 1: return pourWaterXY(cuz_state, result);
        case 2: return pourWaterXZ(cuz_state, result);
        case 3: return pourWaterYX(cuz_state, result);
        case 4: return pourWaterYZ(cuz_state, result);
        case 5: return pourWaterZX(cuz_state, result);
        case 6: return pourWaterZY(cuz_state, result);
        default : printf("Loi!");
            return 0;
    }
}

//Khai bao cau truc nut
typedef struct Node {
    State state;
    struct Node* Parent; //(0,4) se lam cha cua (9,4)
    int no_function;
}Node;

int compareStates(State A, State B) {
    return (A.x==B.x) && (A.y==B.y) && (A.z==B.z);
}
//Tim trang thai trong Stack
int find_State(State state, stack<Node*> openStack) {
    while(!openStack.empty()) {
        
        if(compareStates(openStack.top()->state,state))
            return 1;
        openStack.pop();
    }
    return 0;
}


//Thuat toan duyet theo chieu sau
Node* DFS_Algorithm(State state) {
//    Khai bao 2 ngan xep Open va Close
    stack<Node*> Open_DFS;
    stack<Node*> Close_DFS;
   
    Node*root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    Open_DFS.push(root);
    
    while(!Open_DFS.empty()) {
//        Lay 1 dinh trong ngan xep
        Node* node = Open_DFS.top();
        Open_DFS.pop();
        Close_DFS.push(node);
//        Kiem tra xem dinh lay duoc co phai goal?
        if(goalcheck(node->state))
            return node;
        int opt;
//        Goi cac phep toan trang thai
        for(opt = 1; opt<=6; opt++) {
            State newstate;
            makeNullState(&newstate);
            if(call_operator(node->state, &newstate, opt)) {
                if(find_State(newstate, Close_DFS) || find_State(newstate, Open_DFS))
                    continue;

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent= node;
                newNode->no_function = opt;
                Open_DFS.push(newNode);
                
            }
        }
    }
    return NULL;
}

//In ket qua chuyen nuoc de dat goal
void print_WaysToGetGoal(Node* node) {
    stack<Node*> stackPrint;
    
    while(node->Parent != NULL) {
        stackPrint.push(node);
        node = node->Parent;
    }
    stackPrint.push(node);

    int no_action = 0;
    while(!stackPrint.empty()){
        printf("\nAction %d: %s", no_action, action[stackPrint.top()->no_function]);
        print_State(stackPrint.top()->state);
        stackPrint.pop();
        no_action++;
    }
}




int main(int argc, const char * argv[]) {
    State cuz_state = {10,0,0};
    Node* p = DFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}




