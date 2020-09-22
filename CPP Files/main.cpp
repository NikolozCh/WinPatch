#include "../Header Files/winpatch.h"
#include <fstream>
#include <vector>


// we use these macros to convert "FF" from a string into the unsigned char
#define INRANGE(x,a,b)  (x >= a && x <= b)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
// getByte function returns that


int main(int argc, char* argv[])
{

    if(argc != 3)
    {
        printf("Execute with this structure: %s <program_path> <pattern_file_path>", get_program_name(argv[0]).c_str());
        return 100;
    }

    // after all arguments are ready to go.. we proceed to next tasks
    // read data from there

    // first things first, check if both files can be opened -------------------------------------------------
    std::ifstream patternsFile;
    FILE* targetFile;                                                                          // we need to patch the file in the binary format
    targetFile = fopen(argv[1], "r+b");                                        // so we use r+b mode to open it

    patternsFile .open(argv[2], std::ifstream::in);                                        // we need to only read this file

    if(!patternsFile.is_open())
    {
        std::cerr << "Pattern's file failed to open, please check permissions, path, etc.\n";
        return 201;
    }
    if(targetFile == NULL)
    {
        std::cerr << "Target Program's file failed to open, please check permissions, path, etc.\n";
        return 202;
    }
    // checks are done here -------------------------------- continuing to read patterns ----------------------

    std::string patternLine;                // reading lines from file are stored in this variable
    std::vector<std::string> validPatterns; // we store patterns here, next we will manipulate with them

    int itemIterator = 0;
    while(std::getline(patternsFile, patternLine)) // we loop throughout the text file and reading lines
    {
        if(validatePatternLine(patternLine))
        {
            if(!validPatterns.empty())
            {
                // we need to check that after "original" there should be "replaced" and after "replaced" there should be "original"
                if(validPatterns[itemIterator].compare(2, 8, patternLine.substr(2, 8)) == 0) { std::cerr << "\"original\" should be placed before \"replaced\" and \"replaced\" should be placed after \"original\".\n"; return 301; }
                else
                {
                    itemIterator++;
                    validPatterns.push_back(patternLine);
                }
            }
            else
            {
                if(patternLine.compare(2,8,"original") == 0)
                {
                    validPatterns.push_back(patternLine);
                }
                else
                {
                    std::cerr << R"(First pattern tag must be "original" and not "replaced")";
                    return 301;
                }
            }
        }
        else if(patternLine.size() <= 12) // line must contain at least 12 chars to be valid
        {
            // just pass this, it is a newline
        }
        else
        {
            std::cerr << "Patterns are in incorrect form... Please take a look at them again.\n";
            return 301;
        }
    }

    // if user provided only one pattern or the pattern's file is empty
    if(validPatterns.size() <= 1 && validPatterns.size() % 2 != 0) { std::cerr << "Not enough patterns are provided..\nExiting..."; return 301; }

    std::vector<std::string> original_patterns_bytes;
    std::vector<std::string> replaced_patterns_bytes;

    for(int i = 0; i < validPatterns.size(); i += 2)
    {
        // we are pushing back the parsed pattern from {"original":"FF FF FF FF FF"} we are adding only "FF FF FF FF FF" as a string in std::vector
        // same goes with the replaced patterns
        // so I have separated both of them from validPatterns std::vector
        original_patterns_bytes.push_back(validPatterns[i]    .substr(validPatterns[i]    .find("\":\"") + 3, validPatterns[i]    .size() - validPatterns[i]    .find("\":\"") - 5));
        replaced_patterns_bytes.push_back(validPatterns[i + 1].substr(validPatterns[i + 1].find("\":\"") + 3, validPatterns[i + 1].size() - validPatterns[i + 1].find("\":\"") - 5));
    }

    // Patterns check done here ----------------------------- We will read target file now --------------------


    std::string stringFileBuffer, stringFileBuffer_copy;

    // we are storing the whole file in the vector to get this file in buffer
    while(!feof(targetFile))
    {
        unsigned char byteFromFile;
        byteFromFile = fgetc(targetFile);
        char test[4]; sprintf(test, "%02X ", byteFromFile);
        stringFileBuffer.append(test);
    }

    stringFileBuffer_copy = stringFileBuffer; // we need to change from actual file buffer
                                              // if we change in actual buffer, other patterns can be found then and it will corrupt the file


    for(int i = 0; i < original_patterns_bytes.size(); i++) // we will check all the patterns
    {
        for(int j = 0; j < stringFileBuffer.size(); j += 3 ) // "FF BB CC AA" we iterating through these hex values stored in stringFileBuffer
        {

            if(stringFileBuffer.compare(j, original_patterns_bytes[i].size(), original_patterns_bytes[i]) == 0)
            {
                // we found related pattern, so we change it in copied buffer
                stringFileBuffer_copy.replace(j, replaced_patterns_bytes[i].size(), replaced_patterns_bytes[i]);
            }
        }
    }

    stringFileBuffer_copy.resize(stringFileBuffer_copy.size() - 4); // we remove last trash characters

    std::string new_file = getPatchedFileNameFromOriginal(argv[1]); // we add "_patched" suffix to patched file
                                                                    // that file is generating by this program
                                                                    // original program is staying how it is
                                                                    // new_file holds the new path of the file which will be generated after executing


    FILE *nf; // nf -> new file; we use FILE pointer because we need to use std::fwrite function
    nf = std::fopen(new_file.c_str(), "w+b");

    for(int i = 0; i < stringFileBuffer_copy.size(); i+=3)
    {
        unsigned char newByte = getByte(stringFileBuffer_copy.substr(i, 2));
        std::fwrite(&newByte, sizeof(unsigned char), 1, nf);
    }
    std::cout << "Finished";

    // --------------------------------------------------------------------------------------------------------


    std::cin.get();
    return 0;
}
