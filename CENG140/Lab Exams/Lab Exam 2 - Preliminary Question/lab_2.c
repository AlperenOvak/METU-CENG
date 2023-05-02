#include <math.h>
#include <stdio.h>

#include "lab_2.h"

/*
    This function takes:
        - vector that is array of floats (vec)
        - the size of the array (size)
    as parameters and returns the length of the vector
    that is given in the description
*/
float length(float vec[], int size)
{
    int i;
    float result = 0.0;
    for(i=0;i<size;i++){
        result+=vec[i]*vec[i];
    }
    result=sqrt(result);
    
    /* WRITE YOUR CODE HERE */
    
    return result;
}


/*
    This function takes:
        - vec1 (array of floats)
        - vec2 (array of floats)
        - size (size of vec1 and vec2)
    as parameters and returns the dot product
    of vec1.vec2 that is given in the description
*/
float dot(float vec1[], float vec2[], int size)
{
    float result = 0.0;
    int i;
    for(i=0;i<size;i++){
        result+=vec1[i]*vec2[i];
    }
    
    return result;
}

/*
    This function takes:
        - vertices -> 2D vertex coordinates of an object (V1x, V1y, V2x, V2y, .... Vnx,Vny)
        - vertexCount -> how many vertices does the object have (Note: size of vertices array becomes vertexCount * 2)
        - commands -> Array of translation commands (C1x, C1y, C2x, C2y, ... Cnx, Cny)
        - commandCount -> how many commands exist (Note: size of commands array becomes commandCount * 2)
        
    You will print the resulting vertices as it is explained in the description. You just have to print the output using "printf"
    
     DO NOT TRY TO RETURN ANYTHING WITH THIS FUNCTION. THIS FUNCTION HAS VOID RETURN TYPE
*/
void translateVertices(float vertices[], int vertexCount, float commands[], int commandCount)
{
    int i;
    float x_p=0,y_p=0;
    for(i=0;i<commandCount*2;i+=2){
        x_p+=commands[i];
        y_p+=commands[i+1];
        
    }
    /*for(i=0;i<vertexCount*2;i++){
        printf("v[%d]=%f ",i,vertices[i]);
    }
    for(i=0;i<commandCount*2;i++){
        printf("c[%d]=%f ",i,commands[i]);
    }
    printf("\n%f %f\n",x_p,y_p);*/
    for(i=0;i<vertexCount*2;i++){
        if(i%2==0){
            vertices[i]+=x_p;
        }else{
            vertices[i]+=y_p;
        }
        if(i==vertexCount*2-1){
            printf("%.2f",vertices[i]);
        }else{
            printf("%.2f ",vertices[i]);
        }
    }
}

/*
    This function takes:
        - A -> 2D Vertex coordinates of object A
        - vertexCountA -> how many vertices does the object have (Note: size of A becomes vertexCountA * 2)
        - B -> 2D Vertex coordinates of object B
        - vertexCountB -> how many vertices does the object have (Note: size of B becomes vertexCountB * 2)
        - rowSize -> how many rows does the grid have
        - columnSize -> how many columns does the grid have
        
    You will print the 2D Grid as it is explained in the description. You just have to print the output using "printf"
    
    DO NOT TRY TO RETURN ANYTHING WITH THIS FUNCTION. THIS FUNCTION HAS VOID RETURN TYPE

*/
void visualizeObjects(int A[], int vertexCountA,
                      int B[], int vertexCountB,
                      int rowSize, int columnSize)
{
  int i,j,k,l,cross;
  for(i=0;i<rowSize;i++){
      for(j=0;j<columnSize;j++){
          cross=0;
          for(k=0;k<vertexCountA*2;k+=2){
              if(j==A[k+1] && i==A[k]){
                  cross++;
                  
              }
          }
          for(l=0;l<vertexCountB*2;l+=2){
              if(j==B[l+1] && i==B[l]){
                  cross+=2;
                  
              }
          }
          
          
          if(j==columnSize-1){
            if(cross==3){
                printf("x");
            }else if(cross==2){
                printf("b");
            }else if(cross==1){
                printf("a");
            }else{
                printf("-");
            } 
            if(i==rowSize-1){
                j++;
            }else{
                printf("\n");
            }
            
          }else{
            if(cross==3){
                printf("x  ");
            }else if(cross==2){
                printf("b  ");
            }else if(cross==1){
                printf("a  ");
            }else{
                printf("-  ");
            }    
          }
          
          
      }
      
      
  }
}


