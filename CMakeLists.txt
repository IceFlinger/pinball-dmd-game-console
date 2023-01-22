# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "E:/Programs/Pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(stern-dmd-driver C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(stern-dmd-driver stern-dmd-driver.c util.c screen.c nes_input.c channels/game_example.c channels/screensaver.c channels/conway.c)

pico_set_program_name(stern-dmd-driver "stern-dmd-driver")
pico_set_program_version(stern-dmd-driver "0.1")

pico_enable_stdio_uart(stern-dmd-driver 1)
pico_enable_stdio_usb(stern-dmd-driver 0)

# Add the standard library to the build
target_link_libraries(stern-dmd-driver pico_stdlib pico_multicore)

# Add any user requested libraries
target_link_libraries(stern-dmd-driver
        hardware_spi
        hardware_i2c
        hardware_adc
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        )

pico_add_extra_outputs(stern-dmd-driver)

