cmake_minimum_required(VERSION 3.0.0)
project(DiamondSquare VERSION 0.1.0)

set(SOURCE_FILES src/main.cpp include/shader.h include/camera.h include/mesh.h src/mesh.cpp)

add_executable(DiamondSquare ${SOURCE_FILES} src/glad.c)
target_include_directories(DiamondSquare PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DiamondSquare C:/lib/MinGW/glfw/lib/libglfw3.a )

add_executable(Diamond src/diamond.cpp src/terrain.cpp)
target_include_directories(Diamond PRIVATE ${PROJECT_SOURCE_DIR}/include)
