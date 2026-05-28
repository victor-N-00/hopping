#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int t[100];
    while (i <= m && j <= r)
        t[k++] = a[i] < a[j] ? a[i++] : a[j++];
    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++, k++) a[i] = t[k];
}

void sort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        sort(a, l, m);
        sort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    int a[100], n = 0;
    while (scanf( "%d", &a[n]) == 1) n++;
    sort(a, 0, n - 1);
    printf("\n");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}

