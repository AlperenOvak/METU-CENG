#include <stdio.h>
#include "lab_2.h"

int main(){
    /* Initialize your own inputs like this */
    int ObjA[6]={0,0,1,1,2,2};
    int ObjB[6]={0,2,1,1,2,0};
    int TranslateCommands[2]={2,0};
    int i;
    
    /* Call any function that you have implemented in lab_2.c and test the results */
    eraseCollisions(3, 3,
                     ObjA,  ObjB,
                     3, 3,
                     TranslateCommands, 1);
    printf("\ncompleted\n");
    for(i=0;i<2;i++){
        ObjA[i]=TranslateCommands[1]+ObjB[i];
        printf("%d",ObjA[i]);
    }
    /* Print updated contents of arr */
    
    return 0;
}