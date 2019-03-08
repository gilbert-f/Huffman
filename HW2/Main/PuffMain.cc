// driver file for puff

#include "HuffmanTree.h"

#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        string inputFileName = argv[1];
        if (inputFileName.substr(inputFileName.length() - 5, inputFileName.length() - 1) == ".huff")
        {
            fstream inputStream;
            inputStream.open(inputFileName);
            
            if (inputStream.is_open())
            {
                inputStream.close();
                
                InputBitStream inputBitStream(inputFileName);
                
                HuffmanTree huffmanTree(inputBitStream);
                huffmanTree.dump();
                
                return huffmanTree.puff(inputBitStream, (inputFileName.substr(0, inputFileName.length() - 5) + ".puff"));
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
            cerr << "File is not a .huff file." << endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        cerr << "Invalid arguments." << endl;
        return EXIT_FAILURE;
    }
}
