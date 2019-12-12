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

    static int randnum() {
        int x = (rand() + rand());
        if (rand() % 2 == 0) {
            x*= -1;
        }
        return x;
    }

public: 
    GenerateHeapTest(char* _File) {
        out.open(_File);
        std::srand(std::time(NULL));
    }

    ~GenerateHeapTest() {
        out.close();
    }

    bool insertAddHeap() {
        heap_count++;
        
        out << "AddHeap " << randnum() << '\n'; 
        all_trees.push_back(1);
        return true;
    }

    bool insertInsert() {
        if (heap_count == 0) {
            return false;
        }
        int num = rand() % heap_count;
        
        all_trees[num]++;
        out << "Insert " << num << " " << randnum() << '\n';
        return true;
    }

    bool insertGetMin() {
        if (heap_count == 0)
            return false;
        int num = rand() % heap_count;
        if (all_trees[num] == 0) return false ;
        out << "getMin " << num << '\n'; 
        return true; 
    }

    bool insertExtractMin() {
        if (heap_count == 0) {
            return false ;
        }
        
        int num = rand() % heap_count;
        if (all_trees[num] == 0) {
            return false ;
        }
        out << "ExtractMin " << num << '\n';
        all_trees[num]--;
        return true;
    }

    bool insertMeld() {
        if (heap_count < 2) {
            return false;
        }
        int num1 = rand() % heap_count;
        int num2 = rand() % heap_count;
        while (num1 == num2) {
            num2 = rand() % heap_count;
        } 
        out << "Meld " << num1 << " " << num2 << '\n';
        all_trees[num1] += all_trees[num2];
        all_trees[num2] = 0;
        return true;
    }

    bool insertRandom() {
        int func_ = rand() % all_operations;
        if (func_ == 0) {
            return insertAddHeap();
        }
        if (func_ == 1) {
            return insertExtractMin();
        }
        if (func_ == 2) {
            return insertInsert();
        }
        if (func_ == 3) {
            return insertMeld();
        }
        if (func_ == 4) {
            return insertGetMin();
        }
        
    }
}; 