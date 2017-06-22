aux_source_directory(. SCENE_SRCS)
add_library(env ${SCENE_SRCS})
target_link_libraries(env utils math object light common)
