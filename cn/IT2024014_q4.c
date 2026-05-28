#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

void insert_begin(int x) {
    struct node *n = malloc(sizeof(struct node));
    n->data = x;
    n->next = head;
    head = n;
}

void insert_end(int x) {
    struct node *n = malloc(sizeof(struct node));
    n->data = x;
    n->next = NULL;
    if (!head) { head = n; return; }
    struct node *t = head;
    while (t->next) t = t->next;
    t->next = n;
}

void delete_begin() {
    if (!head) return;
    struct node *t = head;
    head = head->next;
    free(t);
}

void delete_end() {
    if (!head) return;
    if (!head->next) { free(head); head = NULL; return; }
    struct node *t = head;
    while (t->next->next) t = t->next;
    free(t->next);
    t->next = NULL;
}

void display() {
    struct node *t = head;
    while (t) {
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");
}

int main() {
    insert_begin(10);
    insert_end(20);
    insert_end(30);
    display();
    delete_begin();
    display();
    delete_end();
    display();
    return 0;
}

