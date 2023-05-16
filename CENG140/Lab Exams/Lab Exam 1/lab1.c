#include <stdio.h>

/*
    This function takes 4 inputs from stdin and prints 
    in the string given in description
*/
void hello_ceng(){
    int course_code,lab_exam_count ;
    float point1,point2;
    scanf(" %d %d %f %f",&course_code,&lab_exam_count,&point1,&point2);
    printf("I got %.2f from the first and %.2f from the second lab exam of CENG%d.\n",point1,point2,course_code);
    printf("There will be %d lab exams in total.\n",lab_exam_count);
    printf("If I get two zero grades in the forthcoming lab exams, I'm going to get NA.");
}

/* 
    This function takes an integer from stdin
    and checks if it is a square of an integer or not
*/
void square_check(){
    int num,i,count;
    scanf("%d",&num);
    for(i=0;i<=(num);i++){
        if(i*i==num){
            printf("Square of %d",i);
            count++;
        }
    }
    if(count==0){
        printf("Not a square");
    }
}

/*
    This function takes a number N and N integers after that. Checks if the
    given series is a zigzag and narrowing or not.
*/
void zigzag_check(){
    int num,nums[999];
    int i,j;
    int zigzag=1;
    int narrowing=1;
    scanf(" %d",&num);
    
    for(i=0;i<num;i++){
        scanf("%d",&nums[i]);
    }
    
    for(j=3;j<(num);j+=2){                    /*narrowing*/
        if(nums[j]<=nums[j-2]){
            narrowing=0;
        }
        if(nums[j-1]>=nums[j-3]){
            narrowing=0;
        } 
    }
    
    for(i=1;i<(num-1);i+=2){
        if(nums[i-1]>nums[i] && nums[i]<nums[i+1]){     /*zigzag*/
            zigzag=1;
        }else{
            zigzag=0;
        }
    }
    if(num%2==0){
        if(nums[num-2]<=nums[num-1]){
            zigzag=0;
        }
    }
    
    if(zigzag==1 && narrowing==1){
        printf("Narrowing zigzag");
    }else if(zigzag==1){
        printf("Zigzag but not narrowing");
        
    }else{
        printf("Not a zigzag");
    }
    
    
}

/*
    This function takes a number N and N floating-points after that. Takes
    3 more floating points. Calculates the average grade using N+3 grades.
    Prints letter grades of the last 3 grades.
*/
void letter_grades(){
    int N,i;
    float grades[999],total=0,avg,letter[3];
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf(" %f",&grades[i]);
        total+=grades[i];
    }
    scanf("%f",&letter[0]);
    scanf("%f",&letter[1]);
    scanf("%f",&letter[2]);
    total+=letter[0]+letter[1]+letter[2];
    
    avg=total/(N+3);
    printf("Average: %.2f. Letter grades:",avg);
    
    for(i=0;i<3;i++){
        
        if(letter[i]-avg<-20){
            printf(" FF");
        }else if(letter[i]-avg<-15){
            printf(" FD");
        }else if(letter[i]-avg<-10){
            printf(" DD");
        }else if(letter[i]-avg<-5){
            printf(" DC");
        }else if(letter[i]-avg<5){
            printf(" CC");
        }
        
        if(letter[i]-avg>=20){
            printf(" AA");
        }else if(letter[i]-avg>=15 ){
            printf(" BA");
        }else if(letter[i]-avg>=10){
            printf(" BB");
        }else if(letter[i]-avg>=5){
            printf(" CB");
        }
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}