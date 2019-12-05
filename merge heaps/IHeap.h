template<typename T>
class IHeap {
private:
       
public:
    virtual void insert(const T elem) = 0;
    
    virtual T getMin() = 0;
    virtual T extractMin() = 0;    

    virtual void merge(IHeap<T> &other) = 0;
};      