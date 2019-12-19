#pragma once
#include<iostream>
#include "BinaryMergeHeap.h"

template<typename T>
class LeftistHeap : public BinaryMergeHeap<T> {
    struct Vertex : public BinaryMergeHeap<T>::Vertex {
    
        typedef typename BinaryMergeHeap<T>::Vertex Parent;  
        
        int rank = 0;
        
        void updateTree() {
            if (Parent::left != nullptr && Parent::right != nullptr) {
                int min_rank = Parent::right->rank;
                if (Parent::left->rank < Parent::right->rank) {
                    Parent::swap(Parent::left, Parent::right);
                    min_rank = Parent::left->rank;
                }
                this->rank = min_rank + 1;
                return;
            }

            if (Parent::left != nullptr) {
                this->rank = Parent::left->rank + 1;
                return;
            } 
            if (Parent::right != nullptr) {
                Parent::swap(Parent::right, Parent::left);
                this->rank = Parent::left->rank + 1;
                return;
            }

            this->rank = 0;
        }

    };
};