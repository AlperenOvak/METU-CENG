#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

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
    int hashIndex = Hash(startInt,endInt,isCostWeighted); // find the original index

    for (int i = 0; i < MAX_SIZE; ++i) {
         
        if(table[i].startInt == startInt && table[i].endInt==endInt && table[i].isCostWeighted=isCostWeighted){
            preLRU = table[i].lruCounter;
            table[i].lruCounter++;
            return preLRU;
        }               
    }

    // if it's new, insert it
    if(elementCount >= MAX_SIZE/2){
        throw TableCapFullException();
    }
    if(table[hashIndex].sentinel == EMPTY_MARK){
        preLRU=table[hashIndex].lruCounter;
        table[hashIndex].lruCounter++;        
        table[hashIndex].sentinel = OCCUPIED_MARK; 
        table[hashIndex].intArray = intArray;      
        table[hashIndex].isCostWeighted = isCostWeighted;
        table[hashIndex].startInt = startInt;          
        table[hashIndex].endInt = endInt;                
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
    return false;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
}

#endif // HASH_TABLE_HPP