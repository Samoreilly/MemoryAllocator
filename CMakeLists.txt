cmake_minimum_required(VERSION 4.1)
project(MemoryAllocator)

add_executable(
  MemoryAllocator main.cpp
                  alloc.cpp
                  allocutil.cpp
) 
