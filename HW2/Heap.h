// heap class implementation

#ifndef Heap_h
#define Heap_h

#include "HuffmanNode.h"

#include <vector>

template<typename Priority, typename Data, typename Item, typename Compare>
class Heap
{
public:
    Heap(Compare& compare): compare_(compare) {}
    
    int getSize() {return items_.size();}
    bool is_empty() {return (getSize() == 0);}
    
    Item* peek()
    {
        if (is_empty())
        {
            return nullptr;
        }
        else
        {
            return items_[0];
        }
    }
    
    void push(Priority priority, Data data)
    {
        items_.push_back(new HuffmanNode<Priority, Data>(priority, data));
        percolateUp();
    }
    
    void push(Item* item)
    {
        items_.push_back(item);
        percolateUp();
    }
    
    Item* pop()
    {
        if (is_empty())
        {
            return nullptr;
        }
        else
        {
            Item* item = peek();
            
            items_[0] = items_[getSize() - 1];
            items_.pop_back();
            
            percolateDown(0);
            
            return item;
        }
    }
    
    void dump()
    {
        int index = 0;
        while (index < getSize())
        {
            cerr << * items_[index] << endl;
            index++;
        }
    }
    
private:
    vector<Item*> items_;
    Compare compare_;
    
    int parent(int index) {return ((index - 1) / 2);}
    int leftChild(int index) {return (2 * index + 1);}
    int rightChild(int index) {return (2 * index + 2);}
    
    void percolateUp();
    void percolateDown(int index);
    
    void swap(int source, int destination);
};

template<typename Priority, typename Data, typename Item, typename Compare>
void Heap<Priority, Data, Item, Compare>::percolateUp()
{
    int index = getSize() - 1;
    
    while (index > 0 &&
           compare_(items_[index], items_[parent(index)]))
    {
        swap(index, parent(index));
        index = parent(index);
    }
}

// reference: https://www.geeksforgeeks.org/binary-heap/
// percolate down function to fix the heap property
template<typename Priority, typename Data, typename Item, typename Compare>
void Heap<Priority, Data, Item, Compare>::percolateDown(int index)
{
    int smallestIndex = index;
    int leftIndex = leftChild(index);
    int rightIndex = rightChild(index);
    
    if (leftIndex < getSize() &&
        compare_(items_[leftIndex], items_[index]))
    {
        smallestIndex = leftIndex;
    }
    if (rightIndex < getSize() &&
        compare_(items_[rightIndex], items_[smallestIndex]))
    {
        smallestIndex = rightIndex;
    }
    if (smallestIndex != index)
    {
        swap(index, smallestIndex);
        percolateDown(smallestIndex);
    }
}

template<typename Priority, typename Data, typename Item, typename Compare>
void Heap<Priority, Data, Item, Compare>::swap(int source, int destination)
{
    Item* item = items_[source];
    items_[source] = items_[destination];
    items_[destination] = item;
}

// reference: http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
// struct to compare the priorities of two HuffmanNodes
template<typename Priority, typename Data>
struct CompareHuffmanNode: public binary_function<HuffmanNode<Priority, Data>*, HuffmanNode<Priority, Data>*, bool>
{
    bool operator()(const HuffmanNode<Priority, Data>* lhs, const HuffmanNode<Priority, Data>* rhs)
    {
        return lhs->getPriority() < rhs->getPriority();
    }
};

#endif /* Heap_h */
