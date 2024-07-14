cmake_minimum_required(VERSION 3.28)
project(Sandbox)

set(Kraken_DIR "../Kraken")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(SRCS src/main.cpp)
add_executable(Sandbox ${SRCS})

target_include_directories(Sandbox PRIVATE ${Kraken_DIR}/src)
target_link_directories(Sandbox PRIVATE ${Kraken_DIR}/build)

target_link_libraries(Sandbox GLEW::GLEW glfw OpenGL::GL glm::glm assimp::assimp Kraken)