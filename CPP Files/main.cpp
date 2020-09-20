#include "../Header Files/winpatch.h"
#include <fstream>

int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("Execute with this structure: %s <program_path> <pattern_file_path>", get_program_name(argv[0]).c_str());
        return 100;
    }

    // after all arguments are ready to go.. we proceed to next tasks
    // read data from there

    // first things first, check if both files can be opened
    std::ifstream patternsFile, targetFile;
    targetFile   .open(argv[1], std::ifstream::binary|std::ifstream::out|std::ifstream::in); // we need to patch the file in the binary format
                                                                                                // so we use r+b mode to open it
    patternsFile .open(argv[2], std::ifstream::in); // we need to only read this file

    if(!patternsFile.is_open()) {
        std::cerr << "Pattern's file failed to open, please check permissions, path, etc.\n";
        return 201;
    }
    if(!targetFile.is_open()) {
        std::cerr << "Target Program's file failed to open, please check permissions, path, etc.\n";
        return 202;
    }



    return 0;
}
