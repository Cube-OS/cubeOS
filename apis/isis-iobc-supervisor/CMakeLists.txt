cmake_minimum_required(VERSION 3.5)
project(isis-supervisor-api VERSION 1.0.0)

set(cubeos_hal_dir "${isis-supervisor-api_SOURCE_DIR}/../../hal/cubeos-hal/")
add_subdirectory("${cubeos_hal_dir}" "${CMAKE_BINARY_DIR}/cubeos-hal-build")

add_library(isis-supervisor-api
  source/checksum.c
  source/supervisor.c
)

target_include_directories(isis-supervisor-api
  PUBLIC "${isis-supervisor-api_SOURCE_DIR}/isis-iobc-supervisor"
)

target_link_libraries(isis-supervisor-api
  cubeos-hal
)
