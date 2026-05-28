#include <stdio.h>
#include <stdlib.h>

void quick(int a[], int l, int r) {
    if (l < r) {
        int p = a[r], i = l - 1, t;
        for (int j = l; j < r; j++) {
            if (a[j] <= p) {
                i++;
                t = a[i]; a[i] = a[j]; a[j] = t;
            }
        }
        t = a[i + 1]; a[i + 1] = a[r]; a[r] = t;
        quick(a, l, i);
        quick(a, i + 2, r);
    }
}

int main() {
    int a[100], n = 0;
    while (scanf("%d", &a[n]) == 1) n++;
    quick(a, 0, n - 1);
    printf("\n");
    for (int i = 0; i < n; i++) printf( "%d ", a[i]);
    return 0;
}

