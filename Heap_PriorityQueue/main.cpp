#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Heap {
    vector <int> node;
    int nHeap = 0;

    Heap() {}
    Heap(char * filename) {
        fstream inFile;
        inFile.open(filename);

        int value;
        while (inFile >> value)
            insert(value);

        inFile.close();
    }

    void insert(int key) {
        node.push_back(key);  ++nHeap;
        for (int cur = nHeap-1, par; cur; cur = (cur-1)/2) {
            par = (cur-1)/2;
            if (node[par] <= node[cur]) break; else swap(node[cur], node[par]);
        }
    }

    int removeMin() {
        int res = node[0];
        swap(node[0], node[nHeap-1]);
        node.pop_back();  --nHeap;

        for (int cur = 0, child; ; ) {
            child = cur*2+1;
            if (child >= nHeap) break;  //cur does not have child
            if (child+1 < nHeap && node[child] > node[child+1])
                child++;  //find the smaller child
            if (node[cur] <= node[child]) break;
            else {
                swap(node[cur], node[child]);
                cur = child;
            }
        }

        return res;
    }

    int getMin() { return node[0]; }

    int isEmpty() { return !nHeap; }
};

int main() {
    Heap myHeap("a.txt");

    while (!myHeap.isEmpty()) {
        cout << setw(3) << myHeap.removeMin();
        //for (int i = 0; i < myHeap.nHeap; ++i) {
        //cout << setw(3) << myHeap.node[i];
        //}
    }
    cout << endl;
}
