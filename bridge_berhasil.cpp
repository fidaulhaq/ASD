#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100

struct Node {
    int vertex;
    Node* next;
};

struct Graph {
    int V;
    Node* adj[MAX]; // adjacency list
    int disc[MAX];
    int low[MAX];
    int parent[MAX];
    bool visited[MAX];
    int time;
    int bridges[MAX][2]; // menyimpan bridges
    int bridgeCount;

    Graph(int V) {
        this->V = V;
        for (int i = 0; i < V; ++i) {
            adj[i] = nullptr;
            disc[i] = low[i] = parent[i] = -1;
            visited[i] = false;
        }
        time = 0;
        bridgeCount = 0;
    }

    void addEdge(int u, int v) {
        Node* newNode = new Node{v, adj[u]};
        adj[u] = newNode;
        newNode = new Node{u, adj[v]};
        adj[v] = newNode;
    }

    void bridgeUtil(int u) {
        struct StackElement {
            int u;
            Node* adjNode;
        };

        StackElement stack[MAX];
        int top = -1;

        stack[++top] = {u, adj[u]};
        visited[u] = true;
        disc[u] = low[u] = ++time;

        while (top >= 0) {
            StackElement &se = stack[top];
            u = se.u;
            Node* &adjNode = se.adjNode;

            bool backtracked = true;
            while (adjNode != nullptr) {
                int v = adjNode->vertex;
                adjNode = adjNode->next;

                if (!visited[v]) {
                    stack[top].adjNode = adjNode; // Save current adjacency node
                    stack[++top] = {v, adj[v]}; // Process the child node
                    visited[v] = true;
                    disc[v] = low[v] = ++time;
                    parent[v] = u;
                    backtracked = false;
                    break;
                } else if (v != parent[u]) {
                    low[u] = min(low[u], disc[v]);
                }
            }

            if (backtracked) {
                if (parent[u] != -1) {
                    low[parent[u]] = min(low[parent[u]], low[u]);
                    if (low[u] > disc[parent[u]]) {
                        bridges[bridgeCount][0] = parent[u];
                        bridges[bridgeCount][1] = u;
                        bridgeCount++;
                    }
                }
                top--;
            }
        }
    }

    void findBridges() {
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                bridgeUtil(i);
            }
        }

        cout << "Bridges in the graph:\n";
        for (int i = 0; i < bridgeCount; ++i) {
            cout << bridges[i][0] << " -- " << bridges[i][1] << "\n";
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.findBridges();

    return 0;
}
