#pragma once
#include<iostream>
#include "IHeap.h"

template<typename T>
class SkewHeap : public IHeap<T> {
private:
    struct Vertex {
        T key;
        Vertex* left = nullptr;
        Vertex* right = nullptr;
        
        Vertex() : key(T()) {}
        Vertex(T _key) : key(_key) {} 
        ~Vertex() {
            delete left;
            delete right;
        }
    };

    template<typename U>
    static void swap(U &a, U &b) {
        U c = a;
        a = b;
        b = c;
    }
    
    Vertex *root = nullptr;

    SkewHeap(const T &_key);
    
    static Vertex* merge(Vertex *first, Vertex *second);
    
    static void deleteTree(Vertex* vert);
        
public:
    SkewHeap();
    ~SkewHeap();
    
    void insert(const T &elem) override;

    T getMin() override;
    T extractMin() override;

    void merge(SkewHeap<T> &other);
    void merge(IHeap<T> &other) override;

};

template<typename T>
T SkewHeap<T>::getMin() {
    if (this->root == nullptr) {
        return T();
    }
    return this->root->key;
}

template<typename T>
SkewHeap<T>::SkewHeap() {}


template<typename T>
SkewHeap<T>::SkewHeap(const T &_key) : root(new Vertex(_key)) {}

template<typename T>
void SkewHeap<T>::merge(SkewHeap<T> &other) {
    this->root = merge(this->root, other.root);
    other.root = nullptr;
}

template<typename T>
void SkewHeap<T>::merge(IHeap<T> &other) {
    SkewHeap<T> &other_casted = dynamic_cast<SkewHeap<T> &> (other);
    this->merge(other_casted);
}

template<typename T>
typename SkewHeap<T>::Vertex* SkewHeap<T>::merge(Vertex *first_root, Vertex *second_root) {
    if (first_root == nullptr) {
        return second_root;
    }
    if (second_root == nullptr) {
        return first_root;
    }

    if (first_root->key <= second_root->key) {
        first_root->right = merge(first_root->right, second_root);
        swap(first_root->left, first_root->right);
        return first_root;
    } else {
        second_root->right = merge(first_root, second_root->right);
        swap(second_root->left, second_root->right);
        return second_root;
    }
}

template<typename T>
void SkewHeap<T>::insert(const T &elem) {
    SkewHeap<T> ins(elem);
    this->merge(ins);
}

template<typename T>
T SkewHeap<T>::extractMin() {
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
SkewHeap<T>::~SkewHeap() {
    deleteTree(this->root);
}

template<typename T>
void SkewHeap<T>::deleteTree(Vertex* vert) {
    if (vert == nullptr) {
        return;
    }
    deleteTree(vert->left);
    deleteTree(vert->left);
    delete vert;
}
