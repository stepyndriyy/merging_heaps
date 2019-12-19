#include<iostream>
#include "BinomialHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "TestingEazyHeap.h"
#include "GenerateHeapTest.h"
#include<vector>
#include<ctime>
#include<string>
#include <cstdio>
//#include <stdio.h>


int testCorrect(char* File, int heap_type, int count) {
    std::vector<IHeap<int>* > a;

    std::vector<TestingEazyHeap<int> > real;
    freopen(File, "r", stdin);
    std::string type;
    int operation_num = 0;
    for (int cnt_ = 0; cnt_ < count; ++cnt_) {  
        
        operation_num++;
        if (type == "AddHeap") {
            int x; 
            std::cin >> x;

            if (heap_type == 0) {
                IHeap<int>* next = new BinomialHeap<int>();
                a.push_back(next);
            }
            if (heap_type == 1) {
                IHeap<int>* next = new LeftistHeap<int>();
                a.push_back(next);
            }
            if (heap_type == 2) {
                IHeap<int>* next = new SkewHeap<int>();
                a.push_back(next);
            }
            
            real.push_back(TestingEazyHeap<int>());
            a.back()->insert(x);
            real.back().insert(x);
        
        }
        if (type == "ExtractMin") {
            int num; 
            std::cin >> num;
            int min_ = a[num]->extractMin();
            int real_min = real[num].extractMin();
            if (min_ != real_min) {
                fclose(stdin);
                return operation_num;
            }
        }
        if (type == "getMin") {
            int num; 
            std::cin >> num;
            int min_ = a[num]->getMin();
            int real_min = real[num].getMin();
            if (min_ != real_min) {
                fclose(stdin);
                return operation_num;
            }
        }
        if (type == "Meld") {
            int num1, num2;
            std::cin >> num1 >> num2;
            a[num1]->merge(*a[num2]);
            real[num1].merge(real[num2]);
        }
        if (type == "Insert") {
            int num, key;
            std::cin >> num >> key;
            a[num]->insert(key);
            real[num].insert(key);

        }
    }
    std::fflush(stdin);
    fclose(stdin);
    
    return 0;
}


void generateTest(char* str, int size) {
    GenerateHeapTest create_test(str);
    int i = 0;
    while (i < size) {
        if (create_test.insertRandom()) {
            i++;
        }    
    }
} 

float speedTest(char* File, int heap_type, int count) {
    std::vector<IHeap<int>* > a;
    freopen(File, "r", stdin);
    std::string type;
    int operation_num = 0;
    clock_t start_time;
    start_time = clock();
    for (int cnt_ = 0; cnt_ < count; ++cnt_) {   
        std::cin >> type;
        operation_num++;
        if (type == "AddHeap") {
            int x; std::cin >> x;

            if (heap_type == 0) {
                IHeap<int>* next = new BinomialHeap<int>();
                a.push_back(next);
            }
            if (heap_type == 1) {
                IHeap<int>* next = new LeftistHeap<int>();
                a.push_back(next);
            }
            if (heap_type == 2) {
                IHeap<int>* next = new SkewHeap<int>();
                a.push_back(next);
            }
            a.back()->insert(x);
        
        }
        if (type == "ExtractMin") {
            int num; std::cin >> num;
            int min_ = a[num]->extractMin();
        }
        if (type == "getMin") {
            int num; std::cin >> num;
            int min_ = a[num]->getMin();
        }
        if (type == "Meld") {
            int num1, num2;
            std::cin >> num1 >> num2;
            a[num1]->merge(*a[num2]);
        }
        if (type == "Insert") {
            int num, key;
            std::cin >> num >> key;
            a[num]->insert(key);
        }
    }
    float answer = (float)(clock() - start_time) / CLOCKS_PER_SEC;
    std::fflush(stdin);
    fclose(stdin);
        eturn answer;
}

int main() {   

    char str[10] = {"input.txt"};
    int n; 
    std::cin >> n;
    generateTest(str, n);


    int ans1 = testCorrect(str, 0, n);
    int ans2 = testCorrect(str, 1, n );
    int ans3 = testCorrect(str, 2, n);
    
    if (ans1 != ans2 || ans2 != ans3 || ans3 != 0) {
        std::cout << "not correct\n";
        std::cout << "Binomial: " << ans1 << '\n';
        std::cout << "Lefist: " << ans2 << '\n';
        std::cout << "Skew: " << ans3 << '\n';
        return 0;
    }
    float time1 = speedTest(str, 0, n);
    float time2 = speedTest(str, 1, n);
    float time3 = speedTest(str, 2, n);
    std::cout << "number of tests: " << n << '\n';
    std::cout << "work time: \n";
    std::cout << "Binomial: " << time1 << '\n';
    std::cout << "Lefist: " << time2 << '\n';
    std::cout << "Skew: " << time3 << '\n';
}
