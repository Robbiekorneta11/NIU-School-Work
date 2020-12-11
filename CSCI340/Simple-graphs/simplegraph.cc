#include "simplegraph.h"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector< int > visited;  // Track visited nodes
string path;            // The path to the visited node

int main(int argc, char** argv) 
{
    if ( argc < 2 ) 
	{
        cerr << "args: input-file-name\n";
        return 1;
    } 

    Graph g(argv[1]);
    g.Print();    
    g.Traverse();
    return 0;
}

/**
 * Builds a graph based on the file
 * 
 * @param filename -> The name of the file to open
 * *********************************************/
Graph::Graph( const char* filename ) {

    char label;                             // The label of the vertex
    ifstream inputFile(filename, ios::in);  // Input file
    inputFile >> size;                      // Get size of the graph
    
    // Input vertices into labels vector
    for (int i = 0; i < size; i++) {

        inputFile >> label;
        labels.push_back(label);

    }

    // Insert values into the adjacency list
    for (int i = 0; i < size; i++) {

        inputFile >> label; // First value is the edge

        adj_list.push_back(*(new list<int>())); // Create a pointer to a new list and push into adjacency list

        // Insert values into list
        for (int j = 0; j < size; j++) {

            int v = 0;
            inputFile >> v;
            adj_list[i].push_back(v);

        }

    }

}

// Destructor
Graph::~Graph() {}

int Graph::Getsize() const {

    return size;

}

/**
 * Traverses a graph
 * *******************************/
void Graph::Traverse() {

    path = "";

    cout << "------- travere of graph ------\n";

    // Loop through and use depth first to traverse
    for (int i = 0; i < size; i ++) {
		
        // Make sure vertex was not visited
        if (find(visited.begin(), visited.end(), i) == visited.end())
			      Depthfirst(i);

	}

    cout << endl << path << endl;
    cout << "--------- end of traverse -------\n\n";
}

/**
 * Performs a depth first traversal of a graph
 * 
 * @param v -> The index value v of the vertex to visit
 * 
 * ******************************************************/
void Graph::Depthfirst(int v) {

    cout << labels[v] << " ";   // Print label
	visited.push_back(v);       // Vertex has been visited, push into vector
	int j = 0;                  // Next vertex to visit

    list<int>::const_iterator graphIt;

    // Iterate through the graph
	for (graphIt = adj_list[v].begin(); graphIt != adj_list[v].end(); graphIt++) {

        // Check if it is a vertex and make sure the vertex was not visited yet
		if (*graphIt == 1 && find(visited.begin(), visited.end(), j) == visited.end()) {

			  path += "("; path += labels[v]; path += ", "; path += labels[j]; path += ") ";
			  Depthfirst(j);

		}

		j++;

	}

}

/**
 * Print the graph
 * *******************************************/
void Graph::Print() const {

    cout << "\nNumber of vertices in the graph: " << size << "\n\n";
    cout << "-------- graph -------\n";

    for (int i = 0; i < size; i++) {

        cout << labels[i] << ": ";
        int j = 0;
        list<int>::const_iterator graphIt;

        for (graphIt = adj_list[i].begin(); graphIt != adj_list[i].end(); graphIt++) {

            if (*graphIt == 1) {

                cout << labels[j] << ", ";

            }

            j++;

        }

        cout << endl;

    }

    cout << "------- end of graph ------\n\n";

}
