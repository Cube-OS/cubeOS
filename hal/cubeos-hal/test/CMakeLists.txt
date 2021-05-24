cmake_minimum_required(VERSION 3.5)
project(cubeos-hal-tests)

set(cmocka_dir "${cubeos-hal-tests_SOURCE_DIR}/../../../cmocka/")
add_subdirectory("${cmocka_dir}" "${CMAKE_BINARY_DIR}/cmocka-build")

set(hal_dir "${cubeos-hal-tests_SOURCE_DIR}/../")
add_subdirectory("${hal_dir}" "${CMAKE_BINARY_DIR}/hal-build")

add_executable(cubeos-hal-test-i2c
  i2c/i2c.c
  i2c/sysfs.c)

target_include_directories(cubeos-hal-test-i2c
  PRIVATE "${cmocka_dir}/cmocka-1.1.0/include"
  PRIVATE "${hal_dir}/cubeos-hal"
)

set_target_properties(cubeos-hal-test-i2c
        PROPERTIES
        LINK_FLAGS
        "-Wl,--wrap=open \
         -Wl,--wrap=close \
         -Wl,--wrap=ioctl \
         -Wl,--wrap=write \
         -Wl,--wrap=read")

target_link_libraries(cubeos-hal-test-i2c
  cmocka
  cubeos-hal
)

add_test(cubeos-hal-test-i2c cubeos-hal-test-i2c)
enable_testing()
