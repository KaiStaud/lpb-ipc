cmake_minimum_required(VERSION 3.22)
project(ShmemEndpoint)

add_library(libshmem doubler.cpp)
target_link_libraries(libshmem rt)

add_executable(shmem_endpoint main.cpp)
target_link_libraries(shmem_endpoint libshmem rt)

set_target_properties(libshmem PROPERTIES PUBLIC_HEADER doubler.h)

install(TARGETS libshmem
        PUBLIC_HEADER
          DESTINATION /usr/local/include/shmem
)