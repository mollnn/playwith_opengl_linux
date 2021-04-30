cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
project(learn_gl)

include_directories(include)
find_package(glfw3 REQUIRED)

macro(MY_ADD_EXECUTABLE PROGRAM)
    add_executable(${PROGRAM} src/${PROGRAM}/${PROGRAM}.cpp)
    target_link_libraries(${PROGRAM} -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lGL -lglut -lGLU -lGLEW -g -lSOIL)
endmacro()

MY_ADD_EXECUTABLE(01_triangle)
MY_ADD_EXECUTABLE(02_shader)
MY_ADD_EXECUTABLE(03_texture)
