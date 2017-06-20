include_directories(.)
set(EXECUTABLE_OUTPUT_PATH ${ROOT_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${ROOT_DIR}/lib)

aux_source_directory(common COMMON_SRCS)
add_library(common ${COMMON_SRCS})
target_link_libraries(common jsoncpp_lib_static)

aux_source_directory(math MATH_SRCS)
add_library(math ${MATH_SRCS})

aux_source_directory(light LIGHT_SRCS)
add_library(light ${LIGHT_SRCS})

aux_source_directory(object OBJECT_SRCS)
add_library(object ${OBJECT_SRCS})
target_link_libraries(object common math )

aux_source_directory(scene SCENE_SRCS)
add_library(scene ${SCENE_SRCS})
target_link_libraries(scene object light common)

aux_source_directory(engine ENGINE_SRCS)
add_library(engine ${ENGINE_SRCS})
target_link_libraries(engine common object scene)

add_executable(raytracing tools/main.cpp)
target_link_libraries(raytracing object scene object engine object)