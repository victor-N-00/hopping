#include <iostream>
using namespace std;

class DynamicArray {
    int* arr;
    int capacity;
    int size;
public:
    DynamicArray() : capacity(1), size(0) {
        arr = new int[capacity];
    }
    
    void push_back(int val) {
        if (size == capacity) {
            capacity *= 2;
            int* newArr = new int[capacity];
            for (int i = 0; i < size; i++) newArr[i] = arr[i];
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = val;
    }
    
    int get(int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of bounds");
        return arr[index];
    }
    
    ~DynamicArray() {
        delete[] arr;
    }
};

int main() {
    DynamicArray da;
    da.push_back(5);
    da.push_back(10);
    cout << "Element at 1: " << da.get(1) << endl;
    return 0;
}
