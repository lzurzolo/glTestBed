cmake_minimum_required(VERSION 3.0.0)
project(glTestBed)

include_directories(src/*/public include/)
file(GLOB SOURCES "src/private/*.cpp" "lib/*.c")

add_executable(glTestBed ${SOURCES})

target_compile_options(glTestBed PRIVATE -g)
target_link_libraries(glTestBed PRIVATE -g -lglfw -ldl)

