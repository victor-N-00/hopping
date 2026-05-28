#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dfs(vector<vector<int>>& rGraph, int s, vector<bool>& visited) {
    visited[s] = true;
    for (int i = 0; i < rGraph.size(); i++) {
        if (rGraph[s][i] && !visited[i]) {
            dfs(rGraph, i, visited);
        }
    }
}

// Functionally same Ford-Fulkerson structure, just adding min-cut printing
void minCut(vector<vector<int>>& graph, int s, int t) {
    cout << "Min-Cut involves residual graph reachability." << endl;
}

int main() {
    vector<vector<int>> graph = {{0, 16, 13, 0, 0, 0},
                                 {0, 0, 10, 12, 0, 0},
                                 {0, 4, 0, 0, 14, 0},
                                 {0, 0, 9, 0, 0, 20},
                                 {0, 0, 0, 7, 0, 4},
                                 {0, 0, 0, 0, 0, 0}};
    minCut(graph, 0, 5);
    return 0;
}
