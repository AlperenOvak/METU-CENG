#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>

//=======================//
// Implemented Functions //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::PRIMES[3] = {102523, 100907, 104659};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintLine(int tableIndex) const
{
    const HashData& data = table[tableIndex];

    // Using printf here it is easier to format
    if(data.sentinel == SENTINEL_MARK)
    {
        printf("[%03d]         : SENTINEL\n", tableIndex);
    }
    else if(data.sentinel == EMPTY_MARK)
    {
        printf("[%03d]         : EMPTY\n", tableIndex);
    }
    else
    {
        printf("[%03d] - [%03d] : ", tableIndex, data.lruCounter);
        printf("(%-5s) ", data.isCostWeighted ? "True" : "False");
        size_t sz = data.intArray.size();
        for(size_t i = 0; i < sz; i++)
        {
            if(i % 2 == 0)
                printf("[%03d]", data.intArray[i]);
            else
                printf("/%03d/", data.intArray[i]);

            if(i != sz - 1)
                printf("-->");
        }
        printf("\n");
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintTable() const
{
    printf("____________________\n");
    printf("Elements %d\n", elementCount);
    printf("[IDX] - [LRU] | DATA\n");
    printf("____________________\n");
    for(int i = 0; i < MAX_SIZE; i++)
    {
        PrintLine(i);
    }
}

//=======================//
//          TODO         //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Hash(int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int values[] = { startInt, endInt, isCostWeighted ? 1 : 0 };

    int hashValue = 0;
    for (int i = 0; i < 3; ++i) {
        hashValue += PRIMES[i] * values[i];
    }

    return hashValue;
}

template<int MAX_SIZE>
HashTable<MAX_SIZE>::HashTable()
{
    /* TODO */
    for (int i = 0; i < MAX_SIZE; ++i) {
        table[i].lruCounter = 0;                // Set lruCounter to zero
        table[i].sentinel = EMPTY_MARK;         // Mark the spot as empty
        table[i].intArray.clear();              // Clear the integer array (if any)
        table[i].isCostWeighted = false;        // Initialize isCostWeighted to false
        table[i].startInt = 0;                  // Initialize startInt to zero
        table[i].endInt = 0;                    // Initialize endInt to zero
    }
    elementCount = 0;     

}

template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Insert(const std::vector<int>& intArray, bool isCostWeighted)
{
    /* TODO */
    int preLRU=0;

    if(intArray.size()<1){
        throw InvalidTableArgException();
    }


    //search wheter it is in the table or not
    int startInt = intArray[0];
    int endInt = intArray[intArray.size()-1];
    int hashIndex = Hash(startInt,endInt,isCostWeighted)%MAX_SIZE; // find the original index
    for (int i = 0; i < MAX_SIZE; ++i) {
         
        if(table[i].startInt == startInt && table[i].endInt==endInt && table[i].isCostWeighted ==isCostWeighted){
            preLRU = table[i].lruCounter;
            table[i].lruCounter++;
            return preLRU;
        }               
    } 
    //std::cout<<hashIndex<<" "<<startInt<<" "<<endInt<<" "<<isCostWeighted<< " hashIndex ne çıkacak\n";
    //std::cout<<elementCount<<"elementCount\n";
    // if it's new, insert it
    if(elementCount >= MAX_SIZE/2){
        throw TableCapFullException(elementCount);
    }
    if(table[hashIndex].sentinel == EMPTY_MARK){
        preLRU=table[hashIndex].lruCounter;
        table[hashIndex].lruCounter++;        
        table[hashIndex].sentinel = OCCUPIED_MARK; 
        table[hashIndex].intArray = intArray;      
        table[hashIndex].isCostWeighted = isCostWeighted;
        table[hashIndex].startInt = startInt;          
        table[hashIndex].endInt = endInt;
        elementCount++;
    }else{    //quadratic probing
        for (int j = 0; j < MAX_SIZE; j++) {
            // Computing the new hash value
            int t = (hashIndex + j * j) % MAX_SIZE;
            if (table[t].sentinel == EMPTY_MARK) {
                // Break the loop after
                // inserting the value
                // in the table
                preLRU=table[t].lruCounter;
                table[t].lruCounter++;        
                table[t].sentinel = OCCUPIED_MARK; 
                table[t].intArray = intArray;      
                table[t].isCostWeighted = isCostWeighted;
                table[t].startInt = startInt;          
                table[t].endInt = endInt;    
                elementCount++;
                return preLRU;
            }
        }
    }
    return preLRU;

}

template<int MAX_SIZE>
bool HashTable<MAX_SIZE>::Find(std::vector<int>& intArray,
                               int startInt, int endInt, bool isCostWeighted,
                               bool incLRU)
{
    /* TODO */
    //search wheter it is in the table or not
    for(int i=0;i<MAX_SIZE;i++) {
         
        if(table[i].sentinel==OCCUPIED_MARK && table[i].startInt == startInt && table[i].endInt==endInt && table[i].isCostWeighted ==isCostWeighted){
            if(incLRU){
                table[i].lruCounter++;
            }
            intArray = table[i].intArray;
            return true;
        }
    } 
    return false;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */
    for (int i = 0; i < MAX_SIZE; ++i) {
        table[i].lruCounter = 0;                // Set lruCounter to zero
        table[i].sentinel = EMPTY_MARK;         // Mark the spot as empty
        table[i].intArray.clear();              // Clear the integer array (if any)
        table[i].isCostWeighted = false;        // Initialize isCostWeighted to false
        table[i].startInt = 0;                  // Initialize startInt to zero
        table[i].endInt = 0;                    // Initialize endInt to zero
    }
    elementCount = 0;
    /*HashTable();*/
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
    int maxLRU=0;
    int index;
    for (int i = 0; i < MAX_SIZE; ++i) {
        if(maxLRU<table[i].lruCounter){
            maxLRU=table[i].lruCounter;
            index=i;
        }    
    }
    intArray = table[index].intArray;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int i = -1; // find the original index
    for(int j=0;j<MAX_SIZE;j++){
        if(table[j].sentinel==OCCUPIED_MARK && table[j].startInt == startInt && table[j].endInt==endInt && table[j].isCostWeighted ==isCostWeighted){
            i=j;
            break; // I found it 
        }
    }
    if(i==-1){
        return;
    }
    //std::cout<<i<<"\n";
    intArray = table[i].intArray;
    table[i].lruCounter = 0;         
    table[i].sentinel = SENTINEL_MARK;  
    table[i].intArray.clear();       
    table[i].isCostWeighted = false; 
    table[i].startInt = 0;           
    table[i].endInt = 0; 
    elementCount--;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
    for(int j=0;j<lruElementCount;j++){
        int lowestLRU=99999999;
        int index=-1;
        for (int i = 0; i < MAX_SIZE; ++i){
            if(table[i].sentinel == OCCUPIED_MARK && lowestLRU>table[i].lruCounter){
                lowestLRU=table[i].lruCounter;
                index = i;
            }
        }
        
        table[index].lruCounter = 0;         
        table[index].sentinel = SENTINEL_MARK;  
        table[index].intArray.clear();       
        table[index].isCostWeighted = false; 
        table[index].startInt = 0;           
        table[index].endInt = 0; 
        elementCount--;        
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
    MaxPairHeap<int,int> pq;
    for(int i=0;i<MAX_SIZE;i++){
        if(table[i].sentinel == OCCUPIED_MARK){
            pq.push({table[i].lruCounter,i});
        }
    }
    while(!pq.empty()){
        Pair<int,int> curr = pq.top();
        pq.pop();
        PrintLine(curr.value);
    }
}

#endif // HASH_TABLE_HPP