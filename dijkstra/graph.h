// Hailey Hayoon Chung

#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include "heap.h"
#include "hash.h"

class graph {
public:
    // The constructor for graph class
    graph();

    // Member function of the class
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
        node(const std::string &id) : id(id), known(false), minDistance(INT_MAX), previous(nullptr) {}
        std::string id;
        std::list<edge> adjacencyList;
        bool known;
        int minDistance;
        node *previous;
};

class graph::edge {
    public:
        edge(node *destination, int cost) : destination(destination), cost(cost) {}
        node *destination;
        int cost;
};

#endif //_GRAPH_H
