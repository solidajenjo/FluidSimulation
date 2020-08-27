cmake_minimum_required(VERSION 3.12)  
project(FluidSolver)               
set(CMAKE_CXX_STANDARD 17)    

add_subdirectory(ThirdParty/glfw-3.3.2/)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(
		"ThirdParty/glfw-3.3.2/include"
		"ThirdParty/glad/include"
		"ThirdParty/mathGeolib/src"
		"ThirdParty/imgui"
		"ThirdParty/imgui/examples"
		"ThirdParty/OBJ-Loader/Source"
		"ThirdParty/debug"
		"src"
		"src/modules"
		"src/components"
		"src/physics"
		)

file(GLOB source_files
		"src/*.cpp"
		"src/modules/*.cpp"
		"src/components/*.cpp"
		"src/physics/*.cpp"
		"ThirdParty/glad/src/*.c"
		"ThirdParty/imgui/*.cpp"
		"ThirdParty/imgui/examples/imgui_impl_glfw.cpp"
		"ThirdParty/imgui/examples/imgui_impl_opengl3.cpp"
)
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(FluidSolver ${source_files})

find_package(OpenGL REQUIRED)

if (!WINDOWS)
	find_package(GLEW 2.0 REQUIRED)


#	add_library(glew STATIC IMPORTED GLOBAL)

#	set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ThirdParty/glew-2.1.0/lib/libGLEW.a )

	add_library(mathGeolib STATIC IMPORTED GLOBAL)

	set_target_properties(mathGeolib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ThirdParty/mathGeolib/lib/libMathGeoLib.a )

#	target_link_libraries(FluidSolver GLEW::GLEW)

else()

	add_library(mathGeolib STATIC IMPORTED GLOBAL)

	if (CMAKE_BUILD_TYPE EQUAL Release)
		set_target_properties(mathGeolib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ThirdParty/mathGeolib/lib/Release/MathGeoLib.lib )
	else()
		set_target_properties(mathGeolib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ThirdParty/mathGeolib/lib/Debug/MathGeoLib.lib )
	endif()


	
endif()

	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



	target_link_libraries(FluidSolver glfw)
	target_link_libraries(FluidSolver OpenGL::GL)
	target_link_libraries(FluidSolver mathGeolib)

if (!WINDOWS)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
