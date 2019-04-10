cmake_minimum_required(VERSION 3.6)   # CMake version check
project(GoFish)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++ 98 standard

set(SOURCE_FILES card.cpp card_demo.cpp deck.cpp player.cpp)            # Add main.cpp file of project root directory as source file
add_executable(GoFish ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable