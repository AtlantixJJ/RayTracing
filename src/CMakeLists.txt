set(src_dir ${PROJECT_SOURCE_DIR}/src )

include_directories(${PROJECT_SOURCE_DIR}/tools)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${ROOT_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${ROOT_DIR}/lib)

aux_source_directory(${src_dir}/common COMMON_SRCS)
aux_source_directory(${src_dir}/util UTIL_SRCS)
aux_source_directory(${src_dir}/light LIGHT_SRCS)
aux_source_directory(${src_dir}/object OBJECT_SRCS)
aux_source_directory(${src_dir}/scene SCENE_SRCS)
aux_source_directory(${src_dir}/engine RAY_TRACING_SRCS)
aux_source_directory(${src_dir}/modeling MODELING)

add_library(common ${COMMON_SRCS})
add_library(util ${UTIL_SRCS})
add_library(light ${LIGHT_SRCS})
add_library(object ${OBJECT_SRCS})
add_library(scene ${SCENE_SRCS})
add_library(engine ${RAY_TRACING_SRCS})
#add_library(modeling ${MODELING})

target_link_libraries(object util common)
target_link_libraries(scene object light common)
target_link_libraries(engine scene jsoncpp_lib_static)
#target_link_libraries(modeling object jsoncpp_lib_static)
