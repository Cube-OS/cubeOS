cmake_minimum_required(VERSION 3.5)
project(gomspace-p31u-api VERSION 1.0.0)

set(cubeos_hal_dir "${gomspace-p31u-api_SOURCE_DIR}/../../hal/cubeos-hal/")
add_subdirectory("${cubeos_hal_dir}" "${CMAKE_BINARY_DIR}/cubeos-hal-build")

add_library(gomspace-p31u-api
  source/nanopower.c
)

target_include_directories(gomspace-p31u-api
  PUBLIC "${gomspace-p31u-api_SOURCE_DIR}/gomspace-p31u-api"
)

target_link_libraries(gomspace-p31u-api
  cubeos-hal
  pthread
)
