cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
project(learn_gl)

include_directories(include)


find_package(glfw3 REQUIRED)
file(GLOB project_01_triangle src/glad.c src/01_triangle/01_triangle.cpp)
add_executable(01_triangle ${project_01_triangle})
file(GLOB project_02_shader src/glad.c src/02_shader/02_shader.cpp)
add_executable(02_shader ${project_02_shader})

target_link_libraries(01_triangle -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lGL -lglut -lGLU -lGLEW -g)
target_link_libraries(02_shader -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lGL -lglut -lGLU -lGLEW -g)
