cmake_minimum_required(VERSION 3.0)
project(ParallelNBodySimulationMPI)

set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

add_executable(parallel_nbody src/main.c src/body.c src/file_io.c src/timer.c)


target_link_libraries(parallel_nbody ${MPI_LIBRARIES} m)
