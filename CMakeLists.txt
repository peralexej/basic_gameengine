cmake_minimum_required(VERSION 3.10)

# Project name
project(YourProjectName)

# Add your source files here, for example main.cpp
set(SOURCE_FILES main.cpp)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2 and SDL2_image packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2-image CONFIG REQUIRED)

# Create your executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link the required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image)
