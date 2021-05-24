cmake_minimum_required(VERSION 3.5)
project(lsm303dlhc-i2c VERSION 0.1.0)

set(cubeos_hal_dir "${lsm303dlhc-i2c_SOURCE_DIR}/../../../../hal/cubeos-hal/")
add_subdirectory("${cubeos_hal_dir}" "${CMAKE_BINARY_DIR}/cubeos-hal-build")

add_executable(lsm303dlhc-i2c
  source/main.c)

target_include_directories(lsm303dlhc-i2c
  PRIVATE "${cubeos_hal_dir}/cubeos-hal"
)

target_link_libraries(lsm303dlhc-i2c cubeos-hal)
