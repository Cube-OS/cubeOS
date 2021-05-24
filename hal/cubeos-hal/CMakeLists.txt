cmake_minimum_required(VERSION 3.5)
project(cubeos-hal VERSION 0.1.2)

add_library(cubeos-hal
  source/i2c.c
)

target_include_directories(cubeos-hal
  PUBLIC "${cubeos-hal_SOURCE_DIR}/cubeos-hal"
)
