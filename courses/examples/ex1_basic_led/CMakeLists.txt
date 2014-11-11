cmake_minimum_required(VERSION 2.8.11)

project(ex1_basic_led)


include_directories(
    J:/Embedded classes/Examples/ex1_basic_led/
)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the C sources
set ( C_SRCS
    ex1_basic_led.c
    startup_sam4s.c
    system_sam4s.c
)

set_source_files_properties(
    ${C_SRCS} PROPERTIES COMPILE_FLAGS
    " -g -O0 -Wall")

add_executable(ex1_basic_led ${CXX_SRCS} ${C_SRCS})

