#include<stdio.h>
#include<stdlib.h>

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define goal 6 //muc tieu bai toan
#define Maxlength 100 //su dung cai dat ngan xep Stack

//hang chuoi de in ra cac hanh dong
const char* action[] = {"First State","pour Water Full X","pour Water Full Y",
                        "pour Water Empty X","pour Water Empty Y",
                        "pour Water X to Y","pour Water Y to X"};

typedef struct{
     int x;
     int y;
}State;
//khoi tao trang thai
void makeNullState(State *state){
    state->x = 0;
    state->y = 0;
}
//in trang thai
void print_State(State state){
    printf("\n  X:%d --- Y:%d", state.x, state.y);
}
//ham kiem tra trang thai muc tieu
int goalcheck(State state){
    return (state.x==goal || state.y==goal);
}
//lam day x
int pourWaterFullX(State cur_state, State *result){
    if(cur_state.x < tankcapacity_X){
        result->x = tankcapacity_X;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
//lam day y
int pourWaterFullY(State cur_state, State *result){
    if(cur_state.y < tankcapacity_Y){
        result->y = tankcapacity_Y;
        result->x = cur_state.x;
        return 1;
    }
    return 0;
}
//lam rong x
int pourWaterEmptyX(State cur_state, State *result){
    if(cur_state.x > 0){
        result->x = empty;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
//lam rong y
int pourWaterEmptyY(State cur_state, State *result){
    if(cur_state.y > 0){
        result->y = empty;
        result->x = cur_state.x;
        return 1;
    }
    return 0;
}
//max
int max(int a, int b){
    return a > b ? a : b;
}
//min
int min(int a, int b){
    return a < b ? a : b;
}
//chuyen x sang y
int pourWaterXY(State cur_state, State *result){
    if(cur_state.x > 0 && cur_state.y < tankcapacity_Y){
        result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y), empty);
        result->y = min(cur_state.x + cur_state.y, tankcapacity_Y);
        return 1;
    }
    return 0;
}
//chuyen y sang x
int pourWaterYX(State cur_state, State *result){
    if(cur_state.y >0 && cur_state.x < tankcapacity_X){
        result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),empty);
        result->x = min(cur_state.x + cur_state.y, tankcapacity_X);
        return 1;
    }
    return 0;
}
//so sanh hai trang thai co bang nhau khong
int compareStates(State state1, State state2){
    return (state1.x == state2.x && state1.y == state2.y);
}   
//goi trang thai cac hanh dong
int call_operator(State cur_state, State *result, int option){
    switch(option){
        case 1: return pourWaterFullX(cur_state, result);
        case 2: return pourWaterFullY(cur_state, result);
        case 3: return pourWaterEmptyX(cur_state, result);
        case 4: return pourWaterEmptyY(cur_state, result);
        case 5: return pourWaterXY(cur_state, result);
        case 6: return pourWaterYX(cur_state, result);
        default: printf("Error calls operators!");
            return 0;
    }
}
//khai bao Node
typedef struct Node{
    State state;
    struct Node* Parent;
    int no_function;
}Node;
//Khai bao Stack
typedef struct{
    Node* Elements[Maxlength];
    int Top_idx;
}Stack;

//khoi tao ngan xep rong
void makeNull_Stack(Stack *stack){
    stack->Top_idx = Maxlength;
}
//kiem tra ngan xep co rong hay khong
int empty_Stack(Stack stack){
    return stack.Top_idx == Maxlength;
}
//kiem tra ngan xep co day ko
int full_Stack(Stack stack){
    return stack.Top_idx == 0;
}
//Dua 1 phan tu len ngan xep
void push(Node* x, Stack *stack){
    if(full_Stack(*stack))
        printf("Error! Stack is full\n");
    else{
        stack->Top_idx--;
        stack->Elements[stack->Top_idx] = x;
    }
}
//tra ve phan tu tren dinh ngan xep
Node* top(Stack stack){
    if(!empty_Stack(stack))
        return stack.Elements[stack.Top_idx];
    return NULL;
}
//xoa phan tu tai dinh ngan xep
void pop(Stack *stack){
    if(!empty_Stack(*stack))
        stack->Top_idx++;
    else 
        printf("Error! Stack is empty");
}
//tim trang thai trong Open/ Close
int find_State(State state, Stack openStack){
    while(!empty_Stack(openStack)){
        if(compareStates(top(openStack)->state,state))
            return 1;
        pop(&openStack);
    }
    return 0;
}
//thuat toan duyet theo chieu sau
Node* DFS_Algorithm(State state){
    // khai bao hai ngan xep open va close
    Stack Open_DFS;
    Stack Close_DFS;
    makeNull_Stack(&Open_DFS);
    makeNull_Stack(&Close_DFS);
    //tao nut trang thai cha
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    push(root, &Open_DFS);
    while(!empty_Stack(Open_DFS)){
        //lay mot dinh trong ngan xep
        Node* node = top(Open_DFS);
        pop(&Open_DFS);
        push(node, &Close_DFS);
        //kiem tra xem dinh lay ra co phai trang thai muc tieu
        if(goalcheck(node->state))
            return node;
        int opt;
        //goi cac phep toan tren trang thai
        for(opt = 1; opt <= 6; opt++){
            State newstate;
            makeNullState(&newstate);
            if(call_operator(node->state, &newstate, opt)){
                //neu trang thai moi sinh ra ton tai thi bo qua
                if(find_State(newstate, Close_DFS) || find_State(newstate, Open_DFS))
                    continue;
                //neu trang thai moi chua ton tai thi them vao ngan xep
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent = node;
                newNode->no_function = opt;
                push(newNode, &Open_DFS);
            }
        }
    }
    return NULL;
}
//in ket qua chuyen nuoc de dat den trang thai muc tieu
void print_WaysToGetGoal(Node* node) {
    Stack stackPrint;
    makeNull_Stack(&stackPrint);
    //Duyet nguoc ve nut parent
    while (node->Parent != NULL) {
        push(node, &stackPrint);
        node = node->Parent;
    }
    push(node, &stackPrint);
    //In ra thu tu hanh dong chuyen nuoc
    int no_action = 0;
    while(!empty_Stack(stackPrint)) {
        printf("\nAction %d: %s", no_action, action[top(stackPrint)->no_function]);
        print_State(top(stackPrint)->state);
        pop(&stackPrint);
        no_action++;
    }  
}
int main(){
    State cur_state = {0, 0};
    Node* p = DFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
    return 0;
}