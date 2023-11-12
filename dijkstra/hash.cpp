// Hailey Hayoon Chung

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
    int startingPos = currentPos;

    while(data[currentPos].isOccupied && !data[currentPos].isDeleted){
        if(data[currentPos].key == key){
            return currentPos;
        }
        // Linear Probing: move on to next item
        currentPos++;
        // In case it exceeds the capacity
        currentPos = currentPos % capacity;
        if(currentPos == startingPos){
            return -1;
        }
    }
    return -1;
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
int hashTable::insert(const string &key, void *pv){
    
    int currentPos = findPos(key);

    // Returns 1 if the key already exists in the hash table
    if(currentPos != -1){
        return 1;
    }
    // Returns 2 if rehash fails.
    // I tested with 0.3, 0.4, 0.5, 0.6, 0.7, and 0.3 took the least time.
    if(filled > 0.3*capacity){
        // Return 2 if rehash fails.
        if(rehash()==false){
            return 2;
        }
    }
    // Returns 0 on success.
    if(currentPos == -1){
        currentPos = hash(key); // Get the initial position to insert the key
        while(data[currentPos].isOccupied){ // Linear probing to find an empty slot
            currentPos++;
            currentPos = currentPos % capacity;
        }
        data[currentPos].key = key;
        data[currentPos].isOccupied = true;
        data[currentPos].isDeleted = false;
        data[currentPos].pv = pv;
        filled++;
        return 0;
    }
    return -1;

}

bool hashTable::rehash(){

    vector<hashItem> oldData = data;
    int newCapacity = getPrime(2*capacity);

    // Returns false if memory allocation fails.
    if(newCapacity == -1){
        return false;
    }
    int oldCapacity = capacity;
    data.clear(); // clear current data
    data.resize(newCapacity);
    filled = 0;    // reset filled counter
    capacity = newCapacity; // update the capacity to the new value

    for (int i=0; i<oldCapacity; i++){
        if(oldData[i].isOccupied && !oldData[i].isDeleted){
            insert(oldData[i].key, oldData[i].pv);
        }
    }

    return true;
}


unsigned int hashTable::getPrime(int size){
    // Uses a precomputed sequence of 25 selected prime numbers.
    unsigned int primes[] = {101,601,1201,2011,3011,5011,10007,15101,30011,50101,75011,100003,150001,500009,750019,1000003,1500007,3000017, 6000011, 12000017, 24000001, 48000013, 96000017, 192000011, 384000019};

    // Return a prime number at least as large as size.
    for (int i=0 ; i<25 ;i++){
        if (primes[i]>=size){
            return primes[i];
        }
    }
    // Returns -1 if size exceeds maximum prime.
    return -1;
}

int hashTable::setPointer(const std::string &key, void *pv) {
    // Find the position
    int pos = findPos(key); 
    
    // Check if the key exists in the hash table
    if (pos != -1 && data[pos].key == key) {
        // If yes, update the associated pointer
        data[pos].pv = pv;
        // Return 0 on success
        return 0;
    }
    // If not, return 1
    return 1; 
}

void* hashTable::getPointer(const std::string &key, bool *b) {
    int pos = findPos(key);
    // If key is found in the hash table.
    if (pos != -1) {
        // set the bool to true if optional pointer is provided
        if (b != nullptr) {
            *b = true;
        }
        // Return the associated pointer.
        return data[pos].pv; 
    } 
    // If key is not found in the hash table, set bool to false.
    else if (b != nullptr) {
        *b = false;
    }
    // if the key does not exist in the hash table, return nullptr
    else{
        return nullptr;
    }
}

bool hashTable::remove(const std::string &key) {
    int pos = findPos(key);
    
    // If key is found in the hash table.
    if (pos != -1) {
        data[pos].isDeleted = true;
        data[pos].key = ""; 
        data[pos].pv = nullptr;
        return true;
    } 

    // If key is not found in the hash table.
    return false; 
}
