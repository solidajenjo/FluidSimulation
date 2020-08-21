cmake_minimum_required(VERSION 3.13)  
project(FluidSolver)               
set(CMAKE_CXX_STANDARD 17)           
include_directories(
        "./ThirdParty/glfw-3.3.2/include"
        "./ThirdParty/glad/include"
        "./ThirdParty/mathGeolib/src"
        "./src"
        "./src/modules"
        )

file(GLOB source_files
        "src/*.h"
        "src/*.cpp"
        "src/modules/*.cpp"
        "ThirdParty/glad/src/*.c"
)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ThirdParty/glfw-3.3.2/)
add_subdirectory(ThirdParty/mathGeolib/)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(FluidSolver ${source_files})
target_link_libraries(FluidSolver glfw)
target_link_libraries(FluidSolver OpenGL::GL)

set (CMAKE_CXX_FLAGS "-g -lGL")
