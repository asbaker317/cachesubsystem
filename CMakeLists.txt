cmake_minimum_required(VERSION 3.7)
project(cachesubsystem2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cpu.c
        cpu.h
        l1-controller.c
        l1-controller.h
        l1-data-cache.c
        l1-instruction-cache.c
        l1-write-buffer.c
        l2-controller.c
        l2-write-buffer.c
        l2_controller.h
        main.c
        memory.c
        memory.h
        queue.c
        queue.h
        victim-cache.c)

add_executable(cachesubsystem2 ${SOURCE_FILES})