// frequency table class implementation

#ifndef FrequencyTable_h
#define FrequencyTable_h

#include <string>

using namespace std;

class FrequencyTable
{
public:
    FrequencyTable(string inputFileName)
    {
        totalNumberOfCharacters_ = 0;
        
        ifstream inputStream;
        inputStream.open(inputFileName);
        
        if (inputStream.is_open())
        {
            unsigned char character = inputStream.get();
            
            while (!inputStream.eof())
            {
                frequencies_[character] += 1;
                totalNumberOfCharacters_ += 1;
                character = inputStream.get();
            }
            
            inputStream.close();
        }
        else
        {
            inputStream.close();
            cerr << "Cannot open file." << endl;
        }
    }
    
    unsigned int * getFrequencies() {return frequencies_;}
    unsigned int getTotalNumberOfCharacters() {return totalNumberOfCharacters_;}
    
    void dump()
    {
        int i = 0;
        while (i < UCHAR_MAX + 1)
        {
            if (frequencies_[i] != 0)
            {
                if ((unsigned char)i == '\n')
                {
                    cerr << "character: " << "newline" << " \t hex: " << hex << (unsigned int)i << " \t \t printable: " << (bool)isprint(i) << " \t \t frequency: " << dec << frequencies_[i] << endl;
                }
                else if (isspace((unsigned char)i))
                {
                    cerr << "character: " << "space" << " \t hex: " << hex << (unsigned int)i << " \t \t printable: " << (bool)isprint(i) << " \t \t frequency: " << dec << frequencies_[i] << endl;
                }
                else
                {
                    cerr << "character: " << (unsigned char)i << " \t \t hex: " << hex << (unsigned int)i << " \t \t printable: " << (bool)isprint(i) << " \t \t frequency: " << dec << frequencies_[i] << endl;
                }
            }
            i++;
        }
    }
    
private:
    unsigned int frequencies_[UCHAR_MAX + 1] = {0};
    unsigned int totalNumberOfCharacters_;
};

#endif /* FrequencyTable_h */
