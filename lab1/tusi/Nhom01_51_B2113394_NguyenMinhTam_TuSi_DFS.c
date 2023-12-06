#include <stdio.h>
#include <stdlib.h>
#define num_tusi 3
#define num_quy 3
#define Maxlength 100
const char* action[] = {
    "First State", "Chuyển 1 tu sĩ", "Chuyển 1 quỷ", "Chuyển 2 tu sĩ", "Chuyển 2 quỷ", "Chuyển 1 tu sĩ, 1 quỷ"
};
typedef struct {
    int so_tusi, so_quy;
    char vitri_thuyen;
}State;
void makeNullState(State *state) {
    state->so_tusi = num_tusi;
    state->so_quy=num_quy;
//    state->vitri_thuyen = 'B';
}
void print_State(State state) {
    if(state.vitri_thuyen == 'A')
           printf("\n  A: %d tu sĩ, %d quỷ --- Thuyen dang o bo A --- B: %d tu sĩ, %d quỷ", state.so_tusi, state.so_quy, num_tusi - state.so_tusi, num_quy - state.so_quy);
       else if(state.vitri_thuyen=='B')
           printf("\n  A: %d tu sĩ, %d quỷ --- Thuyen dang o bo B --- B: %d tu sĩ, %d quỷ", state.so_tusi, state.so_quy, num_tusi - state.so_tusi, num_quy - state.so_quy);
}
int goalcheck(State state) {
    return (state.so_tusi == 3 && state.so_quy == 3 && state.vitri_thuyen == 'A');
}
int max(int a, int b){
    return a>b?a:b;
}
int min(int a, int b){
    return a<b?a:b;
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
    if(cuz_state.so_tusi >0 && cuz_state.so_tusi < num_tusi) {
        if(cuz_state.so_tusi >= cuz_state.so_quy && num_tusi - cuz_state.so_tusi >= num_quy - cuz_state.so_quy)
            return 0;
    }
    if(cuz_state.so_tusi == num_tusi) {
        if(cuz_state.so_tusi >= cuz_state.so_quy)
            return 0;
    }
    if(cuz_state.so_tusi ==0) {
        if(num_tusi >= num_quy - cuz_state.so_quy)
            return 0;
    }
    return 1; //chet (bi an)
}
int call_operator(State cuz_state, State*result, int option) {
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
    return (A.so_tusi==B.so_tusi) && (A.so_quy==B.so_quy) && (A.vitri_thuyen == B.vitri_thuyen);
}
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
    State cuz_state = {0, 0, 'B'};
    Node* p = DFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}
