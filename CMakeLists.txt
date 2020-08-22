cmake_minimum_required(VERSION 3.13)  
project(FluidSolver)               
set(CMAKE_CXX_STANDARD 17)    
find_package(OpenGL REQUIRED)
find_package(GLEW 2.0 REQUIRED)

include_directories(
        "ThirdParty/glfw-3.3.2/include"
        "ThirdParty/glad/include"
        "ThirdParty/mathGeolib/src"
        "ThirdParty/imgui"
        "ThirdParty/imgui/examples"
        "src"
        "src/modules"
        "src/components"
        )

file(GLOB source_files
        "src/*.h"
        "src/*.cpp"
        "src/modules/*.cpp"
        "src/components/*.cpp"
        "ThirdParty/glad/src/*.c"
        "ThirdParty/imgui/*.cpp"
        "ThirdParty/imgui/examples/imgui_impl_glfw.cpp"
        "ThirdParty/imgui/examples/imgui_impl_opengl3.cpp"
)

add_library(glew STATIC IMPORTED GLOBAL)

set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ThirdParty/glew-2.1.0/lib/libGLEW.a )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ThirdParty/glfw-3.3.2/)
add_subdirectory(ThirdParty/mathGeolib/)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(FluidSolver ${source_files})
target_link_libraries(FluidSolver glfw)
target_link_libraries(FluidSolver OpenGL::GL)
target_link_libraries(FluidSolver GLEW::GLEW)

set (CMAKE_CXX_FLAGS "-g")
