#include<iostream>
#include "BinomialHeap.h"

using namespace std;

int main() {
    
    BinomialHeap<int> a, b;
    int n, m, x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a.insert(x);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> x;
        b.insert(x);
    }
    a.merge(b);
    
    
    for (int i = 0; i < n + m; ++i) {
        cout << a.extractMin() << " ";
    }

   
}
