// Hailey Hayoon Chung

#include <iostream>
#include <fstream>

#include "graph.h"

graph::graph() : nodeHash(10000){}

// addEdge adds the edge between the source and destination nodes
void graph::addEdge(const std::string &source, const std::string &destination, int cost) {
    node *srcNode, *destNode;
    bool exists;

    // Get the source node
    srcNode = static_cast<node *>(nodeHash.getPointer(source, &exists));
    // If a new node is encountered, add to the end
    if (!exists) {
        srcNode = new node(source);
        nodeHash.insert(source, srcNode);
        nodeList.push_back(srcNode);
    }

    // Get the destination node
    destNode = static_cast<node *>(nodeHash.getPointer(destination, &exists));
    // If a new node is encountered, add to the end
    if (!exists) {
        destNode = new node(destination);
        nodeHash.insert(destination, destNode);
        nodeList.push_back(destNode);
    }

    // Add the edge to the adjacencyList of srcNode
    srcNode->adjacencyList.push_back(edge(destNode, cost));
}

void graph::applyDijkstra(const std::string &startVertex) {
    
    // Initialize the minDistance of all nodes to be infinity
    for (auto nodePtr : nodeList) {
        nodePtr->minDistance = INT_MAX;
        nodePtr->previous = nullptr;
    }

    // Get the start node
    bool exists;
    node *startNode = static_cast<node *>(nodeHash.getPointer(startVertex, &exists));

    // Set the minDistance of start node as 0, according to Dijkstra's algorithm
    startNode->minDistance = 0;
    heap minHeap(nodeList.size());
    minHeap.insert(startVertex, 0, startNode);

    // Dijkstra's algorithm
    std::string currentVertexId;
    while (minHeap.deleteMin(&currentVertexId, nullptr, nullptr) == 0) {
        node *currentNode = static_cast<node *>(nodeHash.getPointer(currentVertexId));

        for (const edge &e : currentNode->adjacencyList) {
            node *adjacentNode = e.destination;
            int alternativePathDistance = currentNode->minDistance + e.cost;

            if (alternativePathDistance < adjacentNode->minDistance) {
                adjacentNode->minDistance = alternativePathDistance;
                adjacentNode->previous = currentNode;

                // Try to update the node in the min-heap
                int result = minHeap.setKey(adjacentNode->id, alternativePathDistance);
                // if node not in heap, than insert node to heap
                if (result != 0) {
                    minHeap.insert(adjacentNode->id, alternativePathDistance, adjacentNode);
                }
            }
        }
    }
}


bool graph::contains(const std::string &id){
    return nodeHash.contains(id);
}

void graph::results(const std::string &outputFilename) {
    std::ofstream outFile(outputFilename);

    for (const auto &nodePtr : nodeList) {
        outFile << nodePtr->id << ": ";

        // If there is no path from the specified starting vertex to any existing vertex in the graph
        if (nodePtr->minDistance == INT_MAX) {
            outFile << "NO PATH" << std::endl;
        } 
        // Else print the shortest distanced from the specified starting vertex to the given vertex
        else {
            outFile << nodePtr->minDistance << " [";

            // Reconstruct the path using "previous"
            std::vector<std::string> path;
            for (node *current = nodePtr; current != nullptr; current = current->previous) {
                path.push_back(current->id);
            }
            // Reverse the path
            std::reverse(path.begin(), path.end());

            // Print the path from the start vertex to the current node
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) {
                    outFile << ", ";
                }
                outFile << path[i];
            }
            outFile << "]" << std::endl;
        }
    }

    outFile.close();
}
