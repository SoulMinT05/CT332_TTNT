#include <stdio.h>
#include <stdlib.h>
#define mRow 4
#define mCol 4
const char* action[] = {"Null","Plus","Minus","Multiplication","division"} ;
typedef struct {
    int row;
    int col;
}Coord;
typedef struct{
    Coord list[20];
    int len ;
}ListCoord ;
void initListCoord(ListCoord *L){
    L->len = 0;
}
void append(ListCoord *L,Coord C){
    L->list[L->len] = C ;
    L->len++;
}
Coord pop(ListCoord* L){
    L->len-- ;
    return L->list[L->len];
}
typedef struct{
	int listArr[20][5];
	int len;
}ListA;
void initListA(ListA *L){
	L->len = 0;
}
typedef struct{
    int result, operator, isFiLL;
    ListCoord data;
    ListA available;
}Cage; 
void initCage(Cage* cage){
    cage->result = 0;
    initListCoord(&cage->data);
    cage->operator = 0;
    initListA(&cage->available);
    cage->isFiLL = 0;
}
void addToCage(Cage* cage,Coord C){
    append(&cage->data,C);
}
typedef struct {
    int len;
    Cage list[20];
}ListCage;
void initListCage(ListCage* LC){
    LC->len = 0;
}
void appendCage(ListCage* LC,Cage cage){
    LC->list[LC->len] = cage;
    LC->len++;
}
typedef struct {
    int data[4][4];
    ListCage lCage;
}State;
void initState(State *S){
    int row,col;
    for(row=0;row<mRow;row++)
        for(col=0;col<mCol;col++)
            S->data[row][col] = 0 ;
    initListCage(&S->lCage);
}
void showState(State S){
    printf(" --------- SHOW STATE --------- \n");
    int i,j;
    for(i=0;i<mRow;i++){
        for(j=0;j<mCol;j++)
            printf("%2d ",S.data[i][j]);
        printf("\n");
    }
}
void showCage(Cage C){
    printf("-------Show Cage----- \n");
    printf("Number Of Coord : %d \n",C.data.len);
    printf("Result : %d \n",C.result);
    printf("Operation : %s \n" , action[C.operator]);
    printf("Available Len : %d \n",C.available.len);
    int i,j; 
    printf("Available : \n");
    for(i=0;i<C.available.len;i++){
    	for(j=0;j<C.data.len;j++)
    		printf(" %d ",C.available.listArr[i][j]);
    	printf("\n");
	}
}
int isValid(State S,Coord C,int input){
    int row = C.row;
    int col = C.col;
    int i;
    for(i=0;i<mRow;i++){
        if(i!=col && S.data[row][i] == input) return 0;
        if(i!=row && S.data[i][col] == input) return 0;
    }
    return 1;
}
void getAvailableCage(Cage *C){
    int len = C->data.len ;
    int operator = C->operator ;
    int result = C->result ;
	ListA available ; initListA(&available);
    int i,j,k,u;
    if(len == 1){
        int lenA = C->available.len; 
        C->available.listArr[lenA][0] = C->result;
        C->available.len++;
    }
    if(len == 2){
        for(i=1;i<=4;i++)
            for(j=1;j<=4;j++)
                if((operator == 1 && i+j == result)||
                    (operator == 2 && i-j == result)||
                    (operator == 3 && i*j == result)||
                    (operator == 4 && (float)i/j == (float)result))
                {
                    int lenA = C->available.len ; 
                    C->available.listArr[lenA][0] = i ;
                    C->available.listArr[lenA][1] = j ;
                    C->available.len++;
                    if(operator == 2 || operator == 4){
                        C->available.listArr[lenA+1][0] = j ;
                        C->available.listArr[lenA+1][1] = i ;
                        C->available.len++;
                    }
                }
    }
    else if(len == 3){
        for(i=1;i<=4;i++)
            for(j=1;j<=4;j++)
                for(k=1;k<=4;k++)
                    if((operator == 1 && i+j+k == result)||
                        (operator == 2 && i-j-k == result)||
                        (operator == 3 && i*j*k == result)||
                        (operator == 4 && (float)i/j/k == (float)result))
                    {
                       int lenA = C->available.len ; 
                        C->available.listArr[lenA][0] = i ;
                        C->available.listArr[lenA][1] = j ;
                        C->available.listArr[lenA][2] = k ;
                        C->available.len++;
                        if(operator == 2 || operator == 4)
                        {
                            //Hoan Vi Case DIV va MINUS
                        }
                    }
    }
}
int isFilled(State S){
    int i,j;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
            if(S.data[i][j] == 0) return 0;
    return 1;
}
int checkCage(State S,Cage C){
    if(C.data.len == 1) return (S.data[C.data.list[0].row][C.data.list[0].col] == C.result);
    if(C.data.len == 2){
        Coord X1 = C.data.list[0] ;
        Coord X2 = C.data.list[1] ;
        int i = S.data[X1.row][X1.col];
        int j = S.data[X2.row][X2.col];
        if((C.operator == 1 && i+j == C.result)||
            (C.operator == 2 && i-j == C.result)||
            (C.operator == 3 && i*j == C.result)||
            (C.operator == 4 && (float)i/j == (float)C.result))
                return 1;
        return 0 ;
    }
    if(C.data.len == 3){
        Coord X1 = C.data.list[0] ;
        Coord X2 = C.data.list[1] ;
        Coord X3 = C.data.list[2] ;
        int i = S.data[X1.row][X1.col];
        int j = S.data[X2.row][X2.col];
        int k = S.data[X3.row][X3.col];
        if((C.operator == 1 && i+j+k == C.result)||
            (C.operator == 2 && i-j-k == C.result)||
            (C.operator == 3 && i*j*k == C.result)||
            (C.operator == 4 && (float)i/j/k == (float)C.result))
                return 1;
        return 0 ;
    }
    return -1 ;
}
int getNextCage(State S){
    int i; int min = 99 ;
    int output = -1;
    int lenCage = S.lCage.len;
    for(i=0;i<lenCage;i++)
        if(S.lCage.list[i].available.len < min && !S.lCage.list[i].isFiLL){
            output = i ;
            min = S.lCage.list[i].available.len ;
        }
    return output;
}
int count;
int backTracking(State *S){
    if(isFilled(*S)) return 1;
    int inext = getNextCage(*S);
    Cage next = S->lCage.list[inext] ;
    S->lCage.list[inext].isFiLL = 1;
    if(inext == -1) return 0;
    int i,j,k; 
    for(i=0;i<next.available.len;i++){
        State back = *S;
        for(j=0;j<next.data.len;j++){
            Coord X = next.data.list[j];
            S->data[X.row][X.col] = next.available.listArr[i][j];
        }
        count++;
        for(j=0;j<next.data.len;j++)
            if(!isValid(*S,next.data.list[j],next.available.listArr[i][j])){
                *S = back;
                continue;
            }
            if(backTracking(S)) return 1;
                *S = back ;
    }   
    S->lCage.list[inext].isFiLL = 1;
    return 0;
}
int main(){
    printf("\n\n Play KenKen Game Parse One\n");
    State start;
    initState(&start);
    Coord X1 = {0,0};
    Coord X2 = {0,1};
    ListCoord L1 ;

    Cage C1 ; initCage(&C1);
    addToCage(&C1,X1);
    addToCage(&C1,X2);
    C1.operator = 4;
    C1.result = 2;
    appendCage(&start.lCage,C1);
    Coord X3 = {0,2};
    Coord X4 = {1,2};

    Cage C2 ; initCage(&C2);
    addToCage(&C2,X3);
    addToCage(&C2,X4);
    C2.operator = 1;
    C2.result = 7;
    appendCage(&start.lCage,C2);
    Coord X5 = {0,3};
    
    Cage C3 ; initCage(&C3);
    addToCage(&C3,X5);
    C3.operator = 0;
    C3.result = 4;
    appendCage(&start.lCage,C3);

    Cage C4 ; initCage(&C4);
    Coord X6 = {1,0};
    addToCage(&C4,X6);
    Coord X7 = {2,0};
    addToCage(&C4,X7);
    C4.operator = 2;
    C4.result = 1;
    appendCage(&start.lCage,C4);

    Cage C5 ; initCage(&C5);
    Coord X8 = {1,1};
    Coord X9 = {2,1};
    addToCage(&C5,X8);
    addToCage(&C5,X9);
    C5.operator = 2;
    C5.result = 3;
    appendCage(&start.lCage,C5);

    Cage C6 ; initCage(&C6);
    Coord X10 = {2,2};
    Coord X11 = {3,2};
    Coord X12 = {3,3};
    addToCage(&C6,X10);
    addToCage(&C6,X11);
    addToCage(&C6,X12);
    C6.operator = 3;
    C6.result = 4;
    appendCage(&start.lCage,C6);

    Cage C7 ; initCage(&C7);
    Coord X13 = {1,3};
    Coord X14 = {2,3};
    addToCage(&C7,X13);
    addToCage(&C7,X14);
    C7.operator = 2;
    C7.result = 2;
    appendCage(&start.lCage,C7);

    Cage C8 ; initCage(&C8);
    Coord X15 = {3,0};
    Coord X16 = {3,1};
    addToCage(&C8,X15);
    addToCage(&C8,X16);
    C8.operator = 2;
    C8.result = 1;
    appendCage(&start.lCage,C8);

    int i;
    for(i=0;i<start.lCage.len;i++)
        getAvailableCage(&start.lCage.list[i]);
    showState(start);
    count = 0;
    backTracking(&start);
    printf("RunTimes : %d\n",count);
    showState(start);
    return 0;
}