
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

#define Maxlength 100

//Hang chuoi de in ra cac hanh dong
const char* action[] = {"First State", "Lat 234", "Lat 456", "Lat 345", "Lat 123"};

 typedef struct {
     int glass1, glass2, glass3, glass4, glass5, glass6;
 }State;
 //khoi tao trang thai
 void makeNullState(State *state) {
     state->glass1 = -1;
     state->glass2 = -1;
     state->glass3 = -1;
     state->glass4 = -1;
     state->glass5 = -1;
     state->glass6 = -1;
 }
//in trang thai
void print_State(State state) {
    printf("\n\t%d %d %d %d %d %d ", state.glass1, state.glass2, state.glass3, state.glass4, state.glass5, state.glass6);
}
//kiem tra trang thai muc tieu
int goalcheck(State state) {
    return (state.glass1 + state.glass2 + state.glass3 + state.glass4 + state.glass5 + state.glass6 == 6);
}
//lat ly 1
int flip_1(State *cur_state) {
    if(cur_state->glass1 == 1)
    return cur_state->glass1 = 0;
    return cur_state->glass1 = 1;
}
//lat ly 2
int flip_2(State *cur_state) {
    if(cur_state->glass2 == 1)
    return cur_state->glass2 = 0;
    return cur_state->glass2 = 1;
}
//lat ly 3
int flip_3(State *cur_state) {
    if(cur_state->glass3 == 1)
    return cur_state->glass3 = 0;
    return cur_state->glass3 = 1;
}
//lat ly 4
int flip_4(State *cur_state) {
    if(cur_state->glass4 == 1)
    return cur_state->glass4 = 0;
    return cur_state->glass4 = 1;
}
//lat ly 5
int flip_5(State *cur_state) {
    if(cur_state->glass5 == 1)
    return cur_state->glass5 = 0;
    return cur_state->glass5 = 1;
}
//lat ly 6
int flip_6(State *cur_state) {
    if(cur_state->glass6 == 1)
    return cur_state->glass6 = 0;
    return cur_state->glass6 = 1;
}
//lat ly 123
int flip_123(State cur_state, State *result) {
    if(cur_state.glass1 + cur_state.glass2 + cur_state.glass3 == 3)
        return 0;
    result->glass1 = flip_1(&cur_state);
    result->glass2 = flip_2(&cur_state);
    result->glass3 = flip_3(&cur_state);
    result->glass4 = cur_state.glass4;
    result->glass5 = cur_state.glass5;
    result->glass6 = cur_state.glass6;
    return 1;
}
//lat ly 234
int flip_234(State cur_state, State *result) {
    if(cur_state.glass2 + cur_state.glass3 + cur_state.glass4 == 3)
        return 0;
    result->glass1 = cur_state.glass1;
    result->glass2 = flip_2(&cur_state);
    result->glass3 = flip_3(&cur_state);
    result->glass4 = flip_4(&cur_state);
    result->glass5 = cur_state.glass5;
    result->glass6 = cur_state.glass6;
    return 1;
}
//lat ly 345
int flip_345(State cur_state, State *result) {
    if(cur_state.glass3 + cur_state.glass4 + cur_state.glass5 == 3)
        return 0;
    result->glass1 = cur_state.glass1;
    result->glass2 = cur_state.glass2;
    result->glass3 = flip_3(&cur_state);
    result->glass4 = flip_4(&cur_state);
    result->glass5 = flip_5(&cur_state);
    result->glass6 = cur_state.glass6;
    return 1;
}
//lat ly 456
int flip_456(State cur_state, State *result) {
    if(cur_state.glass4 + cur_state.glass5 + cur_state.glass6 == 3)
        return 0;
    result->glass1 = cur_state.glass1;
    result->glass2 = cur_state.glass2;
    result->glass3 = cur_state.glass3;
    result->glass4 = flip_4(&cur_state);
    result->glass5 = flip_5(&cur_state);
    result->glass6 = flip_6(&cur_state);
    return 1;
}
//so sanh hai trang thai co bang nhau khong
int compareStates(State state1, State state2){
    return (state1.glass1 == state2.glass1 && state1.glass2 == state2.glass2 &&
    state1.glass3== state2.glass3 && state1.glass4 == state2.glass4 &&
    state1.glass5 == state2.glass5 && state1.glass6 == state2.glass6);
}
//goi trang thai cac hanh dong
int call_operator(State cur_state, State *result, int option){
    switch(option){
        case 1: return flip_234(cur_state, result);
        case 2: return flip_456(cur_state, result);
        case 3: return flip_345(cur_state, result);
        case 4: return flip_123(cur_state, result);
        default: printf("Error calls operator!");
            return 0;
    }
}


//Khai bao cau truc nut
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

//Tim trang thai trong Stack
int find_State(State state, queue<Node*> Q) {
    while(!Q.empty()) {
        if(compareStates(Q.front()->state,state))
            return 1;
        Q.pop();
    }
    return 0;
}


//Thuat toan duyet theo chieu sau
Node* BFS_Algorithm(State state) {
//    Khai bao 2 ngan xep Open va Close
    queue<Node*> Open_BFS;
    queue<Node*> Close_BFS;
   
    Node*root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    Open_BFS.push(root);
    
    while(!Open_BFS.empty()) {
//        Lay 1 dinh trong ngan xep
        Node* node = Open_BFS.front();
        Open_BFS.pop();
        Close_BFS.push(node);
//        Kiem tra xem dinh lay duoc co phai goal?
        if(goalcheck(node->state))
            return node;
        int opt;
//        Goi cac phep toan trang thai
        for(opt = 1; opt<=4; opt++) {
            State newstate;
            makeNullState(&newstate);
            if(call_operator(node->state, &newstate, opt)) {
                if(find_State(newstate, Close_BFS) || find_State(newstate, Open_BFS))
                    continue;

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent= node;
                newNode->no_function = opt;
                Open_BFS.push(newNode);
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
    State cuz_state = {1,0,1,0,1,0};
    Node* p = BFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}
