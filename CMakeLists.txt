cmake_minimum_required(VERSION 3.17)
project(WinPatch)

set(CMAKE_CXX_STANDARD 20)

add_executable(WinPatch "CPP Files/main.cpp" "Header Files/winpatch.h" "CPP Files/winpatch.cpp")