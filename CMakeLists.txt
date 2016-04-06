cmake_minimum_required(VERSION 2.8)

# List of directories to search for CMake modules.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(Toolchain-RaspberryPi)
include(Config)

project(RaspiHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
# -mfpu=vfp -mfloat-abi=hard
#SET(GCC_COVERAGE_LINK_FLAGS    "--specs=nosys.specs")

set(RASPIAN "/usr/local/linaro/arm-linux-gnueabihf-raspbian")
set(RASPIAN_LIBC "${RASPIAN}/arm-linux-gnueabihf/libc")

message( STATUS "MYROOTFS:   " ${ROOTFS} )

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}

)

find_library(WIRINGPI
        NAMES libwiringPi libwiringPi.so
        HINTS "
              ${PIROOT}/usr/lib
              "
        )

find_library(RF24
        NAMES librf24-bcm.so librf24-bcm.so.1
        HINTS "
              ${PIROOT}/usr/local/lib
              "
)
message( STATUS "WIRINGPI:   " ${WIRINGPI} )

#find_library(PTHREAD
#        NAMES libpthread libpthread.so libpthread.so.0
#        HINTS "
#              ${RASPIAN_LIBC}
#              "
#)
#if(NOT ${PTHREAD})
#    set(PTHREAD "${RASPIAN_LIBC}/usr/lib/arm-linux-gnueabihf/libpthread.so")
#endif()
#message( STATUS "PTHREAD:    " ${PTHREAD} )

set(SOURCE_FILES main.cpp)

add_executable(RaspiHelloWorld ${SOURCE_FILES})

target_include_directories(
        RaspiHelloWorld
        PUBLIC ${PIROOT}/usr/local/include
        PUBLIC ${PIROOT}/usr/include
)

target_link_libraries (
        RaspiHelloWorld
        ${RF24}
#        ${WIRINGPI}
)