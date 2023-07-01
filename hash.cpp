#include "hash.h"

using namespace std;

// hashTable constructor
// Uses getPrime to choose a prime number at least as large as the specified size for the initial size of the hash table.
hashTable::hashTable(int size){
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}

// The hash function
int hashTable::hash(const string &key){
    // Data Structures and Algorithms Analysis in C++ by Mark A. Weiss
    unsigned int hashValue = 0;
    for(char ch : key){
        hashValue = 37 * hashValue + ch;
    }
    return hashValue % capacity;
}

// Search for an item with the specified key
// Return the position if found, -1 otherwise.
int hashTable::findPos(const string &key){
    int currentPos = hash(key);

    while(data[currentPos].isOccupied){
        if(data[currentPos].key == key){
            return currentPos;
        }
        // Linear Probing: move on to next item
        currentPos++;
        // In case it exceeds the capacity
        currentPos = currentPos % capacity;
        // Returns -1 when item not found
        if(currentPos == hash(key)){
            return -1;
        }
    }
}

// Check if the specified key is in the hash table.
bool hashTable::contains(const string &key){
    // Return false if the specified key is not in the hash table.
    if(findPos(key)==-1){
        return false;
    }
    // Otherwise, return true.
    else{
        return true;
    }
}

// Insert the specified key into the hash table.
int hashTable::insert(const string &key, void *pv = nullptr){
    
    int currentPos = findPos(key);

    // Returns 1 if the key already exists in the hash table
    if(contains(key)){
        return 1;
    }
    // Returns 2 if rehash fails.
    else if(filled > 0.5*capacity){
        // Return 2 if rehash fails.
        if(rehash()==false){
            return 2;
        }
    }
    // Returns 0 on success.
    else if(currentPos==-1){
        data[currentPos].key = key;
        data[currentPos].isOccupied = true;
        data[currentPos].isDeleted = false;
        data[currentPos].pv = pv;
        filled++;

        return 0;
    }
    else{
        return -1;
    }

}

bool hashTable::rehash(){
    return true;
}

unsigned int hashTable::getPrime(int size){
    // Uses a precomputed sequence of 17 selected prime numbers.
    unsigned int primes[] = {101,601,1201,2011,3011,5011,10007,15101,30011,50101,75011,100003,150001,500009,750019,1000003,1500007};

    // Return a prime number at least as large as size.
    for (int i=0 ; i<17 ;i++){
        if (primes[i]>=size){
            return primes[i];
        }
    }
    return 1;
}