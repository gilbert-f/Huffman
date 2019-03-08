// coding table class implementation

#ifndef CodingTable_h
#define CodingTable_h

#include "BitStream.h"
#include "HuffmanNode.h"

class CodingTable
{
public:
    CodingTable(HuffmanNode<unsigned int, unsigned char>* root)
    {
        buildCodingTable(root, 0, 0);
    }
    
    unsigned int * getCodeLengths() {return codeLengths_;}
    unsigned long long * getCodes() {return codes_;}
    
    int huff(string inputFileName, unsigned int totalNumberOfCharacters)
    {
        OutputBitStream outputBitStream(inputFileName + ".huff");
        
        int index = 0;
        while (index < UCHAR_MAX + 1)
        {
            outputBitStream.putByte((unsigned char)codeLengths_[index]);
            
            if (codeLengths_[index] != 0)
            {
                int ii = 1;
                while (ii < codeLengths_[index] + 1)
                {
                    outputBitStream.putBit(((codes_[index] & (1 << (codeLengths_[index] - (unsigned int)ii))) >> (codeLengths_[index] - (unsigned int)ii)) & 1);
                    ii++;
                }
                outputBitStream.flush();
            }
            index++;
        }
        
        int i = 0;
        while (i <= 3)
        {
            outputBitStream.putByte((unsigned char)totalNumberOfCharacters);
            totalNumberOfCharacters = totalNumberOfCharacters >> 8;
            i++;
        }
        
        ifstream inputStream;
        inputStream.open(inputFileName);
        
        if (!inputStream.is_open())
        {
            inputStream.close();
            cerr << "Cannot open file." << endl;
            return EXIT_FAILURE;
        }
        else
        {
            unsigned char character = inputStream.get();
            
            while (!inputStream.eof())
            {
                int ii = 1;
                while (ii < (int)codeLengths_[character] + 1)
                {
                    outputBitStream.putBit(((codes_[character] & (1 << (codeLengths_[character] - (unsigned int)ii))) >> (codeLengths_[character] - (unsigned int)ii)) & 1);
                    ii++;
                }
                character = inputStream.get();
            }
            
            inputStream.close();
            return EXIT_SUCCESS;
        }
    }
    
    void dump()
    {
        int index = 0;
        while (index < UCHAR_MAX + 1)
        {
            if (codeLengths_[index] != 0)
            {
                bitset<64> code(codes_[index]);
                
                if ((unsigned char)index == '\n')
                {
                    cerr << "character: " << "newline" << "\t code: " << code << " \t length: " << codeLengths_[index] << endl;
                }
                else if (isspace((unsigned char)index))
                {
                    cerr << "character: " << "space" << "\t code: " << code << " \t length: " << codeLengths_[index] << endl;
                }
                else
                {
                    cerr << "character: " << (unsigned char)index << "\t \t code: " << code << " \t length: " << codeLengths_[index] <<  endl;
                }
            }
            index++;
        }
    }
    
private:
    unsigned int codeLengths_[UCHAR_MAX + 1] = {0};
    unsigned long long codes_[UCHAR_MAX + 1] = {0};
    
    void buildCodingTable(HuffmanNode<unsigned int, unsigned char>* current, unsigned int depth, unsigned long long code)
    {
        if (current)
        {
            if (current->getLeft() && current->getRight())
            {
                code = code << 1;
                buildCodingTable(current->getLeft(), depth + 1, code);
                buildCodingTable(current->getRight(), depth + 1, code + 1);
            }
            else
            {
                codeLengths_[current->getData()] = depth;
                codes_[current->getData()] = code;
            }
        }
    }
};

#endif /* CodingTable_h */
