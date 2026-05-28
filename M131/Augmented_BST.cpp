#include <iostream>
using namespace std;

struct Node {
    int key;
    int size; // Size of subtree
    Node *left, *right;
    Node(int k) : key(k), size(1), left(nullptr), right(nullptr) {}
};

int getSize(Node* n) {
    return n ? n->size : 0;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    root->size = 1 + getSize(root->left) + getSize(root->right);
    return root;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    cout << "Root size: " << root->size << endl;
    return 0;
}
