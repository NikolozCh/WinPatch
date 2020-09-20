//
// Created by Nikoloz on 20-Sep-20.
//

#include "../Header Files/winpatch.h"

// MISC Function declarations
std::string get_program_name(std::string path) {
    std::string program_name;
    int size_of_path = path.size();
    for(int i = size_of_path - 1; i >= 0; i--) {
        if (path[i] != '\\')
            program_name.push_back(path[i]);
        else
            return std::string(program_name.rbegin(), program_name.rend()); // this method is reversing the strings
    }
    return path; // if path doesn't contain '\' symbol in it
                 // we just return the name, it means only the .exe path is provided
}
// ---------------------------------------