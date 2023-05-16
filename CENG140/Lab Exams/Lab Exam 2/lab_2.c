#include <math.h>
#include <stdio.h>

#include "lab_2.h"


/*
    This function takes:
        - array of floats (Arr)
        - the size of the array (size)
    as parameters and modifies the contents of Arr with
    normalized values as explained in the description
*/
void minMaxNorm(float Arr[], int size)
{
    int i;
    float max=0,min=200;
    for(i=0;i<size;i++){
        if(Arr[i]>max){
            max=Arr[i];
        }
        if(Arr[i]<min){
            min=Arr[i];
        }
    }
    for(i=0;i<size;i++){
        Arr[i]=(Arr[i]-min)/(max-min);
    }
    
}

/*
    This function takes:
        - data of 3D vectors (Vecs)
        - number of 3D vectors inside array Vecs (vecSize)
        - a 3D vector to be compared with vectors of Vecs array (Comp)
    as parameters and PRINTS
        - the 3D vector inside "Vecs" that has the highest similarity
          score with the "Comp" vector
        - index of the vector with highest similarity score
*/
void cosineSimilarity(float Vecs[], int vecSize, float Comp[])
{
    int i,index=0;
    float cossim=0,dot,lng,cos;
    for(i=0;i<vecSize;i++){
        dot=(Vecs[i*3]*Comp[0]+Vecs[i*3+1]*Comp[1]+Vecs[i*3+2]*Comp[2]);
        lng=sqrt(Vecs[i*3]*Vecs[i*3]+Vecs[i*3+1]*Vecs[i*3+1]+Vecs[i*3+2]*Vecs[i*3+2])*sqrt(Comp[0]*Comp[0]+Comp[1]*Comp[1]+Comp[2]*Comp[2]);
        cos=dot/lng;
        if(cos>cossim){
            cossim=cos;
            index=i;
        }
    }
    printf("V%d %.4f",index+1,cossim);
}

/*
    This function takes:
        - width of the frame (width)
        - height of the frame (height)
        - 2D vertices of ObjA (ObjA)
        - 2D vertices of ObjB (ObjB)
        - 2D translate commands for the camera (TranslateCommands)
    as parameters and prints the resulting 2D grid as explained in the description
*/
void eraseCollisions(int n, int m,
                     int ObjA[], int ObjB[],
                     int width, int height,
                     int TranslateCommands[], int commandCount)
{
    int i,j,trnx=0,trny=0;
    char C[11][11];
    
    for(i=0;i<11;i++){         /*create a empty 2D array*/
        for(j=0;j<11;j++){
            C[i][j]='-';
        }
    }
    
    for(i=0;i<commandCount;i++){         /*Find the net translatecommand*/
        trnx-=TranslateCommands[i*2];
        trny-=TranslateCommands[i*2+1];
    }
    
    for(i=0;i<n;i++){        /*Apply it to ObjA*/
        ObjA[i*2]+=trnx;
        ObjA[i*2+1]+=trny;
    }

    for(i=0;i<m;i++){       /*Apply it to ObjB*/
        ObjB[i*2]+=trnx;
        ObjB[i*2+1]+=trny;
    }
    
    for(i=0;i<n;i++){       /*Put 'a's into the empty C array*/
        if(ObjA[i*2+1]>-1 && ObjA[i*2]>-1 ){
           C[ObjA[i*2+1]][ObjA[i*2]]='a'; 
        }
    }
    for(i=0;i<m;i++){       /*Put 'b's into the empty C array*/
    
        if(ObjB[i*2+1]>-1 && ObjB[i*2]>-1 ){
            if(C[ObjB[i*2+1]][ObjB[i*2]]!='a'){
                C[ObjB[i*2+1]][ObjB[i*2]]='b';
            }else{
                C[ObjB[i*2+1]][ObjB[i*2]]='-';
            } 
        }
        
    }
    
    for(i=0;i<height;i++){       /*Print*/
        for(j=0;j<width;j++){
            if(j==width-1){
                printf("%c",C[i][j]);
            }else{
                printf("%c  ",C[i][j]);
            }
        }
        if(i!=height-1){
            printf("\n");
        }
    }
}































