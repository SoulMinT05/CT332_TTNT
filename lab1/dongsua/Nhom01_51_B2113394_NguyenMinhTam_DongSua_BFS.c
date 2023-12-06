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
typedef struct {
    Node* Elements[Maxlength];
    int front,rear;
}Queue;
void makeNull_Queue(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}
int empty_Queue(Queue queue) {
    return queue.front == -1;
}
int full_Queue(Queue queue) {
    return ((queue.rear - queue.front + 1)% Maxlength) == 0;
}
Node* get_Front(Queue queue) {
    if(empty_Queue(queue))
        printf("Queue rong!");
    return queue.Elements[queue.front];
}
void del_Queue(Queue*queue) {
    if(!empty_Queue(*queue)) {
        if(queue->front == queue->rear)
            makeNull_Queue(queue);
        else queue->front = (queue->front + 1)% Maxlength;
    }
    else printf("Error, Delete");
}
void push_Queue(Node* x, Queue *queue) {
    if(!full_Queue(*queue)) {
        if(empty_Queue(*queue))
            queue->front = 0;
        queue->rear = (queue->rear+1)% Maxlength;
        queue->Elements[queue->rear] = x;
    }
    else printf("Error, push");
}
int compareStates(State A, State B) {
    return (A.x==B.x) && (A.y==B.y) && (A.z==B.z);
}
int find_State(State state, Queue Q) {
    while(!empty_Queue(Q)) {
        if(compareStates(get_Front(Q)->state ,state))
            return 1;
        del_Queue(&Q);
    }
    return 0;
}
Node* BFS_Algorithm(State state) {
    Queue Open_BFS;
    Queue Close_BFS;
    makeNull_Queue(&Open_BFS);
    makeNull_Queue(&Close_BFS);
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    push_Queue(root, &Open_BFS);
    while(!empty_Queue(Open_BFS)) {
        Node* node = get_Front(Open_BFS);
        del_Queue(&Open_BFS);
        push_Queue(node, &Close_BFS);
        if(goalcheck(node->state))
            return node;
        int opt;
        for(opt = 1; opt<=6; opt++) {
            State newstate;
            makeNullState(&newstate);
            if(call_operator(node->state, &newstate, opt)) {
                if(find_State(newstate, Close_BFS) || find_State(newstate, Open_BFS))
                    continue;
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent= node;
                newNode->no_function = opt;
                push_Queue(newNode, &Open_BFS);
            }
        }
    }
    return NULL;
}
void reverseQueue(Queue *q) {
    if (empty_Queue(*q))
        return;
    Node* curr = get_Front(*q); 
    del_Queue(q); 
    reverseQueue(q);
    push_Queue(curr, q);
}
void print_WaysToGetGoal(Node* node) {
    Queue QueuePrint;
    makeNull_Queue(&QueuePrint);
    while (node->Parent != NULL) {
        push_Queue(node, &QueuePrint);
        node = node->Parent;
    }
    push_Queue(node, &QueuePrint);
    reverseQueue(&QueuePrint);
    int no_action = 0;
    while(!empty_Queue(QueuePrint)) {
        printf("\nAction %d: %s", no_action, action[get_Front(QueuePrint)->no_function]);
        print_State(get_Front(QueuePrint)->state);
        del_Queue(&QueuePrint);
        no_action++;
    }  
}
int main(int argc, const char * argv[]) {
    State cuz_state = {10,0,0};
    Node* p = BFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}

