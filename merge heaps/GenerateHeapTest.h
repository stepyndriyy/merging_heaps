#pragma once
#include<stdlib.h>
#include<ctime>
#include<fstream>
#include<vector>
class GenerateHeapTest {
private:
    std::ofstream out;  
    std::vector<int> all_trees;
    int heap_count = 0;  
    int all_operations = 5;  
public: 
    GenerateHeapTest(char* _File) {
        out.open(_File);
        std::srand(std::time(NULL));
    }

    ~GenerateHeapTest() {
        out.close();
    }

    void insertAddHeap() {
        heap_count++;
        int x = rand() + rand();
        out << "AddHeap " << x << '\n'; 
        all_trees.push_back(1);
    }

    void insertInsert() {
        if (heap_count == 0) {
            return;
        }
        int num = rand() % heap_count;
        int x = rand() + rand(); 
        all_trees[num]++;
        out << "Insert " << num << " " << x << '\n';
    }

    void insertGetMin() {
        if (heap_count == 0)
            return;
        int num = rand() % heap_count;
        out << "getMin " << num << '\n';  
    }

    void insertExtractMin() {
        if (heap_count == 0) {
            return;
        }
        
        int num = rand() % heap_count;
        if (all_trees[num] == 0) {
            return;
        }
        out << "ExtractMin " << num << '\n';
        all_trees[num]--;
    }

    void insertMeld() {
        if (heap_count < 2) {
            return;
        }
        int num1 = rand() % heap_count;
        int num2 = rand() % heap_count;
        while (num1 == num2) {
            num2 = rand() % heap_count;
        } 
        out << "Meld " << num1 << " " << num2 << '\n';
        all_trees[num1] += all_trees[num2];
        all_trees[num2] = 0;
    }

    void insertRandom() {
        int func_ = rand() % all_operations;
        if (func_ == 0) {
            insertAddHeap();
        }
        if (func_ == 1) {
            insertExtractMin();
        }
        if (func_ == 2) {
            insertInsert();
        }
        if (func_ == 3) {
            insertMeld();
        }
        if (func_ == 4) {
            insertGetMin();
        }
        
    }
}; 