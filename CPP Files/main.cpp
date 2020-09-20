#include "../Header Files/winpatch.h"
#include <fstream>
#include <vector>

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
    std::ifstream patternsFile, targetFile;
    targetFile   .open(argv[1], std::ifstream::binary|std::ifstream::out|std::ifstream::in); // we need to patch the file in the binary format
                                                                                                // so we use r+b mode to open it
    patternsFile .open(argv[2], std::ifstream::in); // we need to only read this file

    if(!patternsFile.is_open())
    {
        std::cerr << "Pattern's file failed to open, please check permissions, path, etc.\n";
        return 201;
    }
    if(!targetFile.is_open())
    {
        std::cerr << "Target Program's file failed to open, please check permissions, path, etc.\n";
        return 202;
    }
    // checks are done here -------------------------------- continuing to read patterns ----------------------

    std::string patternLine;                // reading lines from file are stored in this variable
    std::vector<std::string> validPatterns; // we store patterns here, next we will manipulate with them

    while(std::getline(patternsFile, patternLine)) // we loop throughout the text file and reading lines
    {
        if(validatePatternLine(patternLine))
        {
            validPatterns.push_back(patternLine);
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



    // ---------------------------------------------------------------------------------------------------------



    std::cin.get();
    return 0;
}
