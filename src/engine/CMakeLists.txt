aux_source_directory(. ENGINE_SRCS)
aux_source_directory(raytracer RAY_TRACER_SRCS)
aux_source_directory(photonmapper PHOTON_MAPPER_SRCS)
aux_source_directory(ppm PP_SRCS)

add_library(engine ${ENGINE_SRCS} ${RAY_TRACER_SRCS} ${PHOTON_MAPPER_SRCS} ${PP_SRCS})
target_link_libraries(engine env pthread)
