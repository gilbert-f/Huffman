// input and output bitstream classes implementation

#ifndef BitStream_h
#define BitStream_h

#include <fstream>

using namespace std;

class InputBitStream
{
public:
    InputBitStream(string inputFileName)
    {
        bufferCount_ = 0;
        bufferBits_ = 0;
        
        inputStream_.open(inputFileName);
    }
    
    ~InputBitStream()
    {
        inputStream_.close();
    }
    
    unsigned int getBit()
    {
        if (bufferCount_ != 0)
        {
            unsigned int bit = (bufferBits_ & (1 << (bufferCount_ - 1))) >> (bufferCount_ - 1);
            bufferCount_-= 1;
            
            return bit;
        }
        else
        {
            bufferCount_ = 8;
            bufferBits_ = inputStream_.get();
            
            unsigned int bit = (bufferBits_ & (1 << (bufferCount_ - 1))) >> (bufferCount_ - 1);
            bufferCount_-= 1;
            
            return bit;
        }
    }
    
    unsigned char getByte()
    {
        bufferCount_ = 0;
        bufferBits_ = inputStream_.get();
        
        return bufferBits_;
    }
    
private:
    ifstream inputStream_;
    unsigned int bufferCount_;
    unsigned char bufferBits_;
};

class OutputBitStream
{
public:
    OutputBitStream(string outputFileName)
    {
        bufferCount_ = 0;
        bufferBits_ = 0;
        
        outputStream_.open(outputFileName);
    }
    
    ~OutputBitStream()
    {
        flush();
        outputStream_.close();
    }
    
    int putBit(unsigned int bit)
    {
        if (bit == 0 || bit == 1)
        {
            bufferCount_ += 1;
            bufferBits_ = (bufferBits_ << 1) + bit;
            
            if (bufferCount_ != 8)
            {
                return 1;
            }
            else
            {
                flush();
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    
    int putByte(unsigned char byte)
    {
        bufferCount_ = 8;
        bufferBits_ = byte;

        if (bufferCount_ == 8)
        {
            flush();
            return 0;
        }
        else
        {
            return 0;
        }
    }
    
    void flush()
    {
        if (bufferCount_ != 0)
        {
            outputStream_.put(bufferBits_ << (8 - bufferCount_));
            
            bufferCount_ = 0;
            bufferBits_ = 0;
        }
    }
    
private:
    ofstream outputStream_;
    unsigned int bufferCount_;
    unsigned char bufferBits_;
};

#endif /* BitStream_h */
