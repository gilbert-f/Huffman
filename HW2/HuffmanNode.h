// class for the nodes of Huffman tree

#ifndef HuffmanNode_h
#define HuffmanNode_h

#include <iostream>

using namespace std;

template<typename Priority, typename Data>
class HuffmanNode
{
public:
    HuffmanNode(): priority_(Priority{}), data_(Data{}), left_(nullptr), right_(nullptr) {}
    HuffmanNode(Priority priority, Data data): priority_(priority), data_(data), left_(nullptr), right_(nullptr) {}
    HuffmanNode(Priority priority): priority_(priority), data_(Data{}), left_(nullptr), right_(nullptr) {}
    
    const Priority& getPriority() const {return priority_;}
    Data& getData() {return data_;}
    
    void setPriority(Priority priority) {priority_ = priority;}
    void setData(Data data) {data_ = data;}
    
    HuffmanNode<Priority, Data>* getLeft() {return left_;}
    HuffmanNode<Priority, Data>* getRight() {return right_;}
    
    void setLeft(HuffmanNode<Priority, Data>* node) {left_ = node;}
    void setRight(HuffmanNode<Priority, Data>* node) {right_ = node;}
    
    friend ostream& operator<<(ostream& output, const HuffmanNode<Priority, Data>& rhs)
    {
        if (rhs.data_ == Data{})
        {
            output << "(P: " << rhs.priority_ << ")";
        }
        else
        {
            output << "(P: " << rhs.priority_ << ", D: " << rhs.data_ << ")";
        }
        return output;
    }
    
private:
    Priority priority_;
    Data data_;
    HuffmanNode<Priority, Data>* left_;
    HuffmanNode<Priority, Data>* right_;
};

#endif /* HuffmanNode_h */
