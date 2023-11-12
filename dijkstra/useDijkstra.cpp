// Hailey Hayoon Chung

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "graph.h"

using namespace std;

int main() {
    
    string fileName, startVertex, outputFilename;
    
    cout<<"Enter name of graph file: ";
    cin>>fileName;
    ifstream file(fileName);
    
    graph graph;   
   
    string sourceVertex, destinationVetex;
    int cost;
    
    while(file >> sourceVertex >> destinationVetex >> cost){
        graph.addEdge(sourceVertex, destinationVetex, cost);
    }

    // Prompt for the starting vertex
    cout << "Enter name of starting vertex: ";
    cin >> startVertex;

    // The users are reprompted until they enter a valid index
    while(!graph.contains(startVertex)){
        cout<<"Enter name of starting vertex: ";
        cin >> startVertex;
    }

    // Measure CPU time for Dijkstra's algorithm
    clock_t t1 = clock();
    graph.applyDijkstra(startVertex);
    clock_t t2 = clock();

    // Calculate and output the CPU time used
    double cpuTimeUsed = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << cpuTimeUsed << std::endl;

    // Ask the user for the name of the output file
    cout << "Enter name of output file: ";
    cin >> outputFilename;

    // Write the results to the output file
    graph.results(outputFilename);

    return 0;
}
