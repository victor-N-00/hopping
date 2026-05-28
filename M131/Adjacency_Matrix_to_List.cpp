#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> matrixToList(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

int main() {
    vector<vector<int>> matrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    vector<vector<int>> adjList = matrixToList(matrix);
    
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << ": ";
        for (int v : adjList[i]) cout << v << " ";
        cout << endl;
    }
    return 0;
}
