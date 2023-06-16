#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3.h"


/*
This function prints journals and their article counts in specified format.
*/
void printJournalArticleCounts(Journal* journals, int numJournals) {
    int i,count=0;
    Article* ArtWant;
    printf("Journal article counts:\n");
    for(i=0;i<numJournals;i++){
        count=0;
        ArtWant=journals[i].articles;
        while(ArtWant != NULL){
            ArtWant=ArtWant->next;
            count++;
        }
        printf("- %s: %d articles\n",journals[i].name,count);
    }
    
}

/*
This function adds a new journal instance to the existing dynamic array of journals.
*/
void insertNewJournal(Journal** journals, int* numJournals, char* name) {
    
    *journals=realloc(*journals,(*numJournals+1)*sizeof(Journal));
    strcpy((*journals)[*numJournals].name,name);
    (*journals)[*numJournals].articles=NULL;
    (*numJournals)++;
}

/*
This function adds a new article node to specified journal given as an argument.
*/
void insertNewArticleInAlphabeticOrder(Journal* journals, int numJournals, char* journalName, char* articleName) {
    int i;
    Article* newArticle,*current;
    for(i=0;i<numJournals;i++){
        if(strcmp(journals[i].name,journalName)==0){
            newArticle=(Article*)malloc(sizeof(Article));
            strcpy(newArticle->name,articleName);
            newArticle->next=NULL;
            if(journals[i].articles==NULL || strcmp(journals[i].articles->name,articleName)>0){
                newArticle->next=journals[i].articles;
                journals[i].articles=newArticle;
            }else{
                current=journals[i].articles;
                while(current->next!=NULL && strcmp(current->next->name,articleName)<0){
                    current=current->next;
                }
                newArticle->next=current->next;
                current->next=newArticle;
            }
            break;
        }
    }
}

/*
This function adds a new author entry to specified journal's specified article given as arguments.
*/
void insertNewAuthor(Journal* journals, int numJournals, char* journalName, char* articleName, char* authorName){
    int i, numAut;
    Article* current;
    for(i=0;i<numJournals;i++){
        if(strcmp(journals[i].name,journalName)==0){
            current=journals[i].articles;
            while(current->next!=NULL && strcmp(current->name,articleName)!=0){
                current=current->next;
            }
            numAut=current->numAuthors;
            current->authors=realloc(current->authors,(numAut+1)*sizeof(char));
            (current->authors)[numAut]=(char*)malloc(sizeof(authorName));
            strcpy((current->authors)[numAut],authorName);
            
            (current->numAuthors)++;
            break;
        }
    }
}

/*
This function finds articles belong to given authorName, and prints them in explained format.
*/
void findArticlesByAuthor(Journal* journals, int numJournals, char* authorName){
     int i,j,numAut;
     Article* temp_art;
     printf("Articles by author %s:\n",authorName);
     for(i=0;i<numJournals;i++){
         temp_art=journals[i].articles;
         if(temp_art!=NULL){
            while(temp_art!=NULL){
                numAut=temp_art->numAuthors;
                for(j=0;j<numAut;j++){
                    if(strcmp((temp_art->authors)[j],authorName)==0){
                        printf("- %s (%s)\n",temp_art->name,journals[i].name);
                    }
                    
                }
                temp_art=temp_art->next;
            }
         }
     }
}



















