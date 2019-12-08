#pragma once
#include<set>
#include "IHeap.h"

template<typename T>
class TestingEazyHeap : public IHeap<T> {
private:
    std::set<T> tree; 
public:
    TestingEazyHeap() {}
    
    void insert(const T &elem) {   
        tree.insert(elem);
    }

    T getMin() {
        return *(tree.begin());
    }
    T extractMin() {
        T answer = *(tree.begin());
        tree.erase(tree.begin());
        return answer;
    }    

    void merge(TestingEazyHeap<T> &other) {
        while (!other.tree.empty()) {
            tree.insert(*(other.tree.begin()));
            other.tree.erase(*(other.tree.begin()));
        }
    }

    void merge(IHeap<T> &other) {
        TestingEazyHeap<T> other_casted = dynamic_cast<TestingEazyHeap<T> &> (other);
        this->merge(other_casted);
    }
};





