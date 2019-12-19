#pragma once
#include<iostream>
#include "BinaryMergeHeap.h"


/*
void updateTree {
    swap(second_root->left, second_root->right);
}

*/
template<typename T>
class SkewHeap : public BinaryMergeHeap<T> {
    struct Vertex : public BinaryMergeHeap<T>::Vertex {      
        
        typedef typename BinaryMergeHeap<T>::Vertex Parent;  
        
        void updateTree() {
            Parent::swap(Parent::left, Parent::right);
        }
    };
};