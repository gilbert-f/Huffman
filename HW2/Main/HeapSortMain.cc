// driver file to test the heap sort property of the heap

#include "Heap.h"

using namespace std;

int main()
{
    CompareHuffmanNode<int, char> compare;
    Heap<int, char, HuffmanNode<int, char>, CompareHuffmanNode<int, char>> heap(compare);
    
    cerr << "Initially, is heap empty?: " << heap.is_empty() << endl;
    
    cerr << endl;
    
    cerr << "Adding items to queue." << endl;
    
    heap.push(7000, 'a');
    heap.push(6000, 'a');
    heap.push(5000, 'b');
    heap.push(1, 'c');
    heap.push(2, 'z');
    heap.push(0, 'd');
    heap.push(999, 'g');
    heap.push(0, 'e');
    
    cerr << "After adding, is heap empty?: " << heap.is_empty() << endl;
    
    cerr << endl;
    
    cerr << "What is the item with the smallest priority in the heap?: " << * heap.peek() << endl;
    
    cerr << endl;
    
    cerr << "Printing the array representation of the heap: " << endl;
    heap.dump();
    
    cerr << endl;
    
    cerr << "Performing heap sort (output should be in sorted order): " << endl;
    while (!heap.is_empty())
    {
        cerr << "Output: " << endl;
        cerr << * heap.pop() << endl;
        
        
        cerr << "Heap structure: " << endl;
        heap.dump();
        cerr << endl;
    }
    
    return 0;
}
