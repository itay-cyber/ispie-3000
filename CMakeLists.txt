cmake_minimum_required(VERSION 3.10)
project(i_spie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

set(PSAPI_VERSION 1)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_compile_options(${PROJECT_NAME} PRIVATE -DPSAPI_VERSION=${PSAPI_VERSION})
# Link PSAPI library
target_link_libraries(${PROJECT_NAME} Psapi)