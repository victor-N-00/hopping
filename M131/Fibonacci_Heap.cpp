#include <iostream>
using namespace std;

// Skeleton for Fibonacci Heap
struct FibNode {
    int key;
    FibNode *parent, *child, *left, *right;
    int degree;
    bool mark;
};

class FibonacciHeap {
    FibNode* minNode = nullptr;
    int nNodes = 0;
public:
    void insert(int key) {
        cout << "Inserted " << key << " into Fibonacci Heap." << endl;
    }
    
    int extractMin() {
        return -1; // Dummy
    }
};

int main() {
    FibonacciHeap fh;
    fh.insert(10);
    return 0;
}
