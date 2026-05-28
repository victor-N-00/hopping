#include <iostream>
#include <vector>
using namespace std;

bool bpm(vector<vector<bool>>& bpGraph, int u, vector<bool>& seen, vector<int>& matchR) {
    for (int v = 0; v < bpGraph[0].size(); v++) {
        if (bpGraph[u][v] && !seen[v]) {
            seen[v] = true;
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR)) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxBPM(vector<vector<bool>>& bpGraph) {
    int M = bpGraph.size();
    int N = bpGraph[0].size();
    vector<int> matchR(N, -1);
    int result = 0;
    for (int u = 0; u < M; u++) {
        vector<bool> seen(N, false);
        if (bpm(bpGraph, u, seen, matchR)) result++;
    }
    return result;
}

int main() {
    vector<vector<bool>> bpGraph = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1}
    };
    cout << "Max Bipartite Matching: " << maxBPM(bpGraph) << endl;
    return 0;
}
