//
// Created by Nikoloz on 20-Sep-20.
//

#include "../Header Files/winpatch.h"

// MISC Function declarations
std::string get_program_name(std::string path)
{
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

// adds _patched to original file path
std::string getPatchedFileNameFromOriginal(std::string fileName)
{
    std::string extension, newName; // we store file extension into extension var
                                    // we store whole new path in newName

    for(int i = fileName.size() - 1; i >= 0; i--)
    {
        if(fileName[i] != '.')
        {
            extension.push_back(fileName[i]);
        }
        else
        {
            newName = fileName.substr(0, i);
            break;
        }
    }
    extension = std::string(extension.rbegin(), extension.rend()); // we reverse extension here

    newName.append("_patched.");
    newName.append(extension);

    return newName;
}

// ---------------------------------------

// Pattern related -----------------------

bool validatePatternLine(std::string line)
{
    if(line.size() >= 12) // line must contain at least 12 chars to be valid
    {
        if(line.compare(2, 8, "original") == 0 || line.compare(2, 8, "replaced") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// ---------------------------------------