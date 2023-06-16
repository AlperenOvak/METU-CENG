#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"


void addNode2Head(CacheNode* current,CacheNode* neww ,Cache* cache){
    (cache->mediaCount)++;
    cache->currentSize+=(neww->media).size;
    if(current==NULL){
        cache->head=neww;
        cache->tail=neww;
        neww->next=NULL;
        neww->prev=NULL;
    }else{
        neww->next=current;    /* ya boş cache gelirse ve ekleme yapman lazımsa*/
        neww->prev=current->prev;
        if(current->prev!=NULL){
            current->prev->next=neww;
        }else{
            cache->head=neww;
        }
        current->prev=neww;
    }
    
}

CacheNode* ejectNode(CacheNode* current ,Cache* cache){  /* ya baştaysa ya da sondaysa*/
    (cache->mediaCount)--;
    cache->currentSize-=current->media.size;
    if(current->prev!=NULL){
        current->prev->next=current->next;
    }else{
        cache->head=current->next;
    }
    if(current->next!=NULL){
        current->next->prev=current->prev;
    }else{
        cache->tail=current->prev;
    }
    return current;
}

void createListNode(DomainFreqNode* new,int freq, char* name){
    new->name=name;
    new->freq=freq;    
}


void addFreq2List(DomainFreqNode* current,DomainFreqNode* new,DomainFreqList* freqList){

    new->prev=current->prev;
    if(new->prev==NULL){
        freqList->head=new;
    }else{
        current->prev->next=new;
    }
    current->prev=new;
    new->next=current;
    if(new->prev==NULL){
        freqList->head=new;
    }
}

DomainFreqNode* ejectFreq(DomainFreqNode* current,DomainFreqList* freqList){
    if(current->prev!=NULL){
        current->prev->next=current->next;
    }else{
        freqList->head=current->next;
    }
    
    
    if(current->next!=NULL){
        current->next->prev=current->prev;
    }else{
        freqList->tail=current->prev;
    }
    if(freqList->head==NULL && freqList->tail==NULL){
    }
    return current;
}

void addFreq2Tail(DomainFreqNode* current,DomainFreqNode* new,DomainFreqList* freqList){

    new->next=current->next;
    current->next=new;
    new->prev=current;

    if(new->next==NULL){
        freqList->tail=new;
    }
}

void sortFreqList(DomainFreqNode* neww,DomainFreqList* freqList){
    int sorted=0;
    DomainFreqNode* temp_freq;
    temp_freq=freqList->head;

    while(temp_freq!=NULL){
        if(neww->freq > temp_freq->freq){
            sorted++;
            addFreq2List(temp_freq,neww,freqList);
            break;
            
        }else if(neww->freq == temp_freq->freq){
            if(strcmp(neww->name, temp_freq->name)>0){
                temp_freq=temp_freq->next;
            }
            else{
                sorted++;
                addFreq2List(temp_freq,neww,freqList);
                break;
            }
        }else{
            temp_freq=temp_freq->next;
        }    
    }
    if(sorted==0 && freqList->head!=NULL ){ 
        addFreq2Tail(freqList->tail,neww,freqList);
    }
    
    if(freqList->head==NULL){
        freqList->head=neww;
        freqList->tail=neww;
    }
}
/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{
    int Count,Limit,i,crntSize=0, freq,freqcount;
    char *buf,*token,delimiters[] = "  ", *url;  
    CacheNode* temp,*prev_temp=NULL;
    DomainFreqNode* new,*temp_freq;

    Cache* cache = (Cache*)malloc(sizeof(Cache));
    DomainFreqList *freqList;
    scanf("%d %d\n",&Limit,&Count);
    
    cache->head = (CacheNode*)malloc(sizeof(CacheNode));
    cache->mediaCount=Count;
    cache->cacheLimit=Limit;
    temp=cache->head;

    for(i=1;i<=Count;i++){  /* Create each CacheNode one by one */
        freqcount=0;
        if(Count==i){
            temp->next=NULL;
            cache->tail=temp;
        }
        else{
            temp->next=(CacheNode*)malloc(sizeof(CacheNode));
        }
        
        temp->prev=prev_temp;

        buf=malloc(sizeof(char) * 1000);
        fgets(buf, 1000, stdin);
        buf[strcspn(buf, "\n")] = '\0'; 


        token = strtok(buf, delimiters);
        (temp->media).name=(char*)malloc(sizeof(char));
        (temp->media).name=token;   
        token = strtok(NULL, delimiters);
        (temp->media).size= atoi(token);
        crntSize+=(temp->media).size; /* increment Size of cache*/
        
        temp->domainFreqList=(DomainFreqList*)malloc(sizeof(DomainFreqList));
        freqList=temp->domainFreqList;
        
        token = strtok(NULL, delimiters);
        while (token != NULL) {  /* let's add other freqnodes by sorting*/
            url=token;
            token = strtok(NULL, delimiters);
            freq=atoi(token);

            if(freqcount==0){
                freqList->head=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
                freqList->tail=freqList->head;
                temp_freq=freqList->head;
                temp_freq->prev=NULL;
                temp_freq->name=url;
                temp_freq->freq=freq;
                temp_freq->next=NULL;
            }else{
                new=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
                createListNode(new,freq, url);
                sortFreqList(new,freqList);   
            }
            

            freqcount++;
            token = strtok(NULL, delimiters);
        }
        
        
        prev_temp=temp;
        temp=temp->next;
        /*printf("freq count= %d \n",freqcount);*/


        
    }
    /*printf("%s\n",cache->head->domainFreqList->head->name);
    printf("%s\n",cache->head->domainFreqList->head->next->name);
    printf("%s\n",cache->head->domainFreqList->head->next->next->name);
    printf("%s\n",cache->head->domainFreqList->head->next->next->next->name);*/
    cache->currentSize=crntSize;
    
    return cache;
}

/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{
    CacheNode* currentNode;
    DomainFreqNode* currentFreq;
    int mediaCount,i;
    if(cache->head==NULL){
        printf("The Cache is Empty\n");
    }
    else{
        printf("-------------- Cache Information --------------\n");
        printf("Cache Limit: %d KB\n",cache->cacheLimit);
        printf("Current Size: %d KB\n",cache->currentSize);
        printf("Media Count: %d\n",cache->mediaCount);
        printf("Cache Media Info:\n");
        mediaCount=cache->mediaCount;
        
        currentNode=cache->head;
        for(i=0;i<mediaCount;i++){
            printf("    Name: %s    Size: %d KB\n",(currentNode->media).name,(currentNode->media).size);
            printf("    ------- Media Domain Frequencies -------\n");
            
            currentFreq=currentNode->domainFreqList->head;
            while(currentFreq!=NULL){
                printf("    Name: %s        Freq: %d\n",currentFreq->name,currentFreq->freq);
                currentFreq=currentFreq->next;
            }
            
            currentNode=currentNode->next;
            printf("    ----------------------------------------\n");
        }
        printf("----------------------------------------------\n");
    }
}


/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{

    int i, mediaCount=cache->mediaCount,isExist=0 , urlExist=0;
    CacheNode* currentNode,*neww, *result, *ejectedNode;
    DomainFreqNode* FreqNode,*newFreq;
    
    currentNode=cache->head;
    for(i=0;i<mediaCount;i++){
        if(strcmp(media.name, (currentNode->media).name)==0){
            
            isExist=1;
            FreqNode = currentNode->domainFreqList->head;
            while(FreqNode!=NULL){
                if(strcmp(FreqNode->name, domain)==0){
                    urlExist=1;
                    FreqNode->freq++;
                    ejectFreq(FreqNode,currentNode->domainFreqList);
                    sortFreqList(FreqNode,currentNode->domainFreqList);
                    
                    break;
                }
                else{
                    FreqNode=FreqNode->next;
                }
            }
            if(urlExist==0){
                newFreq=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
                createListNode(newFreq,1, domain);
                
                sortFreqList(newFreq,currentNode->domainFreqList);
            }
            result=currentNode;
            addNode2Head(cache->head,ejectNode(currentNode,cache) ,cache);
            
            
            break;
        }else{
            currentNode=currentNode->next;
        }
        
    }
    if(isExist==0){ /*create a new node*/
        /*(cache->mediaCount)++;*/
        /*cache->currentSize+=media.size;*/
        
        
        neww=(CacheNode*)malloc(sizeof(CacheNode));
        neww->media=media; /*be carefull*/
        neww->domainFreqList=(DomainFreqList*)malloc(sizeof(DomainFreqList));
        neww->domainFreqList->head=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        neww->domainFreqList->tail=neww->domainFreqList->head;
        neww->domainFreqList->head->name = (char*)malloc(sizeof(domain));
        strcpy(neww->domainFreqList->head->name,domain);
        neww->domainFreqList->head->freq=1;
        neww->domainFreqList->head->next=NULL;
        neww->domainFreqList->head->prev=NULL;
        
        addNode2Head(cache->head,neww ,cache);
        
        if(cache->currentSize > cache->cacheLimit){
            while(cache->currentSize > cache->cacheLimit){
                ejectedNode=ejectNode(cache->tail ,cache);
                free(ejectedNode);
            }
        }
        result=neww;
    }
    return result;
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    CacheNode* result=NULL, *temp;
    int count=cache->mediaCount,i;
    temp=cache->head;
    for(i=0;i<count;i++){
        if(strcmp(name, temp->media.name)==0){
            result=temp;
        }else{
            temp=temp->next;
        }
    }
    return result;
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{
    int i;
    CacheNode* currentNode,*ejectedNode;
    currentNode=cache->head;
    for(i=0;i<cache->mediaCount;i++){
        if(strcmp(name, (currentNode->media).name)==0){
            ejectedNode=ejectNode(currentNode ,cache);
            free(ejectedNode);
            break;
        }else{
            currentNode=currentNode->next;
        }
    }
}



int main(int argc, char** argv)
{
    Cache* cache;
    CacheNode* finded;
    Media media1, media2, media5, Alperen,media3;

    /* Create the cache */
    cache = createCache();
    printCache(cache);
    /* Add new media */
    media1.name = "newVideo";
    media1.size = 300;
    
    media2.name ="belgesel keyfi";
    media2.size =400;
    
    media5.name="video1";
    media5.size=200;
    
    media3.name="video3";
    media3.size=319;
    
    Alperen.name="Alperen";
    Alperen.size=35;
/*
    addMediaRequest(cache, media5, "aa");
    printCache(cache);

    addMediaRequest(cache, media5, "aa");
    printCache(cache);

    
    addMediaRequest(cache, Alperen, "aa");
    printCache(cache);
    
    addMediaRequest(cache, Alperen, "aa");
    printCache(cache);
    
    finded=findMedia(cache, "video30");
    if(finded==NULL){
        printf("nah\n");
    }else{
        printf("hah\n");
    }
    
    addMediaRequest(cache, media5, "tr");
    addMediaRequest(cache, media5, "tr");
    addMediaRequest(cache, media1, "tr");
    addMediaRequest(cache, media3, "aa");
    addMediaRequest(cache, media5, "tr");
    printCache(cache);
    addMediaRequest(cache, media2, "tr");
    printCache(cache);
    
    deleteMedia(cache, "belgesel keyfi");
    printCache(cache);
    
    deleteMedia(cache, "Alperen");
    printCache(cache);

    deleteMedia(cache, "video3");
    printCache(cache);
    deleteMedia(cache, "video1");
    printCache(cache);
    deleteMedia(cache, "newVideo");*/
    addMediaRequest(cache, media2, "tr");
    printCache(cache);
    addMediaRequest(cache, media2, "tr");
    printCache(cache);


    
    return 0;
}