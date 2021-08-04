cmake_minimum_required(VERSION 3.0.0)
project(DiamondSquare VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp src/terrain.cpp include/shader.h include/camera.h include/mesh.h src/mesh.cpp)

find_package(glfw3 3.3. REQUIRED)
add_executable(DiamondSquare ${SOURCE_FILES} src/glad.c)
target_include_directories(DiamondSquare PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DiamondSquare glfw)