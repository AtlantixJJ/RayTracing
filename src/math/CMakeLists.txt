aux_source_directory(. MATH_SRCS)
add_library(math ${MATH_SRCS})
target_link_libraries(math object light common)
