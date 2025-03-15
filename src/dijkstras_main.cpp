#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include "dijkstras.h"

using namespace std;


int main()
{
    //declarations

    Graph graph;
    file_to_graph("src/small.txt", graph);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, source, previous);

    for (int i = 0; i < graph.numVertices; i++) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }


    //get user input



    //calculation 


    //Output

  
    system("pause");
    return 0;
}
