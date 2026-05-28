#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct FibNode {
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;

FibNode* makeHeap() {
    return NULL;
}

FibNode* createNode(int key) {
    FibNode* node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

FibNode* insert(FibNode* min, int key) {
    FibNode* node = createNode(key);

    if (!min)
        return node;

    node->right = min->right;
    node->left = min;
    min->right->left = node;
    min->right = node;

    if (node->key < min->key)
        min = node;

    return min;
}

FibNode* unionHeap(FibNode* min1, FibNode* min2) {
    if (!min1) return min2;
    if (!min2) return min1;

    FibNode* temp = min1->right;
    min1->right = min2->right;
    min1->right->left = min1;
    min2->right = temp;
    min2->right->left = min2;

    return (min1->key < min2->key) ? min1 : min2;
}

FibNode* findMin(FibNode* min) {
    return min;
}

int main() {
    FibNode* heap1 = makeHeap();
    FibNode* heap2 = makeHeap();

    heap1 = insert(heap1, 10);
    heap1 = insert(heap1, 3);
    heap1 = insert(heap1, 7);

    heap2 = insert(heap2, 1);
    heap2 = insert(heap2, 5);

    FibNode* heap = unionHeap(heap1, heap2);

    FibNode* min = findMin(heap);
    if (min)
        printf("Minimum element: %d\n", min->key);

    return 0;
}
