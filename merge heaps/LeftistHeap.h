#pragma once
#include<iostream>
#include "IHeap.h"

template<typename T>
void swap(T &a, T &b) {
    T cmp = a;
    a = b;
    b = cmp;    
}

template<typename T>
class LeftistHeap : public IHeap<T> {
private:
    struct Vertex {
        T key;
        Vertex* left = nullptr;
        Vertex* right = nullptr;
        int rank = 0;
        Vertex() : key(T()) {}
        Vertex(T _key) : key(_key) {} 
        ~Vertex() {
            delete left;
            delete right;
        }

        void updateTree() {
            if (left != nullptr && right != nullptr) {
                int min_rank = right->rank;
                if (left->rank < right->rank) {
                    swap(left, right);
                    min_rank = left->rank;
                }
                this->rank = min_rank + 1;
                return;
            }

            if (left != nullptr) {
                this->rank = left->rank + 1;
                return;
            } 
            if (right != nullptr) {
                swap(right, left);
                this->rank = left->rank + 1;
                return;
            }

            this->rank = 0;
        }
    };

    Vertex *root = nullptr;

    LeftistHeap(const T &_key);
    
    static Vertex* merge(Vertex *first, Vertex *second);
    
    static void deleteTree(Vertex* vert);
        
public:
    LeftistHeap();
    ~LeftistHeap();
    
    void insert(const T &elem) override;

    T getMin() override;
    T extractMin() override;

    void merge(LeftistHeap<T> &other);
    void merge(IHeap<T> &other) override;

};

template<typename T>
T LeftistHeap<T>::getMin() {
    if (this->root == nullptr) {
        return T();
    }
    return this->root->key;
}

template<typename T>
LeftistHeap<T>::LeftistHeap() {}


template<typename T>
LeftistHeap<T>::LeftistHeap(const T &_key) : root(new Vertex(_key)) {}

template<typename T>
void LeftistHeap<T>::merge(LeftistHeap<T> &other) {
    this->root = merge(this->root, other.root);
    other.root = nullptr;
}

template<typename T>
void LeftistHeap<T>::merge(IHeap<T> &other) {
    LeftistHeap<T> other_casted = dynamic_cast<LeftistHeap<T> &> (other);
    this->merge(other_casted);
}

template<typename T>
typename LeftistHeap<T>::Vertex* LeftistHeap<T>::merge(Vertex *first_root, Vertex *second_root) {
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
void LeftistHeap<T>::insert(const T &elem) {
    LeftistHeap<T> ins(elem);
    this->merge(ins);
}

template<typename T>
T LeftistHeap<T>::extractMin() {
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
LeftistHeap<T>::~LeftistHeap() {
    deleteTree(this->root);
}

template<typename T>
void LeftistHeap<T>::deleteTree(Vertex* vert) {
    if (vert == nullptr) {
        return;
    }
    deleteTree(vert->left);
    deleteTree(vert->left);
    delete vert;
}
