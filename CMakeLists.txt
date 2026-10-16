cmake_minimum_required(VERSION 3.16)

project(ExperimentLab VERSION 1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create the main executable
add_executable(experiment
    cpp/src/main.cpp
    cpp/src/experiment.cpp
)

# Tell the compiler where our header files are
target_include_directories(experiment PRIVATE
    ${PROJECT_SOURCE_DIR}/cpp/include
)