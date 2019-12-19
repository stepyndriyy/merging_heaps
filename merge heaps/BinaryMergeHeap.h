#pragma once
#include<iostream>
#include "IHeap.h"

template<typename T>
class BinaryMergeHeap : public IHeap<T> {
protected:
    struct Vertex {
        public:
            T key;
            Vertex* left = nullptr;
            Vertex* right = nullptr;

            Vertex() : key(T()) {}
            Vertex(T _key) : key(_key) {} 
            virtual ~Vertex() {
                delete left;
                delete right;
            }

            virtual void updateTree() {}
    };

    template<typename U>
    static void swap(U &a, U &b) {
        U c = a;
        a = b;
        b = c;
    }
    
    Vertex *root = nullptr;

    BinaryMergeHeap(const T &_key);
    
    static Vertex* merge(Vertex *first, Vertex *second);
    
    static void deleteTree(Vertex* vert);
        
public:
    BinaryMergeHeap();
    ~BinaryMergeHeap();
    
    void insert(const T &elem) override;

    T getMin() override;
    T extractMin() override;

    void merge(BinaryMergeHeap<T> &other);
    void merge(IHeap<T> &other) override;

};

template<typename T>
T BinaryMergeHeap<T>::getMin() {
    if (this->root == nullptr) {
        return T();
    }
    return this->root->key;
}

template<typename T>
BinaryMergeHeap<T>::BinaryMergeHeap() {}


template<typename T>
BinaryMergeHeap<T>::BinaryMergeHeap(const T &_key) : root(new Vertex(_key)) {}

template<typename T>
void BinaryMergeHeap<T>::merge(BinaryMergeHeap<T> &other) {
    this->root = merge(this->root, other.root);
    other.root = nullptr;
}

template<typename T>
void BinaryMergeHeap<T>::merge(IHeap<T> &other) {
    BinaryMergeHeap<T> &other_casted = dynamic_cast<BinaryMergeHeap<T> &> (other);
    this->merge(other_casted);
}

template<typename T>
typename BinaryMergeHeap<T>::Vertex* BinaryMergeHeap<T>::merge(Vertex *first_root, Vertex *second_root) {
    if (first_root == nullptr) {
        return second_root;
    }
    if (second_root == nullptr) {
        return first_root;
    }

    if (first_root->key <= second_root->key) {
        first_root->right = merge(first_root->right, second_root);
        first_root->updateTree();
        return first_root;
    } else {
        second_root->right = merge(first_root, second_root->right);
        second_root->updateTree();
        return second_root;
    }
}

template<typename T>
void BinaryMergeHeap<T>::insert(const T &elem) {
    BinaryMergeHeap<T> ins(elem);
    this->merge(ins);
}

template<typename T>
T BinaryMergeHeap<T>::extractMin() {
    if (root == nullptr) {
        return T();
    }
    
    Vertex *min_vert = this->root;
    T min_ = min_vert->key;
    Vertex *left = this->root->left;
    Vertex *right = this->root->right;
    
    this->root = merge(left, right);
    
    return min_;
}

template<typename T>
BinaryMergeHeap<T>::~BinaryMergeHeap() {
    deleteTree(this->root);
}

template<typename T>
void BinaryMergeHeap<T>::deleteTree(Vertex* vert) {
    if (vert == nullptr) {
        return;
    }
    deleteTree(vert->left);
    deleteTree(vert->left);
    delete vert;
}
