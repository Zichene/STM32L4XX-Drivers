cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME baremetal)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Add compile options
add_compile_definitions(
        STM32L4S5xx
        SPI_WIFI
)

# STM minimum includes
set(STM_Include_Dirs
        stm32/inc
        stm32/inc/cmsis
)

# STM sources
set(STM_Src
        stm32/src/main.c
        stm32/src/sysmem.c
        stm32/src/syscalls.c
        stm32/src/system_stm32l4xx.c
        stm32/src/board_specific/startup_stm32l4s5xx.s
)

# Interface library for includes and symbols
add_library(stm32 INTERFACE)
target_include_directories(stm32 INTERFACE ${STM_Include_Dirs})
target_compile_definitions(stm32 INTERFACE STM32L4S5xx)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        src/clock.c
        src/gpio.c
        src/ringbuffer.c
        src/spi.c
        src/tim.c
        src/uart.c
        inc/clock.h
        inc/common.h
        inc/ringbuffer.h
        inc/gpio.h
        inc/spi.h
        inc/tim.h
        inc/uart.h
        inc/rcc.h
        src/rcc.c
        projects/bl4s5i-iot01a/uart_receive.c
        projects/bl4s5i-iot01a/uart_printf.c
        projects/bl4s5i-iot01a/ringbuffer_test.c
        projects/bl4s5i-iot01a/push_button_led.c
        projects/bl4s5i-iot01a/blinky_led.c
        projects/bl4s5i-iot01a/spi_wifi.c
)

# Add STM sources to our project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${STM_Src})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Add STM32CubeMX generated sources
#add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME}
        PRIVATE inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32
)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
