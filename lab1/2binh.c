#include <stdio.h>
#include <stdlib.h>
const char* action[] = {
    "First State", "pour Water Full X", "pour Water Full Y", "pour Water Empty X",
    "pour Water Empty Y", "pour Water X to Y", "pour Water Y to X"
};
#define tankX 9
#define tankY 4
#define empty 0
#define goal 6
#define Maxlength 100
typedef struct {
    int x,y;
}State;
void makenullstate(State *S){
    S->x=0;
    S->y=0;
}
void print_state(State s){
    printf("\n X:%d --- Y:%d", s.x, s.y);
}
int goalcheck(State s){
    return (s.x == goal || s.y == goal);
}
int min(int a, int b){
    return a<b ? a : b;
}
int max(int a, int b){
    return a>b ? a : b;
}
int pourWaterFullX(State cuz_state, State *result){
    if(cuz_state.x < tankX){
        result->x=tankX;
        result->y = tankY;
        return 1;
    }
    return 0;
}
int pourWaterFullY(State cuz_state, State *result){
    if(cuz_state.y < tankY){
        result->y = tankY;
        result->x= tankX;
        return 1;
    }
    return 0;
}
int pourWaterEmptyX(State cuz_state, State *result){
    if(cuz_state.x>0){
        result->x=empty;
        result->y = cuz_state.y;
        return 1;
    }
    return 0;
}
int pourWaterEmptyY(State cuz_state, State *result){
    if(cuz_state.y>0){
        result->y=empty;
        result->x = cuz_state.x;
        return 1;
    }
    return 0;
}
int pourWaterXY(State cuz_state, State *result){
    if(cuz_state.x>0 && cuz_state.y < tankY){
        result->x = max(cuz_state.x - (tankY - cuz_state.y), empty);
        result->y=  min(cuz_state.x + cuz_state.y, tankY);
        return 1;
    }
    return 0;
}
int pourWaterYX(State cuz_state, State *result){
    if(cuz_state.y>0 && cuz_state.x < tankX){
        result->y = max(cuz_state.y - (tankX - cuz_state.x), empty);
        result->x=  min(cuz_state.y + cuz_state.x, tankX);
        return 1;
    }
    return 0;
}
int call_operator(State cuz_state, State *result, int opt){
    switch(opt){
        case 1: return pourWaterFullX(cuz_state, result);
        case 2: return pourWaterFullY(cuz_state, result);
        case 3: return pourWaterEmptyX(cuz_state, result);
        case 4: return pourWaterEmptyY(cuz_state, result);
        case 5: return pourWaterXY(cuz_state, result);
        case 6: return pourWaterYX(cuz_state, result);
        default: printf("erros");
        return 0;
    }
}
int main(){
    State cuz_state = {5,4}, result;
    printf("Trang thai bat dau:");
    print_state(cuz_state);
    int opt;
    for(opt = 1; opt<=6; opt++){
        int thuchien=call_operator(cuz_state, &result, opt);
        if(thuchien==1){
            printf("Hanh dong %s thanh cong\n", action[opt]);
            print_state(result);
        }else 
            printf("Hanh dong %s ko thanh cong\n", action[opt]);

    }
    return 0;
}
