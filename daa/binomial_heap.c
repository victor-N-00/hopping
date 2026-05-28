#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct BinomialNode {
    int key;
    int degree;
    struct BinomialNode *parent;
    struct BinomialNode *child;
    struct BinomialNode *sibling;
} BinomialNode;

BinomialNode* makeHeap() {
    return NULL;
}

BinomialNode* createNode(int key) {
    BinomialNode* node = (BinomialNode*)malloc(sizeof(BinomialNode));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

BinomialNode* linkTrees(BinomialNode* y, BinomialNode* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
    return z;
}

BinomialNode* mergeRootLists(BinomialNode* h1, BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    BinomialNode *head = NULL, **pos = &head;

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            *pos = h1;
            h1 = h1->sibling;
        } else {
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);
    }

    *pos = (h1) ? h1 : h2;
    return head;
}

BinomialNode* unionHeap(BinomialNode* h1, BinomialNode* h2) {
    BinomialNode* heap = mergeRootLists(h1, h2);
    if (!heap) return NULL;

    BinomialNode *prev = NULL, *curr = heap, *next = curr->sibling;

    while (next) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                curr = linkTrees(next, curr);
            } else {
                if (prev)
                    prev->sibling = next;
                else
                    heap = next;

                curr = linkTrees(curr, next);
            }
        }
        next = curr->sibling;
    }
    return heap;
}

BinomialNode* insert(BinomialNode* heap, int key) {
    BinomialNode* node = createNode(key);
    return unionHeap(heap, node);
}

BinomialNode* findMin(BinomialNode* heap) {
    int min = INT_MAX;
    BinomialNode* minNode = NULL;

    while (heap) {
        if (heap->key < min) {
            min = heap->key;
            minNode = heap;
        }
        heap = heap->sibling;
    }
    return minNode;
}

int main() {
    BinomialNode* heap1 = makeHeap();
    BinomialNode* heap2 = makeHeap();

    heap1 = insert(heap1, 10);
    heap1 = insert(heap1, 3);
    heap1 = insert(heap1, 7);

    heap2 = insert(heap2, 1);
    heap2 = insert(heap2, 5);

    BinomialNode* heap = unionHeap(heap1, heap2);

    BinomialNode* min = findMin(heap);
    if (min)
        printf("Minimum element: %d\n", min->key);

    return 0;
}
