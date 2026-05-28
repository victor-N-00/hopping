#include <stdio.h>

int main() {
    int a[100], n = 0;
    while (scanf("%d", &a[n]) == 1) n++;
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    printf("\n");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}

