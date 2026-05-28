#include <iostream>
using namespace std;

int main() {
    cout << "Multi-Source/Sink Max Flow:" << endl;
    cout << "Approach: Add a super-source connected to all sources with infinite capacity," << endl;
    cout << "and a super-sink connected to all sinks with infinite capacity." << endl;
    cout << "Then run standard Edmonds-Karp/Ford-Fulkerson from super-source to super-sink." << endl;
    return 0;
}
