#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"


int str2int(char *numStr)  /* char string to int */
{
    int intVal=0 ;

    while(*numStr != '\0')
    {
        intVal *= 10;
        intVal  += *numStr - '0'; /*0x30 ascii value of charater 0 */
        numStr++;
    } 
    return intVal;
}

void swap(struct DomainFreqNode *a, struct DomainFreqNode *b) /*swap the DomainFreqNode for sorting*/
{ 
    int temp_f = a->freq;   /* I prefer to change their values not "next" "prev" adresses*/
    char* temp_n=a->name;
    a->freq = b->freq; 
    a->name = b->name;
    b->freq = temp_f; 
    b->name = temp_n;
} 

/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{
    int Count,Limit,i,crntSize=0,size_of_media;
    char *buf=malloc(sizeof(char) * 1000) ,*token,delimiters[] = "  ",*media_name;  
    CacheNode* temp,*prev_temp=NULL;

    Cache* cache = (Cache*)malloc(sizeof(Cache));
    DomainFreqList* freqList;
    
    cache->head = (CacheNode*)malloc(sizeof(CacheNode));
    scanf("%d %d\n",&Limit,&Count);
    

    cache->mediaCount=Count;
    cache->cacheLimit=Limit;
    temp=cache->head;
    (cache->head)->prev=NULL;

    for(i=0;i<Count;i++){  /* Create each CacheNode one by one */
        if(Count-i==1){
            temp->next=NULL;
            cache->tail=temp;
        }else{
            temp->next=(CacheNode*)malloc(sizeof(CacheNode));
        }
        temp->prev=prev_temp;


        fgets(buf, 1000, stdin);
        buf[strcspn(buf, "\n")] = '\0'; 
        /*printf("You entered: %s", buf);*/
        
        token = strtok(buf, delimiters);
        (temp->media).name=token;   
        token = strtok(NULL, delimiters);
        (temp->media).size= str2int(token);
        token = strtok(NULL, delimiters);
        printf("reached to media : %s %d\n",(temp->media).name,(temp->media).size);

        temp->domainFreqList=(DomainFreqList*)malloc(sizeof(DomainFreqList));
        freqList=temp->domainFreqList;
        freqList->head=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        while (token != NULL) {
            printf("%s ", token);
            token = strtok(NULL, delimiters);
            printf("%d ", str2int(token));





            
            token = strtok(NULL, delimiters);
        }
        printf("\n");
    }
    
    cache->currentSize=crntSize;
    
    return cache;
}

/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{

}


/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{
    return NULL;
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    return NULL;
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{
    
}

int main(){
    createCache();
    return 0;
}