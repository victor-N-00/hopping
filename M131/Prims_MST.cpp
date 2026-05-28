#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

int primsMST(int V, vector<vector<pii>>& adj) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<bool> inMST(V, false);
    
    int mstCost = 0;
    pq.push({0, 0}); // {weight, vertex}
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        
        if (inMST[u]) continue;
        inMST[u] = true;
        mstCost += weight;
        
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    return mstCost;
}

int main() {
    int V = 4;
    vector<vector<pii>> adj(V);
    adj[0].push_back({1, 10}); adj[1].push_back({0, 10});
    adj[0].push_back({2, 6});  adj[2].push_back({0, 6});
    adj[0].push_back({3, 5});  adj[3].push_back({0, 5});
    adj[1].push_back({3, 15}); adj[3].push_back({1, 15});
    adj[2].push_back({3, 4});  adj[3].push_back({2, 4});
    cout << "Prim's MST cost: " << primsMST(V, adj) << endl;
    return 0;
}
