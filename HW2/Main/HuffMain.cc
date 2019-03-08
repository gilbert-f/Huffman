// driver file for huff

#include "CodingTable.h"
#include "FrequencyTable.h"
#include "HuffmanTree.h"

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        string inputFileName = argv[1];
        if (inputFileName.substr(inputFileName.length() - 4, inputFileName.length() - 1) == ".txt")
        {
            ifstream inputStream;
            inputStream.open(inputFileName);
            
            if (inputStream.is_open())
            {
                inputStream.close();
                
                FrequencyTable frequencyTable(inputFileName);
                frequencyTable.dump();
                
                HuffmanTree huffmanTree(frequencyTable.getFrequencies(), frequencyTable.getTotalNumberOfCharacters());
                huffmanTree.dump();
                
                CodingTable codingTable(huffmanTree.getRoot());
                codingTable.dump();
                
                return codingTable.huff(inputFileName, frequencyTable.getTotalNumberOfCharacters());
            }
            else
            {
                inputStream.close();
                cerr << "Cannot open file." << endl;
                return EXIT_FAILURE;
            }

        }
        else
        {
            cerr << "File is not a .txt file." << endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        cerr << "Invalid arguments." << endl;
        return EXIT_FAILURE;
    }
}
