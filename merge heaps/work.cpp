#include<iostream>
//#include "BinomialHeap.h"
#include "LeftistHeap.h"

using namespace std;

int main() {
    
    LeftistHeap<int> a;

    
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        a.insert(x);
        //cout << "cur min: " << a.getMin() << '\n';
    } 

    LeftistHeap<int> b;

    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        b.insert(x);
    } 

    a.merge(b);
    for (int i = 0; i < m + n; ++i) {
        cout << a.extractMin() << " ";
    }
    /*
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
    */
   
}
