cmake_minimum_required(VERSION 3.28)
project(Kraken)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

set(SRC_DIR "src")
file(GLOB SRCS
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.h"
)

message(STATUS "SRCS: ${SRCS}")

add_library(Kraken STATIC ${SRCS})
target_link_libraries(Kraken GLEW::GLEW glfw OpenGL::GL glm::glm assimp::assimp)

set_target_properties(Kraken PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)