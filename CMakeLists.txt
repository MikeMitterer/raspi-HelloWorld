cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(Toolchain-RaspberryPi)
include(Config)

project(RaspiHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS} --verbose")
#SET(GCC_COVERAGE_LINK_FLAGS    "--specs=nosys.specs")

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
#set( ENV{PKG_CONFIG_PATH} "/usr/local/linaro/arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-pkg-config" )

find_package(PkgConfig REQUIRED)
set(PKG_CONFIG_EXECUTABLE  "/usr/local/linaro/arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-pkg-config")

set(ROOTFS "/Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs")
set(RASPIAN "/usr/local/linaro/arm-linux-gnueabihf-raspbian")
set(RASPIAN_LIBC "${RASPIAN}/arm-linux-gnueabihf/libc")

message( STATUS "MYROOTFS:   " ${ROOTFS} )

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    ${RASPIAN_LIBC}
    ${ROOTFS}/lib ${ROOTFS}/lib/arm-linux-gnueabihf
    ${ROOTFS}/usr/lib ${ROOTFS}/usr/lib/arm-linux-gnueabihf
)

set(CMAKE_MODULE_PATH
        ${ROOTFS}
        ${ROOTFS}/lib ${ROOTFS}/lib/arm-linux-gnueabihf
        ${ROOTFS}/usr/lib ${ROOTFS}/usr/lib/arm-linux-gnueabihf
        )

find_library(WIRINGPI
        NAMES libwiringPi libwiringPi.so
        HINTS "
              ${ROOTFS}/lib ${ROOTFS}/lib/arm-linux-gnueabihf
              ${ROOTFS}/usr/lib ${ROOTFS}/usr/lib/arm-linux-gnueabihf
              "
)
message( STATUS "WIRINGPI:   " ${WIRINGPI} )

#find_library(PTHREAD
#        NAMES libpthread libpthread.so libpthread.so.0
#        HINTS "
#              ${RASPIAN_LIBC}
#              "
#)
if(NOT ${PTHREAD})
    set(PTHREAD "${RASPIAN_LIBC}/usr/lib/arm-linux-gnueabihf/libpthread.so")
endif()
message( STATUS "PTHREAD:    " ${PTHREAD} )

file(GLOB_RECURSE ALLLIBS
        "${ROOTFS}/lib/arm-linux-gnueabihf/*.so"
        "${ROOTFS}/usr/lib/arm-linux-gnueabihf/*.so"
)
#message( WARNING "ALLLIBS:    " ${ALLLIBS} )
message( WARNING "CROSS_COMPILER_PATH:    " ${CROSS_COMPILER_PATH} )

#find_library(OPENCV
#        NAMES libopencv_core.so.2.4
#        HINTS "
#              ${ROOTFS}/lib ${ROOTFS}/lib/arm-linux-gnueabihf
#              ${ROOTFS}/usr/lib ${ROOTFS}/usr/lib/arm-linux-gnueabihf
#              "
#        )
#message( STATUS "OPENCV:   " ${OPENCV} )
#
#find_library(OPENCV_HIGHGUI
#        NAMES libopencv_highgui.so.2.4
#        HINTS "
#              ${ROOTFS}/lib ${ROOTFS}/lib/arm-linux-gnueabihf
#              ${ROOTFS}/usr/lib ${ROOTFS}/usr/lib/arm-linux-gnueabihf
#              "
#        )
#message( STATUS "OPENCV_HIGHGUI:   " ${OPENCV_HIGHGUI} )

find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp)

add_executable(RaspiHelloWorld ${SOURCE_FILES})

target_include_directories(
        RaspiHelloWorld
        PUBLIC ${ROOTFS}/usr/include
        PUBLIC ${ROOTFS}/usr/include/arm-linux-gnueabihf
)

target_link_libraries (
        RaspiHelloWorld
        ${PTHREAD}
#        ${PTHREAD} ${WIRINGPI}

        ${OpenCV_LIBS}

        #${ROOTFS}/usr/lib/arm-linux-gnueabihf/libpthread.so

#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libSM.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libICE.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libX11.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libXext.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libjpeg.so
#        ${ROOTFS}/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/jre/lib/arm/libjpeg.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libpng12.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libtiff.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libjasper.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libImath.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libIlmImf.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libIex.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libHalf.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libIlmThread.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgtk-x11-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgdk-x11-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libpangocairo-1.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libatk-1.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libcairo.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgdk_pixbuf-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgio-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libpangoft2-1.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libpango-1.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgobject-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libfontconfig.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libfreetype.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgthread-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libgmodule-2.0.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libdc1394.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libavcodec.so
#        ${ROOTFS}/usr/lib/omxplayer/libavcodec.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libavformat.so
#        ${ROOTFS}/usr/lib/omxplayer/libavformat.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libavutil.so
#        ${ROOTFS}/usr/lib/omxplayer/libavutil.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libswscale.so
#        ${ROOTFS}/usr/lib/omxplayer/libswscale.so
#        ${ROOTFS}/usr/lib/arm-linux-gnueabihf/libpng12.so

#        ${ALLLIBS}
#        ${ROOTFS}/lib/arm-linux-gnueabihf/libm-2.19.so
)