
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

// A class that represents an undirected graph
class Graph {
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    void bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, 
                    vector<int>& low, int parent);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    void bridge();    // prints all bridges
};

// Constructor
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

// Adds an undirected edge between vertices v and w
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// A recursive function that finds and prints bridges using DFS traversal
void Graph::bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, 
                       vector<int>& low, int parent) {
    static int time = 0; // Initialize time

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices adjacent to this
    for (int v : adj[u]) {
        // If v is parent, continue to next adjacent vertex
        if (v == parent) continue;
        
        // If v is not visited, recurse for it
        if (!visited[v]) {
            bridgeUtil(v, visited, disc, low, u);

            // Check if the subtree rooted at v has a connection back to one of u's ancestors
            low[u] = min(low[u], low[v]);

            // If the lowest vertex reachable from subtree under v is below u in DFS tree, then u-v is a bridge
            if (low[v] > disc[u])
                cout << u << " " << v << endl;
        }
        // Update low[u] for back edge
        else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

// DFS based function to find all bridges
void Graph::bridge() {
    vector<bool> visited(V, false);
    vector<int> disc(V, -1);
    vector<int> low(V, -1);

    // Initially there is no parent so let it be -1
    int parent = -1;

    // Call the recursive helper function to find Bridges in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            bridgeUtil(i, visited, disc, low, parent);
        }
    }
}

// Driver program to test above function
int main() {
    cout << "\nBridges in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.bridge();

    cout << "\nBridges in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.bridge();

    cout << "\nBridges in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.bridge();

    return 0;
}
