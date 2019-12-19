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
        std::string type;
    for (int i = 0; i < size; ++i) {  
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
    return commands;
} 

template<typename T>
float speedTest(std::vector<command> &inp, int count) {
    std::vector<IHeap<int>* > a;
    std::string type;
    int operation_num = 0;
    clock_t start_time;
    start_time = clock();
    for (int i = 0; i < count; ++i) {   
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
 public: 
    std::vector<command> test;
    int test_num = 100000;
 protected:
  FooTest() {
     // You can do set-up work for each test here.
  }

  void SetUp() override {
      test = generateTest(test_num);
  }

  void TearDown() override {
  }

};

TEST_F(FooTest, correct_Binomial) {
    testCorrect<BinomialHeap<int> >(test, test_num);
}
TEST_F(FooTest, correct_leftist) {
    testCorrect<LeftistHeap<int> >(test, test_num);
}

TEST_F(FooTest, correct_skew) {
    testCorrect<SkewHeap<int> >(test, test_num);
}

TEST_F(FooTest, speed_Binomial) {
    float time_ = speedTest<BinomialHeap<int> >(test, test_num);
}

TEST_F(FooTest, speed_leftist) {
    float time_ = speedTest<LeftistHeap<int> >(test, test_num);
}

TEST_F(FooTest, speed_skew) {
    float time_ = speedTest<SkewHeap<int> >(test, test_num);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}