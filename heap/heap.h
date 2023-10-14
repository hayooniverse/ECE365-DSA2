// Hailey Hayoon Chung

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap{
    public:
        // The constructor allocates space for the nodes of the heap and the mapping (hash table) basd on the specified capacity
        heap(int capacity);

        // Inserts a new node into the binary heap
        // Inserts a node with the specified id string, key, and optionally a pointer. The key is used to determine the final position of the new node.
        int insert(const std::string &id, int key, void *pv = nullptr);
       
        // setKey - set the key of the specified node to the specified value
        int setKey(const std::string &id, int key);

        // deleteMin - return the data associated with the smallest key and delete that node from the binary heap
        int deleteMin(std:: string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

        // remove - delete the node with the specified id from the binary heap
        int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);
    
    private:
        // The capacity of the heap
        int capacity;
        // The current size of the heap
        int currentSize;

        // "node" - a private nested class within the heap class
        class node{
            public:
                std::string id;
                int key;
                void *pData;

                node() : key(0), pData(nullptr) {}
                // The constructor for node
                node(const std::string &id, int key, void *pv) : id(id), key(key), pData(pv) {}
            
        };

        // The vector of node objects containing the actual data of the heap
        std::vector<node> data;
        hashTable mapping;

        void percolateUp(int posCur);
        void percolateDown(int posCur);
        int getPos(node *pn);

};

#endif //_HEAP_H