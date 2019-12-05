#pragma once
#include "IHeap.h"
#include<iostream>

template<typename T>
struct Vertex {
public:    
    T key;
    Vertex<T> *left_child = nullptr;
    Vertex<T> *next_degree = nullptr;
    int degree = 0;

    Vertex() : key(T()) {}
    Vertex(T _key) : key(_key) {}
};


template<typename T>
class BinomialHeap : public IHeap<T> {
private:
    Vertex<T> *root;

    BinomialHeap(Vertex<T> *_root); 
     
    void mergeSimilar(const BinomialHeap<T> &other);
    
    static Vertex<T>* mergeSimilar(Vertex<T>* x, Vertex<T>* y);

    static void push_next_degree(Vertex<T>* &ans, Vertex<T>* next, Vertex<T>* &ans_root);

    void normalize();        
public:
    BinomialHeap();
    
    BinomialHeap(const T val);

    ~BinomialHeap();
    
    void insert(const T elem) override; 
    
    T getMin() override;
    
    T extractMin() override; 
    
    void merge(IHeap<T> &other) override;
    void merge(BinomialHeap<T> &other);

    void printAll2() {
        printAll(this->root);
    }

    void printDegrees() {
        //printHeap(root);
        
        Vertex<T> *begin_ = root; 
        while (begin_ != nullptr) {
            std::cout << begin_->degree << " " << begin_->key << " | " ;
            begin_ = begin_->next_degree;
        }
        std::cout << '\n';
        //root = begin_;
        
    }
};

template<typename T>
void printAll(Vertex<T> *root) {
    if (!root) return;
    auto cur = root;
    std::cout << cur->key << " ";
    printAll(cur->left_child);
    std::cout << "\n";
    printAll(cur->next_degree);

}

template<typename T>
void printDegrees2(Vertex<T> *root) {
    auto begin_ = root; 
    while (begin_ != nullptr) {
        std::cout << begin_->degree << " " << begin_->key << " | " ;
        begin_ = begin_->next_degree;
    }
    std::cout << '\n';
    //root = begin_;
}

template<typename T>
static   void delete_tree(Vertex<T> *cur) {
    if (cur == nullptr)
        return;
    delete_tree(cur->left_child);
    Vertex<T> *next = cur->next_degree;
    delete cur;
    delete_tree(next);
}

template<typename T>
static Vertex<T>* find_right_child(Vertex<T> *x) {
    Vertex<T> *child = x->left_child;
    if (child == nullptr) {
        return nullptr;
    }

    for (;child->next_degree != nullptr; child = child->next_degree) {}

    return child;
}


template<typename T>
void BinomialHeap<T>::push_next_degree(Vertex<T>* &ans, Vertex<T>* next, Vertex<T>* &ans_root) {
    next->next_degree = nullptr;
    if (ans == nullptr) {
        ans = next;
        ans_root = ans;
    } else {
        ans->next_degree = next;
        ans = ans->next_degree;
    }

}

template<typename T>
Vertex<T>* BinomialHeap<T>::mergeSimilar(Vertex<T>* x, Vertex<T>* y) {
    if (x->degree != y->degree)
        return nullptr;
    if (x->key > y->key) {
        return mergeSimilar(y, x);
    }      
    y->next_degree = nullptr;
    x->next_degree = nullptr;
    if (x->left_child != nullptr) {
        Vertex<T> *right_child = find_right_child(x);
        right_child->next_degree = y;
    } else {
        y->next_degree = nullptr;
        x->left_child = y;
    }   
    x->degree++;

    return x;
}

template<typename T>
void BinomialHeap<T>::merge(BinomialHeap<T> &other) {
    Vertex<T> *cur_x = this->root;
    Vertex<T> *cur_y = other.root;
    Vertex<T> *ans = nullptr;
    Vertex<T> *ans_root = nullptr;

    while(cur_x != nullptr && cur_y != nullptr) {
        int x_degree = cur_x->degree;
        int y_degree = cur_y->degree;
        
        if (x_degree < y_degree) {
            push_next_degree(ans, cur_x, ans_root);
            cur_x = cur_x->next_degree;

        } else if (x_degree > y_degree) {
            push_next_degree(ans, cur_y, ans_root);
            cur_y = cur_y->next_degree;
        } else {

            Vertex<T> *next_x = cur_x->next_degree;
            Vertex<T> *next_y = cur_y->next_degree;

            Vertex<T> *merged = mergeSimilar(cur_y, cur_x);
            cur_x = next_x; 
            cur_y = next_y;
            push_next_degree(ans, merged, ans_root);

        }
    }

    while (cur_x != nullptr) {
        push_next_degree(ans, cur_x, ans_root);
        cur_x = cur_x ->next_degree;
    }

    while (cur_y != nullptr) {
        push_next_degree(ans, cur_y, ans_root);
        cur_y = cur_y ->next_degree;
    }  
    
    this->root = ans_root;
    std::cout << "pizda: "; this->printDegrees();
    //this->normalize();
}

template<typename T>
void BinomialHeap<T>::normalize() {
    /*
    Vertex<T> *cur = this->root;
    Vertex<T>* begin = nullptr;
    Vertex<T> *prev = nullptr;
    std::cout << "umolay\n";
    
    while (cur != nullptr && cur->next_degree != nullptr) {   
        std::cout << "gogogo\n";
        if (cur->degree == cur->next_degree->degree) {
            Vertex<T> *next = cur->next_degree->next_degree;

            Vertex<T> *merged = mergeSimilar(cur, cur->next_degree);
            
            //std::cout << "merged:: \n"; printDegrees2(merged); std::cout << "--_---_--__---_\n";
            
            merged->next_degree = next; 
            cur = merged;
            
            if (prev == nullptr) {
                begin = cur;
            } else {
                prev->next_degree = merged;
            }
            
            //std::cout << "cur_merged(): \n"; printDegrees2(cur); std::cout << "__=---__-\n";        
        } else {
            prev = cur;
            cur = cur->next_degree;
        }
    }
    if (begin != nullptr)
        this->root = begin;
    */
}

template<typename T>
void BinomialHeap<T>::merge(IHeap<T> &other) {
    BinomialHeap<T> other_casted = dynamic_cast<BinomialHeap<T> &> (other);
    this->merge(other_casted);
}

template<typename T>
BinomialHeap<T>::BinomialHeap(Vertex<T> *_root) : root(_root) {}

template<typename T>
BinomialHeap<T>::BinomialHeap() : root(nullptr) {}

template<typename T>
BinomialHeap<T>::BinomialHeap(const T val) : root(new Vertex<T>(val))  {}

template<typename T>
BinomialHeap<T>::~BinomialHeap() { 
    delete_tree(root);
}

template<typename T>
void BinomialHeap<T>::insert(const T elem) {
    BinomialHeap<T> ins(elem);
    this->merge(ins);
}

template<typename T>
T BinomialHeap<T>::getMin() {
    if (this->root == nullptr) {
        return T();
    }
    T min_ = this->root->key;   
    Vertex<T> *cur = this->root;
    while (cur != nullptr) {
        min_ = (cur->key < min_) ? cur->key : min_;
        cur = cur->next_degree;
    }
    return min_;
}

template<typename T>
T BinomialHeap<T>::extractMin() {
    if (this->root == nullptr) {
        return T();
    }
    Vertex<T> *prev_vert = nullptr;
    Vertex<T> *prev_min_vert = nullptr;
    Vertex<T>* &min_vert = this->root;
    Vertex<T> *cur = this->root;

    while (cur != nullptr) {
        if (cur->key < min_vert->key) {
            prev_min_vert = prev_vert;
            min_vert = cur;
        }        
        prev_vert = cur;
        cur = cur->next_degree;
    }
    std::cout << "pidor\n";
    if (prev_min_vert != nullptr) {
        prev_min_vert->next_degree = min_vert->next_degree;
    }
    min_vert->next_degree = nullptr;
    
    T answer = min_vert->key;
    BinomialHeap<T> children(min_vert->left_child);
    
    
    if (this->root == nullptr) {
        std::cout << "tvoya mater sluxa\n";
    } else {
        std::cout << "precrasnaya jenshina\n" << '\n';
    }
    
    //delete min_vert;
    std::cout << "this: "; this->printDegrees(); std::cout << "=++=+==++\n"; 
    
    this->merge(children);

    
    
    return answer;
}

