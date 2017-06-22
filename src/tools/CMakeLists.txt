set(MODELING_SRCS modeling.cpp)
set(TESTOR_SRCS test.cpp)
set(RENDER_SRCS render.cpp)
set(RENDER_SRCS render.cpp)

add_executable(mm ${MODELING_SRCS})
target_link_libraries(mm object)

add_executable(testor ${TESTOR_SRCS})
target_link_libraries(testor engine)

add_executable(genscene )

add_executable(renderEx ${RENDER_SRCS})
target_link_libraries(renderEx engine)
