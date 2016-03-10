cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(Toolchain-RaspberryPi)
include(Config)

project(RaspiHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#SET(GCC_COVERAGE_LINK_FLAGS    "--specs=nosys.specs")

set(ROOTFS "/Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs")
set(RASPIAN "/usr/local/linaro/arm-linux-gnueabihf-raspbian")
set(RASPIAN_LIBC "${RASPIAN}/arm-linux-gnueabihf/libc")

message( STATUS "MYROOTFS:   " ${ROOTFS} )

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}

)

find_library(WIRINGPI
        NAMES libwiringPi libwiringPi.so
        HINTS "
              ${ROOTFS}/lib ${ROOTFS}/lib/arm-linux-gnueabihf
              ${ROOTFS}/usr/lib ${ROOTFS}/usr/lib/arm-linux-gnueabihf
              "
)
message( STATUS "WIRINGPI:   " ${WIRINGPI} )

find_library(PTHREAD
        NAMES libpthread libpthread.so libpthread.so.0
        HINTS "
              ${RASPIAN_LIBC}
              "
)
if(NOT ${PTHREAD})
    set(PTHREAD "${RASPIAN_LIBC}/usr/lib/arm-linux-gnueabihf/libpthread.so")
endif()
message( STATUS "PTHREAD:    " ${PTHREAD} )

set(SOURCE_FILES main.cpp)

add_executable(RaspiHelloWorld ${SOURCE_FILES})

target_include_directories(
        RaspiHelloWorld
        PUBLIC ${ROOTFS}/usr/include
        PUBLIC ${ROOTFS}/usr/include/arm-linux-gnueabihf
)

target_link_libraries (
        RaspiHelloWorld
        ${PTHREAD} ${WIRINGPI}
)