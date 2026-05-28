#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, weight;
};

const int INF = 1e9;

void bellmanFord(int V, vector<Edge>& edges, int src) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    
    for (int i = 1; i <= V - 1; i++) {
        for (Edge& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;
            }
        }
    }
    
    for (Edge& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }
    
    cout << "Vertex Distances from Source " << src << ":\n";
    for (int i = 0; i < V; i++) cout << i << " \t " << dist[i] << endl;
}

int main() {
    vector<Edge> edges = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};
    bellmanFord(5, edges, 0);
    return 0;
}
