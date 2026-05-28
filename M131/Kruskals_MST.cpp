#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n); rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int rootI = find(i), rootJ = find(j);
        if (rootI != rootJ) {
            if (rank[rootI] < rank[rootJ]) parent[rootI] = rootJ;
            else if (rank[rootI] > rank[rootJ]) parent[rootJ] = rootI;
            else { parent[rootJ] = rootI; rank[rootI]++; }
        }
    }
};

bool compare(Edge a, Edge b) { return a.weight < b.weight; }

int kruskalsMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compare);
    DSU dsu(V);
    int mstCost = 0;
    for (Edge& e : edges) {
        if (dsu.find(e.src) != dsu.find(e.dest)) {
            dsu.unite(e.src, e.dest);
            mstCost += e.weight;
        }
    }
    return mstCost;
}

int main() {
    vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    cout << "Kruskal's MST cost: " << kruskalsMST(4, edges) << endl;
    return 0;
}
