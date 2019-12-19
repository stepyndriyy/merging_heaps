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
#include "gtest/gtest.h"

struct command {
    std::string type;
    int num1;
    int num2;
    command() {}
    command(std::string _t, int n1) : type(_t), num1(n1) {}
    command(std::string _t, int n1, int n2) : type(_t), num1(n1), num2(n2) {}
};


template<typename T>
void testCorrect(std::vector<command> &inp, int count) {
    std::vector<IHeap<int>* > a;

    std::vector<TestingEazyHeap<int> > real;
    //freopen(File, "r", stdin);
    std::string type;
    for (int i = 0; i < count; ++i) {  
        type = inp[i].type;    
        if (type == "AddHeap") {
            int x = inp[i].num1; 
            IHeap<int>* next = new T();
            a.push_back(next);
            real.push_back(TestingEazyHeap<int>());
            
            a.back()->insert(x);
            real.back().insert(x);
        
        }
        if (type == "ExtractMin") {
            int num = inp[i].num1;
            int min_ = a[num]->extractMin();
            int real_min = real[num].extractMin();
            
            ASSERT_EQ(real_min, min_);
            
        }
        if (type == "getMin") {
            int num = inp[i].num1; 
            int min_ = a[num]->getMin();
            int real_min = real[num].getMin();
            
            ASSERT_EQ(real_min, min_);
        }
        if (type == "Meld") {
            int num1 = inp[i].num1, 
            num2 = inp[i].num2;
            
            a[num1]->merge(*a[num2]);
            real[num1].merge(real[num2]);
        }
        if (type == "Insert") {
            int num = inp[i].num1, 
                key = inp[i].num2;
            
            a[num]->insert(key);
            real[num].insert(key);
        }
    }
}


std::vector<command> generateTest(int size) {
    char str[10] = {"input.txt"};
    GenerateHeapTest create_test(str);
    int i = 0;
    while (i < size) {
        if (create_test.insertRandom()) {
            i++;
        }    
    }
    freopen(str, "r", stdin);
    std::vector<command> commands(size);
    for (int i = 0; i < size; ++i) {
        std::string type;
        int x, y;
        std::cin >> type;
        if (type == "AddHeap") {
            std::cin >> x;
            commands[i] = command(type, x);
        }
        if (type == "ExtractMin") {
            std::cin >> x;
            commands[i] = command(type, x);
        }
        if (type == "getMin") {
            std::cin >> x;
            commands[i] = command(type, x);    
        }
        if (type == "Meld") {
            std::cin >> x;
            std::cin >> y;
            commands[i] = command(type, x, y);
        }
        if (type == "Insert") {    
            std::cin >> x;
            std::cin >> y;
            commands[i] = command(type, x, y);
        }
    }
    fclose(stdin);
    remove("input.txt");
} 

template<typename T>
float speedTest(std::vector<command> &inp, int count) {
    std::vector<IHeap<int>* > a;
    std::string type;
    int operation_num = 0;
    clock_t start_time;
    start_time = clock();
    for (int cnt_ = 0; cnt_ < count; ++cnt_) {   
        type = inp[i].type; 
        operation_num++;
        if (type == "AddHeap") {
            int x = inp[i].num1;
            IHeap<int>* next = new T();
            a.push_back(next);
            a.back()->insert(x);
        
        }
        if (type == "ExtractMin") {
            int num = inp[i].num1; 
            int min_ = a[num]->extractMin();
        }
        if (type == "getMin") {
            int num = inp[i].num1; 
            int min_ = a[num]->getMin();
        }
        if (type == "Meld") {
            int num1 = inp[i].num1, 
                num2 = inp[i].num2;
            a[num1]->merge(*a[num2]);
        }
        if (type == "Insert") {
            int num = inp[i].num1, 
                key = inp[i].num2;
            a[num]->insert(key);
        }
    }
    float answer = (float)(clock() - start_time) / CLOCKS_PER_SEC;
    return answer;
}


class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FooTest() {
     // You can do set-up work for each test here.
  }

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

};


int main() {   

    char str[10] = {"input.txt"};
    int n; 
    std::cin >> n;
    


    int ans1 = testCorrect<BinomialHeap<int> >(str, n);
    int ans2 = testCorrect<SkewHeap<int> >(str, n );
    int ans3 = testCorrect<LeftistHeap<int> >(str, n);
    
    if (ans1 != ans2 || ans2 != ans3 || ans3 != 0) {
        std::cout << "not correct\n";
        std::cout << "Binomial: " << ans1 << '\n';
        std::cout << "Lefist: " << ans2 << '\n';
        std::cout << "Skew: " << ans3 << '\n';
        return 0;
    }
    float time1 = speedTest<BinomialHeap<int> >(str, n);
    float time2 = speedTest<SkewHeap<int> > (str, n);
    float time3 = speedTest<LeftistHeap<int> >  (str, n);
    std::cout << "number of tests: " << n << '\n';
    std::cout << "work time: \n";
    std::cout << "Binomial: " << time1 << '\n';
    std::cout << "Lefist: " << time2 << '\n';       
    std::cout << "Skew: " << time3 << '\n';
}
