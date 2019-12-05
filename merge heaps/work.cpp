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
    
    a.printDegrees();
    cout << "------------=------------\n";
    a.printAll2();
    cout << "================\n";
    
    for (int i = 0; i < n + m; ++i) {
        a.extractMin();

        a.printDegrees();
        cout << "------------=------------\n";
        a.printAll2();
        cout << "================\n";
        
    }

    /*
    cin >> m; 
    for (int i = 0; i < m; ++i) {
        cin >> x;
        b.insert(x);
    }
    */
   /*
    a.printDegrees();
    cout << "------------=------------\n";
    a.printAll2();
    cout << "================\n";
    */
/*
    cout << "min: " << a.extractMin() << '\n';
    a.printDegrees();
    cout << "------------=------------\n";
    a.printAll2();
    cout << "================\n";

    cout << "min: " << a.extractMin() << '\n';
    a.printDegrees();
    cout << "------------=------------\n";
    a.printAll2();
    cout << "================\n";
*/    
    /*
    for (int i = 0; i < n; ++i)  {
        cout << a.extractMin() << " ";
    }
    */

}
