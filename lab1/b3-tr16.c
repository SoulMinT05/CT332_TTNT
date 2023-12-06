#include<stdio.h>
#include<stdlib.h>

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define goal 6
#define Maxlength 100
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
    if(cur_state.y >0 && cur_state.x<tankcapacity_X){
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
        default: printf("Error calls operator!");
            return 0;
    }
}
typedef struct Node{
    State state;
    struct Node* Parent;
    int no_function;
}Node;
//khai bao cau truc Queue
 typedef struct {
     Node* Elements[Maxlength];
     int front, rear;
 }Queue;
//khoi tao hang doi rong
 void makeNull_Queue(Queue *queue) {
     queue->front = -1;
     queue->rear = -1;
 }
 //kiem tra hang doi co rong hay khong
 int empty_Queue(Queue queue) {
     return queue.front == -1;
 }
 //kiem tra hang doi co day hay khong
 int full_Queue(Queue queue) {
     return ((queue.rear - queue.front + 1)%Maxlength) == 0;
 }
 //tra ve phan tu dau hang doi
 Node* get_Front(Queue queue) {
     if(empty_Queue(queue)) 
         printf("Queue is empty!");
    else   
        return queue.Elements[queue.front];
 }
 //xoa bo mot phan tu khoi hang doi
 void del_Queue(Queue *queue) {
     if(!empty_Queue(*queue)) {
         if(queue->front == queue->rear)
            makeNull_Queue(queue);
        else 
            queue->front = (queue->front+1)%Maxlength;
     }
     else
        printf("Error, Delete");
 }
 //Them phan tu vao hang doi
 void push_Queue(Node* x, Queue *queue) {
     if(!full_Queue(*queue)) {
         if(empty_Queue(*queue))
            queue->front = 0;
        queue->rear = (queue->rear+1)%Maxlength;
        queue->Elements[queue->rear] = x;
     }
     else  
        printf("Error, Push");
 }
 //tim trang thai trong Open/ Close
int find_State(State state, Queue openQueue){
    while(!empty_Queue(openQueue)){
        if(compareStates(get_Front(openQueue)->state,state))
            return 1;
        del_Queue(&openQueue);
    }
    return 0;
}
//thuat toan duyet theo chieu rong
Node* BFS_Algorithm(State state){
    //khai bao hai ngan xep open va close
    Queue Open_BFS;
    Queue Close_BFS;
    makeNull_Queue(&Open_BFS);
    makeNull_Queue(&Close_BFS);
    //tao nut trang thai cha
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    push_Queue(root, &Open_BFS);
    while(!empty_Queue(Open_BFS)){
        //lay mot dinh trong ngan xep
        Node* node = get_Front(Open_BFS);
        del_Queue(&Open_BFS);
        push_Queue(node, &Close_BFS);
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
                if(find_State(newstate, Close_BFS) || find_State(newstate, Open_BFS))
                    continue;
                //neu trang thai moi chua ton tai thi them vao ngan xep
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent = node;
                newNode->no_function = opt;
                push_Queue(newNode, &Open_BFS);
            }
        }
    }
    return NULL;
}
//dao nguoc hang doi
void reverseQueue(Queue *q) {
    if (empty_Queue(*q))
        return;
    Node* curr = get_Front(*q); 
    del_Queue(q); 
    reverseQueue(q);
    push_Queue(curr, q);
}

//in ket qua chuyen nuoc de dat den trang thai muc tieu
void print_WaysToGetGoal(Node* node) {
    Queue QueuePrint;
    makeNull_Queue(&QueuePrint);
    //Duyet nguoc ve nut parent
    while (node->Parent != NULL) {
        push_Queue(node, &QueuePrint);
        node = node->Parent;
    }
    push_Queue(node, &QueuePrint);
    reverseQueue(&QueuePrint);
    //In ra thu tu hanh dong chuyen nuoc
    int no_action = 0;
    while(!empty_Queue(QueuePrint)) {
        printf("\nAction %d: %s", no_action, action[get_Front(QueuePrint)->no_function]);
        print_State(get_Front(QueuePrint)->state);
        del_Queue(&QueuePrint);
        no_action++;
    }  
}
int main(){
    State cur_state = {0, 0};
    Node* p = BFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
    return 0;
}