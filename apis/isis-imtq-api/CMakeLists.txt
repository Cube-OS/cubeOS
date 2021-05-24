cmake_minimum_required(VERSION 3.5)
project(isis-imtq-api VERSION 1.0.0)

set(cubeos_hal_dir "${isis-imtq-api_SOURCE_DIR}/../../hal/cubeos-hal/")
add_subdirectory("${cubeos_hal_dir}" "${CMAKE_BINARY_DIR}/cubeos-hal-build")

set(json_dir "${isis-imtq-api_SOURCE_DIR}/../../ccan/json/")
add_subdirectory("${json_dir}" "${CMAKE_BINARY_DIR}/json-build")

add_library(isis-imtq-api
  source/imtq-config.c
  source/imtq-core.c
  source/imtq-data.c
  source/imtq-ops.c
)

target_include_directories(isis-imtq-api
  PUBLIC "${isis-imtq-api_SOURCE_DIR}/isis-imtq-api"
)

target_link_libraries(isis-imtq-api
  cubeos-hal
  json
  pthread
)
