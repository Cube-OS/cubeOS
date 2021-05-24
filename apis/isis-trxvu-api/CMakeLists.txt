cmake_minimum_required(VERSION 3.5)
project(isis-trxvu-api VERSION 1.0.0)

set(cubeos_hal_dir "${isis-trxvu-api_SOURCE_DIR}/../../hal/cubeos-hal/")
add_subdirectory("${cubeos_hal_dir}" "${CMAKE_BINARY_DIR}/cubeos-hal-build")

add_library(isis-trxvu-api
  source/radio_core.c
  source/radio_rx.c
  source/radio_tx.c
)

target_include_directories(isis-trxvu-api
  PUBLIC "${isis-trxvu-api_SOURCE_DIR}/isis-trxvu-api"
)

target_link_libraries(isis-trxvu-api
  cubeos-hal
  pthread
  m
)
