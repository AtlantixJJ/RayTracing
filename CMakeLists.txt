cmake_minimum_required(VERSION 2.8.7)
project(RayTracer)
set(ROOT_DIR .)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -O3 -Wall")

FIND_PACKAGE( OpenMP REQUIRED)  
if(OPENMP_FOUND)  
message("OPENMP FOUND")  
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")  
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")  
endif()  

include_directories(${PROJECT_SOURCE_DIR}/tools)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(externals/jsoncpp/include)

option(JSONCPP_WITH_TESTS OFF)
add_subdirectory(externals/jsoncpp)

message(${PROJECT_SOURCE_DIR})
add_subdirectory(src)