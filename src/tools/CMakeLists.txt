set(MODELING_SRCS mesh.cpp)
set(TESTOR_SRCS test.cpp)
set(RENDER_SRCS render.cpp)
set(GEN_SRCS genscene.cpp)

add_executable(mm ${MODELING_SRCS})
target_link_libraries(mm object)

add_executable(testor ${TESTOR_SRCS})
target_link_libraries(testor engine)

add_executable(genscene ${GEN_SRCS})
target_link_libraries(genscene env utils common)

add_executable(renderEx ${RENDER_SRCS})
target_link_libraries(renderEx engine)
