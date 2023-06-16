#include <stdio.h>
#include <stdlib.h>

int is_first_path_founded=0;

int path_finder(char** copy,char** matrix, int x, int y, int length,int depth){
    int exit_f=0,exit_1,exit_2,exit_3,exit_4;
    if((x==0 || y==0 || x==depth-1 || y==length-1)){
            if(matrix[x][y]==' '){
                copy[x][y]='.';
                exit_f=1;
                is_first_path_founded=1;
                matrix[x][y]='*';
                return(exit_f);
            }else{
                return 0;
            }
    }else{
        if(copy[x][y]=='X' || copy[x][y]=='.' || is_first_path_founded==1){
            return 0;
        }else{
            copy[x][y]='.';
            exit_1=path_finder(copy,matrix,x-1,y,length,depth);
            exit_2=path_finder(copy,matrix,x,y+1,length,depth);
            exit_4=path_finder(copy,matrix,x,y-1,length,depth);
            exit_3=path_finder(copy,matrix,x+1,y,length,depth);
            
            
            exit_f=(exit_1 || exit_2 || exit_3 || exit_4);
        }
        if(exit_f==1){
            matrix[x][y]='*';
        }
    }
    return(exit_f);
}

void print_matrix(char** matrix,int length, int depth){
    int i,j;
    for(i=0;i<depth;i++){
            for(j=0;j<length;j++){
                printf("%c",matrix[i][j]);
            }
            printf("\n");
        }
}

int main() {
    char **matrix,**copy;
    char line[33333];
    char c;
    int length = 0,depth=0,i,j,l2,b=0,x,y, bool_find;
    
    scanf("%d %d\n",&y,&x);
    
    /* Taking the matrix as an input altough its size is not given*/
    while ((c = getchar()) != '\n' && c != EOF) {
        length++;
        line[length-1] = c; 
    }
    matrix=(char**)malloc(1*sizeof(char*));
    matrix[depth]=(char*)malloc(length*sizeof(char));
    for(i=0;i<length;i++){
        matrix[depth][i]=line[i];
    }
    depth++;
    while(1){
        l2=0;
        while ((c = getchar()) != '\n') {
            if(c == EOF){
                b++;
                break;
            }
            l2++;
            line[l2-1] = c; 
        } 
        if(b){
            break;
        }
        matrix=(char**)realloc(matrix,(depth+1)*sizeof(char*));
        matrix[depth]=(char*)malloc(l2*sizeof(char));
        for(i=0;i<l2;i++){
            matrix[depth][i]=line[i];
        }
        depth++;
    }
    
    copy=(char**)malloc(depth*sizeof(char*));
    for(i=0;i<depth;i++){
        copy[i]=(char*)malloc(length*sizeof(char));
        
        for(j=0;j<length;j++){
            copy[i][j]=matrix[i][j];
        }
    }

    bool_find=path_finder(copy,matrix,x,y,length,depth); 
    /*printf("bool find=%d\n",bool_find);*/
    if(bool_find==0){   
        print_matrix(copy,length,depth);
    }else{
        print_matrix(matrix,length,depth);
    }
    

    return 0;
}
