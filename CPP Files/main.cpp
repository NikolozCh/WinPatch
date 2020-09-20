#include "../Header Files/winpatch.h"


int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("Execute with this structure: %s <program_path> <pattern_file_path>", get_program_name(argv[0]).c_str());
        return 1;
    }
    std::cout << "Hello, World! Found Parameters: "<< argc << std::endl;
    return 0;
}