
#include <stdio.h>
#include <stdlib.h>
#define num_tusi 3
#define num_quy 3
#include <stack>
using namespace std;
#define Maxlength 100

//Hang chuoi de in ra cac hanh dong
const char* action[] = {
    "First State", "Chuyển 1 tu sĩ", "Chuyển 1 quỷ", "Chuyển 2 tu sĩ", "Chuyển 2 quỷ", "Chuyển 1 tu sĩ, 1 quỷ"
};

//Khai bao cau truc trang thai
typedef struct {
    int so_tusi;
    int so_quy;
    char vitri_thuyen;
}State;

//Khoi tao trang thai binh X = 0 va binh Y = 0 (Trang thai bat dau)
void makeNullState(State *state) {
    state->so_tusi = num_tusi;
    state->so_quy=num_quy;
    state->vitri_thuyen = 'A';
}

//In
void print_State(State state) {
    if(state.vitri_thuyen == 'A')
        printf("\n  A: %d tu sĩ, %d quỷ --- Thuyen dang o bo A --- B: %d tu sĩ, %d quỷ", state.so_tusi, state.so_quy, num_tusi - state.so_tusi, num_quy - state.so_quy);
    else if(state.vitri_thuyen=='B')
        printf("\n  A: %d tu sĩ, %d quỷ --- Thuyen dang o bo B --- B: %d tu sĩ, %d quỷ", state.so_tusi, state.so_quy, num_tusi - state.so_tusi, num_quy - state.so_quy);
//    printf("%d Tu sĩ", state.so_tusi);
//    printf("%d Quỷ", state.so_quy);
//    printf(" |");
//    printf("%d Ban đầu - tu sĩ", state.so_tusi);
//    printf("%d Ban đầu - quỷ", state.so_quy);
//    printf(" |");
}
// Kiem tra muc tieu
int goalcheck(State state) {
    return (state.so_tusi == 3 && state.so_quy == 3 && state.vitri_thuyen == 'A');
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

int moveOnePriest(State cuz_state, State*result) {
    if(cuz_state.vitri_thuyen == 'A') {
        if(cuz_state.so_tusi >=1 ) {
            result->so_tusi = cuz_state.so_tusi -1;
            result->so_quy = cuz_state.so_quy;
            result->vitri_thuyen = 'B';
            return 1;
        }
        return 0;
    }else {
        if(cuz_state.so_tusi == num_tusi) return 0;
        else {
            result->so_tusi = cuz_state.so_tusi + 1;
            result->so_quy = cuz_state.so_quy;
            result->vitri_thuyen = 'A';
            return 1;
        }
    }
}

int moveOneDevil(State cuz_state, State*result) {
    if(cuz_state.vitri_thuyen == 'A') {
        if(cuz_state.so_quy >=1 ) {
            result->so_quy = cuz_state.so_quy -1;
            result->so_tusi = cuz_state.so_tusi;
            result->vitri_thuyen = 'B';
            return 1;
        }
        return 0;
    }else {
        if(cuz_state.so_quy == num_quy) return 0;
        else {
            result->so_quy = cuz_state.so_quy + 1;
            result->so_tusi = cuz_state.so_tusi;
            result->vitri_thuyen = 'A';
            return 1;
        }
    }
}

int moveTwoPriest(State cuz_state, State*result) {
    if(cuz_state.vitri_thuyen == 'A') {
        if(cuz_state.so_tusi >=2 ) {
            result->so_tusi = cuz_state.so_tusi -2;
            result->so_quy = cuz_state.so_quy;
            result->vitri_thuyen = 'B';
            return 1;
        }
        return 0;
    }else {
        if(cuz_state.so_tusi > num_tusi - 2) return 0;
        else {
            result->so_tusi = cuz_state.so_tusi + 2;
            result->so_quy = cuz_state.so_quy;
            result->vitri_thuyen = 'A';
            return 1;
        }
    }
}

int moveTwoDevil(State cuz_state, State*result) {
    if(cuz_state.vitri_thuyen == 'A') {
        if(cuz_state.so_quy >=2) {
            result->so_quy = cuz_state.so_quy -2;
            result->so_tusi = cuz_state.so_tusi;
            result->vitri_thuyen = 'B';
            return 1;
        }
        return 0;
    }else {
        if(cuz_state.so_quy > num_quy - 2) return 0;
        else {
            result->so_quy = cuz_state.so_quy + 2;
            result->so_tusi = cuz_state.so_tusi;
            result->vitri_thuyen = 'A';
            return 1;
        }
    }
}

int moveOnePriestOneDevil(State cuz_state, State*result) {
    if(cuz_state.vitri_thuyen == 'A') {
        if((cuz_state.so_tusi >=1 && cuz_state.so_quy>=1)) {
            result->so_tusi = cuz_state.so_tusi -1;
            result->so_quy = cuz_state.so_quy -1;
            result->vitri_thuyen = 'B';
            return 1;
        }
        return 0;
    }else {
        if(cuz_state.so_tusi == num_tusi || cuz_state.so_quy == num_quy) return 0;
        else {
            result->so_tusi = cuz_state.so_tusi+1;
            result->so_quy = cuz_state.so_quy + 1;
            result->vitri_thuyen = 'A';
            return 1;
        }
    }
}

int check(State cuz_state) {
//    if(cuz_state.so_quy > cuz_state.so_tusi && cuz_state.so_tusi!=0) {
//        return 0;
//    }else if(cuz_state.so_tusi==0) {
////        result.so_tusi = cuz_state.so_tusi;
//        return 1;
//    }
//    return 1;
    
    
    if(cuz_state.so_tusi >0 && cuz_state.so_tusi < num_tusi) {
        if(cuz_state.so_tusi >= cuz_state.so_quy && num_tusi - cuz_state.so_tusi >= num_quy - cuz_state.so_quy)
                return 0; //song
    }
    if(cuz_state.so_tusi == num_tusi) {
        if(cuz_state.so_tusi >= cuz_state.so_quy)
            return 0;
    }
    if(cuz_state.so_tusi ==0) {
//        if(num_tusi >= num_quy - cuz_state.so_quy)
            return 0;
    }
    return 1; //chet (bi an)
}

//Goi cac hanh dong
int call_operator(State cuz_state, State*result, int option) {
    //    option = 0;
    switch(option){
        case 1: return moveOnePriest(cuz_state, result);
        case 2: return moveOneDevil(cuz_state, result);
        case 3: return moveTwoPriest(cuz_state, result);
        case 4: return moveTwoDevil(cuz_state, result);
        case 5: return moveOnePriestOneDevil(cuz_state, result);
        default :
            printf("Loi!");
            return 0;
    }
}

typedef struct Node {
    State state;
    struct Node* Parent; //(0,4) se lam cha cua (9,4)
    int no_function;
}Node;

//Khai bao cau truc Stack
typedef struct {
    Node* Elements[Maxlength];
    int Top_idx;
}Stack;


//Queue

typedef struct {
    Node* Elements[Maxlength];
    int front,rear;
}Queue;


int compareStates(State A, State B) {
    return (A.so_tusi==B.so_tusi) && (A.so_quy==B.so_quy) && (A.vitri_thuyen == B.vitri_thuyen);
}
//Tim trang thai trong Stack
int find_State(State state, stack<Node*> S) {
    while(!S.empty()) {
        if(compareStates(S.top()->state,state))
            return 1;
       S.pop();
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
        for(opt = 1; opt<=5; opt++) {
            State newstate;
            makeNullState(&newstate);
            if(call_operator(node->state, &newstate, opt)) {
                if(find_State(newstate, Close_DFS) || find_State(newstate, Open_DFS))
                    continue;
                if(check(newstate)) continue;
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
    State cuz_state = {0, 0, 'B'};
    Node* p = DFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}
