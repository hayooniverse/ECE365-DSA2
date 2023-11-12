// Hailey Hayoon Chung

#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include "heap.h"  // Your custom heap implementation
#include "hash.h"  // Your custom hash table implementation

class graph {
public:
    graph();

    void addEdge(const std::string &source, const std::string &destination, int cost);
    bool contains(const std::string &id);
    void applyDijkstra(const std::string &startVertex);
    void results(const std::string &outputFilename);

private:
    class node;
    class edge;

    hashTable nodeHash;
    std::list<node*> nodeList;
};

class graph::node {
    public:
        std::string id;
        std::list<edge> adjacencyList;
        bool encountered;
        int minDistance;
        node *previous;
};

class graph::edge {
    public:
        node *destination;
        int cost;
};

#endif //_GRAPH_H
