#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* findLocalMinimum(TreeNode* root) {
    if (!root) return nullptr;
    if (root->left && root->left->val < root->val) {
        return findLocalMinimum(root->left);
    }
    if (root->right && root->right->val < root->val) {
        return findLocalMinimum(root->right);
    }
    return root; // Root is local minimum
}

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    TreeNode* res = findLocalMinimum(root);
    cout << "Local minimum: " << (res ? res->val : -1) << endl;
    return 0;
}
