// In this file we define the prototypes of the functions
// later, we will use those functions into the main.cpp
#ifndef WINPATCH_WINPATCH_H
#define WINPATCH_WINPATCH_H

#include <iostream>
#include <string>


// MISC Functions ------------------------

std::string get_program_name(std::string path); // Removes the path and leaves just the program name (exe name)

// ---------------------------------------

// Pattern related -----------------------

bool validatePatternLine(std::string line);

// ---------------------------------------

#endif //WINPATCH_WINPATCH_H
