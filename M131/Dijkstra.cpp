#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
const int INF = 1e9;

vector<int> dijkstra(int V, vector<vector<pii>>& adj, int src) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> dist(V, INF);
    pq.push({0, src});
    dist[src] = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int V = 5;
    vector<vector<pii>> adj(V);
    adj[0].push_back({1, 10}); adj[0].push_back({2, 5});
    adj[1].push_back({2, 2}); adj[1].push_back({3, 1});
    adj[2].push_back({1, 3}); adj[2].push_back({3, 9}); adj[2].push_back({4, 2});
    adj[3].push_back({4, 4}); adj[4].push_back({0, 7}); adj[4].push_back({3, 6});
    
    vector<int> dist = dijkstra(V, adj, 0);
    cout << "Distances from src 0: ";
    for (int d : dist) cout << d << " ";
    cout << endl;
    return 0;
}
