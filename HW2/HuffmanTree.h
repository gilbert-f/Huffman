// huffman tree class implementation

#ifndef HuffmanTree_h
#define HuffmanTree_h

#include "BitStream.h"
#include "Heap.h"

#include <iostream>

class HuffmanTree
{
public:
    HuffmanTree(unsigned int frequencies[], unsigned int totalNumberOfCharacters)
    {
        totalNumberOfCharacters_ = totalNumberOfCharacters;
        
        CompareHuffmanNode<unsigned int, unsigned char> compare;
        Heap<unsigned int, unsigned char, HuffmanNode<unsigned int, unsigned char>, CompareHuffmanNode<unsigned int, unsigned char>> heap(compare);
        
        int index = 0;
        while (index < UCHAR_MAX + 1)
        {
            if (frequencies[index] != 0)
            {
                heap.push(new HuffmanNode<unsigned int, unsigned char>(frequencies[index], index));
            }
            index++;
        }
        
        while (heap.getSize() >= 2)
        {
            HuffmanNode<unsigned int, unsigned char>* left = heap.pop();
            HuffmanNode<unsigned int, unsigned char>* right = heap.pop();
            
            HuffmanNode<unsigned int, unsigned char>* node = new HuffmanNode<unsigned int, unsigned char>(left->getPriority() + right->getPriority());
            node->setLeft(left);
            node->setRight(right);
            
            heap.push(node);
        }
        root_ = heap.pop();
    }
    
    HuffmanTree(InputBitStream& inputBitStream)
    {
        int index = 0;
        while (index < UCHAR_MAX + 1)
        {
            unsigned int codeLength = inputBitStream.getByte();
            unsigned long long code = 0;
            
            if (codeLength != 0)
            {
                int i = 0;
                while (i < codeLength)
                {
                    code = (code << 1) + inputBitStream.getBit();
                    i++;
                }
                root_ = buildHuffmanTree(root_, (unsigned char)index, codeLength, code);
            }
            index++;
        }
        
        totalNumberOfCharacters_ = 0;
        
        int ii = 0;
        while (ii <= 3)
        {
            totalNumberOfCharacters_ = totalNumberOfCharacters_ + (inputBitStream.getByte() << (ii * 8));
            ii++;
        }
    }
    
    HuffmanNode<unsigned int, unsigned char>* getRoot() {return root_;};
    
    int puff(InputBitStream& inputBitStream, string outputFileName)
    {
        ofstream outputStream;
        outputStream.open(outputFileName);
        
        if (outputStream.is_open())
        {
            int index = 0;
            while (index < totalNumberOfCharacters_)
            {
                puffHelper(root_, inputBitStream, outputStream);
                index++;
            }
            outputStream.close();
            return EXIT_SUCCESS;
        }
        else
        {
            outputStream.close();
            cerr << "Cannot open file." << endl;
            return EXIT_FAILURE;
        }
    }
    
    //  Credits:
    //      dump - https://courses.cs.washington.edu/courses/cse143/11wi/lectures/02-18/19-binary-tree.pdf
    //  output the structure of the tree
    void dump()
    {
        dumpHelper(root_, 0);
    }
    
private:
    HuffmanNode<unsigned int, unsigned char>* root_;
    unsigned int totalNumberOfCharacters_;
    
    HuffmanNode<unsigned int, unsigned char>* buildHuffmanTree(HuffmanNode<unsigned int, unsigned char>* current, unsigned char character, unsigned int codeLength, unsigned long long code)
    {
        if (codeLength != 0)
        {
            if (!current)
            {
                current = new HuffmanNode<unsigned int, unsigned char>();
            }
            
            unsigned long long bit = (code & ((1 << codeLength) - 1)) >> (codeLength - 1);
            
            if (bit == 1)
            {
                current->setRight(buildHuffmanTree(current->getRight(), character, codeLength - 1, code));
            }
            else
            {
                current->setLeft(buildHuffmanTree(current->getLeft(), character, codeLength - 1, code));
            }
            return current;
        }
        else
        {
            current = new HuffmanNode<unsigned int, unsigned char>();
            current->setData(character);
            return current;
        }
    }
    
    void puffHelper(HuffmanNode<unsigned int, unsigned char>* current, InputBitStream& inputBitStream, ofstream& outputStream)
    {
        if (current)
        {
            if (current->getLeft() && current->getRight())
            {
                unsigned int bit = inputBitStream.getBit();
                if (bit == 1)
                {
                    puffHelper(current->getRight(), inputBitStream, outputStream);
                }
                else
                {
                    puffHelper(current->getLeft(), inputBitStream, outputStream);
                }
            }
            else
            {
                outputStream.put((unsigned char)current->getData());
            }
        }
    }
    
    //  helper function to output the structure of the tree
    void dumpHelper(HuffmanNode<unsigned int, unsigned char>* current, int depth)
    {
        if (current)
        {
            if (current->getRight())
            {
                dumpHelper(current->getRight(), depth + 1);
            }
            
            for (int i = 0; i < depth; i++)
            {
                std::cerr << "+-------";
            }
            
            if (current->getData() == '\n')
            {
                cerr << "(P: " << current->getPriority() << ", D: " << "newline" << ")" << endl;
            }
            else if (isspace(current->getData()))
            {
                cerr << "(P: " << current->getPriority() << ", D: " << "space" << ")" << endl;
            }
            else
            {
                cerr << * current << endl;
            }
            
            if (current->getLeft())
            {
                dumpHelper(current->getLeft(), depth + 1);
            }
        }
    }
};

#endif /* HuffmanTree_h */
