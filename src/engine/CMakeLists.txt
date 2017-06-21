aux_source_directory(raytrace RAYTRACE_SRCS)
aux_source_directory(photonmap PHOTONMAP_SRCS)
aux_source_directory(. ENGINE_SRCS)
add_library(engine ${RAYTRACE_SRCS} ${PHOTONMAP_SRCS} ${ENGINE_SRCS})