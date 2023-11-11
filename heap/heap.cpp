// Hailey Hayoon Chung

#include "heap.h"
#include "hash.h"

// Heap Constructor
heap::heap(int capacity) : mapping(capacity*2), capacity(capacity), currentSize(0) {
    data.resize(capacity + 1);
}

int heap::insert(const std::string &id, int key, void *pv) {
    // Heap is not full but doesn't contain id
    if (currentSize < capacity && mapping.contains(id) == false) {
        // Create a new node and insert at end
        currentSize++; // Increment the size
        node newNode = node(id, key, pv);
        data[currentSize] = newNode;
        // Insert to hashtable and percolate up
        mapping.insert(id, &data[currentSize]);
        percolateUp(currentSize);
        // Return 0 on success
        return 0;
    } 
    // Heap is already filled to capacity
    else if (currentSize == capacity) {
        return 1;
    } 
    // Node with the given id already exists
    else {
        return 2;
    }
}

int heap::setKey(const std::string &id, int key){
    // Find node via hash table
    node *pn = static_cast<node *> (mapping.getPointer(id));
    
    // Node with the given id does not exist
    if(pn == nullptr){
        return 1;
    }

    int oldKey = pn->key;
    pn->key = key;

    // Get the position of the node
    int pos = getPos(pn);

    // Determine whether to percolate up or down
    if (key < oldKey) {
        percolateUp(pos);
    } else if (key > oldKey) {
        percolateDown(pos);
    }
    // Return 0 on success
    return 0;
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    // Return 1 if heap is empty
    if (currentSize == 0) {
        return 1;
    }
    // If pId is supplied, write to that address the id of the node being deleted
    if (pId != nullptr) {
        *pId = data[1].id;
    }
    // If pKey is supplied, write to that address the key of the node being deleted
    if (pKey != nullptr) {
        *pKey = data[1].key;
    }
    // If ppData is supplied, write to that address the associated void pointer
    if (ppData != nullptr) {
        *(static_cast<void **> (ppData)) = data[1].pData;
    }
    
    // Remove root id from mapping
    mapping.remove(data[1].id);
    // Replace root
    data[1] = data[currentSize];
    currentSize--;
    percolateDown(1);
    
    // Return 0 on success
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
    node *pn = static_cast<node *> (mapping.getPointer(id));
    
    // Node with the provided id does not exist
    if(pn == nullptr){
        return 1;
    }
    // If pKey is supplied, write to that address the key of the node being deleted.
    if (pKey != nullptr) {
        *pKey = pn->key;
    }
    // If ppData is supplied, write to that address the associated void pointer.
    if (ppData != nullptr) {
        *(static_cast<void **> (ppData)) = pn->pData;
    }

    // Get the position of the node
    int pos = getPos(pn);
    // Remember old key
    int oldKey = pn -> key;
    // Replace the node with the last node in the heap and update the mapping
    mapping.remove(id);
    data[pos] = data[currentSize];
    currentSize--;

    mapping.setPointer(data[pos].id, &data[pos]);

    // Determine whether to percolate up or down
    if (data[pos].key < oldKey) {
        percolateUp(pos);
    } else {
        percolateDown(pos);
    }
    // Return 0 on success
    return 0;
}

void heap::percolateUp(int posCur){
    node temp = data[posCur];
    // While index is not at the root and parent's key is higher than child's key
    while(posCur > 1 && data[posCur/2].key > temp.key){
        // Move the parent node down
        data[posCur] = data[posCur/2];
        mapping.setPointer(data[posCur].id, &data[posCur]);
        posCur = posCur/2;
    }

    data[posCur] = temp;
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur){
    node temp = data[posCur];
    int child;
    while (2 * posCur <= currentSize) {
        child = 2 * posCur; // Left child index
        // Check if the right child exists and is smaller than left
        if(child != currentSize && data[child+1].key < data[child].key) {
            child++; // Use the right child instead
        }
        // If the child key < temp key, move child up
        if(data[child].key < temp.key){
            data[posCur] = data[child];
            mapping.setPointer(data[posCur].id, &data[posCur]);
        }
        else{
            break;
        }
        posCur = child;
    }
    data[posCur] = temp;
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}

