#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Box {
    int h, w, d;
};

bool compare(Box a, Box b) {
    return (a.w * a.d) > (b.w * b.d);
}

int maxStackHeight(vector<Box>& boxes) {
    vector<Box> rot;
    for (Box b : boxes) {
        rot.push_back(b);
        rot.push_back({b.w, max(b.h, b.d), min(b.h, b.d)});
        rot.push_back({b.d, max(b.h, b.w), min(b.h, b.w)});
    }
    
    sort(rot.begin(), rot.end(), compare);
    
    int n = rot.size();
    vector<int> msh(n);
    for (int i = 0; i < n; i++) msh[i] = rot[i].h;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (rot[i].w < rot[j].w && rot[i].d < rot[j].d && msh[i] < msh[j] + rot[i].h) {
                msh[i] = msh[j] + rot[i].h;
            }
        }
    }
    
    int mx = -1;
    for (int i = 0; i < n; i++) mx = max(mx, msh[i]);
    return mx;
}

int main() {
    vector<Box> boxes = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};
    cout << "Max stack height: " << maxStackHeight(boxes) << endl;
    return 0;
}
