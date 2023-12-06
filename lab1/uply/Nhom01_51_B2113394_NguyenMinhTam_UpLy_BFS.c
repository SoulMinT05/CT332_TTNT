#include <stdio.h>
#include <stdlib.h>
#define Maxlength 100
const char* action[] = {
    "First State", "Lat 234", "Lat 456", "Lat 345", "Lat 123"
};
typedef struct {
    int glass1, glass2, glass3, glass4, glass5, glass6;
}State;
void makeNullState(State *state) {
    state->glass1 = 0;
    state->glass2 = 0;
    state->glass3 = 0;
    state->glass4 = 0;
    state->glass5 = 0;
    state->glass6 = 0;
}
void print_State(State state) {
    printf("\n\t%d %d %d %d %d %d", state.glass1, state.glass2, state.glass3, state.glass4, state.glass5, state.glass6);
}
int goalcheck(State state) {
    return state.glass1 + state.glass2 + state.glass3 + state.glass4 + state.glass5 + state.glass6 == 6;
}
int max(int a, int b){
    return a>b ? a:b;
}

int min(int a, int b){
    return a<b ? a:b;
}
int flip_1(State*cuz_state) {
    if(cuz_state->glass1 == 1)
        return cuz_state->glass1 = 0;
    return cuz_state->glass1 = 1;
}
int flip_2(State *cur_state) {
    if(cur_state->glass2 == 1)
        return cur_state->glass2 = 0;
    return cur_state->glass2 = 1;
}
int flip_3(State *cur_state) {
    if(cur_state->glass3 == 1)
        return cur_state->glass3 = 0;
    return cur_state->glass3 = 1;
}
int flip_4(State *cur_state) {
    if(cur_state->glass4 == 1)
        return cur_state->glass4 = 0;
    return cur_state->glass4 = 1;
}
int flip_5(State *cur_state) {
    if(cur_state->glass5 == 1)
        return cur_state->glass5 = 0;
    return cur_state->glass5 = 1;
}
int flip_6(State *cur_state) {
    if(cur_state->glass6 == 1)
        return cur_state->glass6 = 0;
    return cur_state->glass6 = 1;
}
int flip_123(State cuz_state, State* result) {
    if(cuz_state.glass1 + cuz_state.glass2 + cuz_state.glass3 == 3)
        return 0;
    result->glass1 = flip_1(&cuz_state);
    result->glass2 = flip_2(&cuz_state);
    result->glass3 = flip_3(&cuz_state);
    result->glass4 = cuz_state.glass4;
    result->glass5 = cuz_state.glass5;
    result->glass6 = cuz_state.glass6;
    return 1;
}
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
int call_operator(State cuz_state, State*result, int option) {
    switch(option){
        case 1: return flip_234(cuz_state, result);
        case 2: return flip_456(cuz_state, result);
        case 3: return flip_345(cuz_state, result);
        case 4: return flip_123(cuz_state, result);
        default : printf("Loi!");
            return 0;
    }
}
typedef struct Node {
    State state;
    struct Node* Parent; //(0,4) se lam cha cua (9,4)
    int no_function;
}Node;
int compareStates(State A, State B) {
    return (A.glass1==B.glass1) && (A.glass2==B.glass2) && (A.glass3==B.glass3) && (A.glass4==B.glass4) && (A.glass5==B.glass5) && (A.glass6==B.glass6);
}
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
    if(empty_Queue(queue)){
        printf("Queue rong!");
    }
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
    State cuz_state = {1,0,1,0,1,0};
    Node* p = BFS_Algorithm(cuz_state);
    print_WaysToGetGoal(p);
    return 0;
}
