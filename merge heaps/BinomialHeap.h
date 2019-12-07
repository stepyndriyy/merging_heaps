#pragma once
#include "IHeap.h"

template<typename T>
class BinomialHeap : public IHeap<T> {
private:
    struct Vertex {
    public:    
        T key;
        Vertex *left_child = nullptr;
        Vertex *next_degree = nullptr;
        int degree = 0;

        Vertex() : key(T()) {}
        Vertex(T _key) : key(_key) {}
        ~Vertex() {
            delete next_degree;
            delete left_child;
        }
    }; 

    Vertex *root;

    BinomialHeap(Vertex *_root); 
        
    static Vertex* mergeSimilar(Vertex* x, Vertex* y);

    static void push_next_degree(Vertex* &ans, Vertex* next, Vertex* &ans_root);

    void normalize(); 

    static void delete_tree(Vertex *cur);   

    static Vertex* find_right_child(Vertex *x);        
public:
    BinomialHeap();
    
    BinomialHeap(const T val);

    ~BinomialHeap();
    
    void insert(const T &elem) override; 
    
    T getMin() override;
    
    T extractMin() override; 
    
    void merge(IHeap<T> &other) override;
    void merge(BinomialHeap<T> &other);

};

template<typename T>
void BinomialHeap<T>::delete_tree(Vertex *cur) {
    if (cur == nullptr)
        return;
    delete_tree(cur->left_child);
    Vertex *next = cur->next_degree;
    delete cur;
    delete_tree(next);
}

template<typename T>
typename BinomialHeap<T>::Vertex* BinomialHeap<T>::find_right_child(Vertex *x) {
    Vertex *child = x->left_child;
    if (child == nullptr) {
        return nullptr;
    }

    for (;child->next_degree != nullptr; child = child->next_degree) {}

    return child;
}

template<typename T>
void BinomialHeap<T>::push_next_degree(Vertex* &ans, Vertex* next, Vertex* &ans_root) {
    if (ans == nullptr) {
        ans = next;
        ans_root = ans;
    } else {
        ans->next_degree = next;
        ans = ans->next_degree;
    }

}

template<typename T>
typename BinomialHeap<T>::Vertex* BinomialHeap<T>::mergeSimilar(Vertex* x, Vertex* y) {
    if (x->degree != y->degree)
        return nullptr;
    if (x->key > y->key) {
        return mergeSimilar(y, x);
    }      
    y->next_degree = nullptr;
    x->next_degree = nullptr;
    if (x->left_child != nullptr) {
        Vertex *right_child = find_right_child(x);
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
    Vertex *cur_x = this->root;
    Vertex *cur_y = other.root;
    Vertex *ans = nullptr;
    Vertex *ans_root = nullptr;

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

            Vertex *next_x = cur_x->next_degree;
            Vertex *next_y = cur_y->next_degree;

            Vertex *merged = mergeSimilar(cur_y, cur_x);
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
    other.root = nullptr;
    
    this->normalize();
}

template<typename T>
void BinomialHeap<T>::normalize() {
    Vertex *cur = this->root;
    Vertex* begin = nullptr;
    Vertex *prev = nullptr;
    
    while (cur != nullptr && cur->next_degree != nullptr) {   
        if (cur->degree == cur->next_degree->degree) {
            Vertex *next = cur->next_degree->next_degree;

            Vertex *merged = mergeSimilar(cur, cur->next_degree);
            
            merged->next_degree = next; 
            cur = merged;
            
            if (prev == nullptr) {
                begin = cur;
            } else {
                prev->next_degree = merged;
            }    
        } else {
            prev = cur;
            cur = cur->next_degree;
        }
    }
    if (begin != nullptr)
        this->root = begin;
}

template<typename T>
void BinomialHeap<T>::merge(IHeap<T> &other) {
    BinomialHeap<T> other_casted = dynamic_cast<BinomialHeap<T> &> (other);
    this->merge(other_casted);
}

template<typename T>
BinomialHeap<T>::BinomialHeap(Vertex *_root) : root(_root) {}

template<typename T>
BinomialHeap<T>::BinomialHeap() : root(nullptr) {}

template<typename T>
BinomialHeap<T>::BinomialHeap(const T val) : root(new Vertex(val))  {}

template<typename T>
BinomialHeap<T>::~BinomialHeap() { 
    delete_tree(root);
}

template<typename T>
void BinomialHeap<T>::insert(const T &elem) {
    BinomialHeap<T> ins(elem);
    this->merge(ins);
}

template<typename T>
T BinomialHeap<T>::getMin() {
    if (this->root == nullptr) {
        return T();
    }
    T min_ = this->root->key;   
    Vertex *cur = this->root;
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
    Vertex *prev_vert = nullptr;
    Vertex *prev_min_vert = nullptr;
    Vertex* min_vert = this->root;
    Vertex *cur = this->root;

    while (cur != nullptr) {
        if (cur->key < min_vert->key) {
            prev_min_vert = prev_vert;
            min_vert = cur;
        }        
        prev_vert = cur;
        cur = cur->next_degree;
    }
    if (prev_min_vert != nullptr) {
        prev_min_vert->next_degree = min_vert->next_degree;
    }
    
    if (min_vert == this->root) {
        this->root = this->root->next_degree;
    }

    min_vert->next_degree = nullptr;
    T answer = min_vert->key;
    BinomialHeap<T> children(min_vert->left_child);
    min_vert->left_child = nullptr;
        
    delete min_vert;    
     
    this->merge(children);
    
    return answer;
}
