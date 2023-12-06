#include <stdio.h>
#include <stdlib.h>
#define tankcapacity_X 10
#define tankcapacity_Y 5
#define tankcapacity_Z 6
#define Empty 0
#define goal 8
#define Maxlength 100
const char* action[] = {
     "First State", "pour Water X to Y", "pour Water X to Z", "pour Water Y to X", "pour Water Y to Z", "pour Water Z to X", "pour Water Z to Y"
};
typedef struct {
    int x,y,z;
}State;
void makeNullState(State *state) {
    state->x = 0;
    state->y=0;
    state->z =0;
}
void print_State(State state) {
    printf("\n  X: %d  --- Y: %d --- Z: %d", state.x, state.y, state.z);
}
int goalcheck(State state) {
    return (state.x == goal || state.y == goal || state.z == goal);
}
int max(int a, int b){
    return a>b?a:b;
}
int min(int a, int b){
    return a<b?a:b;
}
int pourWaterFullX(State cur_state, State *result) {
    if(cur_state.x < tankcapacity_X) {
        result->x = tankcapacity_X;
        result->y = cur_state.y;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}
int pourWaterFullY(State cur_state, State *result) {
    if(cur_state.y < tankcapacity_Y) {
        result->y = tankcapacity_Y;
        result->x = cur_state.x;
        result->z = cur_state.z;
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
int pourWaterEmptyX(State cur_state, State *result) {
    if(cur_state.x > 0 ) {
        result->x = Empty;
        result -> y = cur_state.y;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}
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
int call_operator(State cuz_state, State*result, int option) {
    switch(option){
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
void makeNull_Stack(Stack *stack) {
    stack->Top_idx = Maxlength;
}
int empty_Stack(Stack stack) {
    return stack.Top_idx == Maxlength;
}
int full_Stack(Stack stack) {
    return stack.Top_idx == 0;
}
void push(Node* x, Stack* stack) {
   if(full_Stack(*stack)) {
       printf("Loi! Ngan xep da day.");
   }
    else {
        stack->Top_idx -=1;
        stack->Elements[stack->Top_idx] = x;
    }
}
Node* top(Stack stack) {
    if(!empty_Stack(stack)) 
        return stack.Elements[stack.Top_idx];
    return NULL;
}
void pop(Stack *stack) {
    if(!empty_Stack(*stack))
        stack->Top_idx +=1;
    else printf("Loi! Ngan xep dang rong.");
}
int compareStates(State A, State B) {
    return (A.x==B.x) && (A.y==B.y) && (A.z==B.z);
}
//Tim trang thai trong Stack
int find_State(State state, Stack openStack) {
    while(!empty_Stack(openStack)) {
        if(compareStates(top(openStack)->state,state))
            return 1;
        pop(&openStack);
    }
    return 0;
}
Node* DFS_Algorithm(State state) {
    Stack Open_DFS;
    Stack Close_DFS;
    makeNull_Stack(&Open_DFS);
    makeNull_Stack(&Close_DFS);
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    push(root, &Open_DFS);
    while(!empty_Stack(Open_DFS)) {
        Node* node = top(Open_DFS);
        pop(&Open_DFS);
        push(node, &Close_DFS);
        if(goalcheck(node->state))
            return node;
        int opt;
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
                push(newNode, &Open_DFS);
            }
        }
    }
    return NULL;
}
void print_WaysToGetGoal(Node* node) {
    Stack stackPrint;
    makeNull_Stack(&stackPrint);
    while(node->Parent != NULL) {
        push(node, &stackPrint);
        node = node->Parent;
    }
    push(node, &stackPrint);
    int no_action = 0;
    while(!empty_Stack(stackPrint)){
        printf("\nAction %d: %s", no_action, action[top(stackPrint)->no_function]);
        print_State(top(stackPrint)->state);
        pop(&stackPrint);
        no_action++;
    }
}
int main(int argc, const char * argv[]) {
    State cuz_state = {10,0,0};
    Node* p = DFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}




