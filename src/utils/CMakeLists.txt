aux_source_directory(. UTILS_SRCS)
add_library(utils ${UTILS_SRCS})
target_link_libraries(utils common)
