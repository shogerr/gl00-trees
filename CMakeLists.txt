cmake_minimum_required(VERSION 3.15)
project(trees)
set(CMAKE_CXX_STANDARD 20)

find_package(glm CONFIG REQUIRED)
find_package(gl00 CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

#  Main
#
add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/glad)
target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
  )

target_link_libraries(${PROJECT_NAME} glm)

#  Tests
#
add_executable(test_cylinder
    tests/test_cylinder.cpp
    tests/test_signal.cpp
    tests/cylinder_sketch.cpp
    )

target_compile_options(test_cylinder
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
  )

target_link_libraries(test_cylinder glm glfw glad gl00::gl00 OpenGL::GL)
