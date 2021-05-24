cmake_minimum_required(VERSION 3.5)
project(isis-ants-api VERSION 1.0.0)

set(cubeos_hal_dir "${isis-ants-api_SOURCE_DIR}/../../hal/cubeos-hal/")
add_subdirectory("${cubeos_hal_dir}" "${CMAKE_BINARY_DIR}/cubeos-hal-build")

add_library(isis-ants-api
  source/ants.c
)

target_include_directories(isis-ants-api
  PUBLIC "${isis-ants-api_SOURCE_DIR}/isis-ants-api"
)

target_link_libraries(isis-ants-api
  cubeos-hal
  pthread
)
