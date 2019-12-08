#include<iostream>
#include "BinomialHeap.h"
//#include "LeftistHeap.h"
//#include "SkewHeap.h"
#include "TestingEazyHeap.h"
#include "GenerateHeapTest.h"
#include<vector>
#include<ctime>
#include<string>

using namespace std;

int testTrue(char* File) {
    vector<BinomialHeap<int> > a;
    vector<TestingEazyHeap<int> > real;
    freopen(File, "r", stdin);
    string type;
    int operation_num = 0;
    while(cin >> type) {   
        operation_num++;
        if (type == "AddHeap") {
            
            int x; cin >> x;

            a.push_back(BinomialHeap<int>());
            real.push_back(TestingEazyHeap<int>());
            a.back().insert(x);
            real.back().insert(x);
        
        }
        if (type == "ExtractMin") {
            int num; cin >> num;
            int min_ = a[num].extractMin();
            int real_min = real[num].extractMin();
            if (min_ != real_min) {
                fclose(stdin);
                return operation_num;
            }
        }
        if (type == "getMin") {
            int num; cin >> num;
            int min_ = a[num].getMin();
            int real_min = real[num].getMin();
            if (min_ != real_min) {
                fclose(stdin);
                return operation_num;
            }
        }
        if (type == "Meld") {
            int num1, num2;
            cin >> num1 >> num2;
            a[num1].merge(a[num2]);
            real[num1].merge(real[num2]);
        }
        if (type == "Insert") {
            int num, key;
            cin >> num >> key;
            a[num].insert(key);
            real[num].insert(key);

        }
    }
    return 0;
}

void generateTest(char* str, int size) {
    GenerateHeapTest create_test(str);
    
    for (int i = 0; i < size; ++i) {
        create_test.insertRandom();    
    }
} 


int main() {   

    char str[10] = {"input.txt"};
    int n; cin >> n;
    generateTest(str, n);
    int ans = testTrue(str);
    
    //freopen(str, "w", stdout);
    
    cout << ans << '\n';
}
