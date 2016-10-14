cmake_minimum_required(VERSION 3.0)

# List of directories to search for CMake modules.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#include(Toolchain-RaspberryPi)

#include(Config)

project(RaspiHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
# -mfpu=vfp -mfloat-abi=hard
#SET(GCC_COVERAGE_LINK_FLAGS    "--specs=nosys.specs")

set(RASPIAN "/usr/local/linaro/arm-linux-gnueabihf-raspbian")
set(RASPIAN_LIBC "${RASPIAN}/arm-linux-gnueabihf/libc")

#set(PIROOT "/Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs")

set(SHARED_FOLDER  "_shared")

message( STATUS "MYROOTFS:   " ${ROOTFS} )

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}

)

#set(CMAKE_PREFIX_PATH ${RF24PATH} ${CMAKE_PREFIX_PATH})

# Bei der Aktivierung muss auch der Teil in target_link_libraries
# wieder aktiviert werden!
#
# find_library(WIRINGPI
#        NAMES libwiringPi libwiringPi.so
#        HINTS "
#              ${PIROOT}/usr/lib
#              "
#        )

find_library(RF24
        NAMES librf24-bcm.so librf24-bcm.so.1
        HINTS ${PIROOT}
)

message( STATUS "WIRINGPI:                " ${WIRINGPI} )
message( STATUS "PIROOT:                  " ${PIROOT} )
message( STATUS "RF24:                    " ${RF24} )

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

set(SOURCE_FILES
        main.cpp
        include/GPIO.h
        ${SHARED_FOLDER}/rf24/rf24.cpp
        ${SHARED_FOLDER}/rf24/ReadingPipe.hpp
        ${SHARED_FOLDER}/rf24/MsgToSend.hpp)

add_executable(RaspiHelloWorld ${SOURCE_FILES})

target_include_directories(
        RaspiHelloWorld
        PUBLIC include

        PUBLIC ${SHARED_FOLDER}/rf24

        # PUBLIC ${PIROOT}/usr/include

        # Komischer Hack - CLion findet die Files in .../usr/include nicht
        # https://youtrack.jetbrains.com/issue/CPP-7257
        PUBLIC ${PIROOT}/usr/clion/include
        PUBLIC ${PIROOT}/usr/local/include
)

target_link_libraries (
        RaspiHelloWorld
        ${RF24}
        # ${WIRINGPI}
)
