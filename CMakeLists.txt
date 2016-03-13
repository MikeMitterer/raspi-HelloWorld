cmake_minimum_required(VERSION 2.8)

# List of directories to search for CMake modules.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(Toolchain-RaspberryPi)
include(Config)

project(RaspiHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --verbose")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    ${PIROOT}/lib ${PIROOT}/lib/arm-linux-gnueabihf
    ${PIROOT}/usr/lib ${PIROOT}/usr/lib/arm-linux-gnueabihf
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Qt                                                              │
# └──────────────────────────────────────────────────────────────────┘

set(QT5DIR "${PIROOT}/usr/lib/arm-linux-gnueabihf/qt5")

set(CMAKE_PREFIX_PATH ${QT5DIR} ${CMAKE_PREFIX_PATH})
message( WARNING "CMAKE_PREFIX_PATH:       " ${CMAKE_PREFIX_PATH} )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core
        PATHS "${PIROOT}/usr/lib/arm-linux-gnueabihf/cmake" ${QT5DIR}
        REQUIRED)
#find_package(Qt5Widgets REQUIRED)


# Sample - findet alle SOs
# file(GLOB_RECURSE ALLLIBS
#         "${PIROOT}/lib/arm-linux-gnueabihf/*.so"
#         "${PIROOT}/usr/lib/arm-linux-gnueabihf/*.so"
# )


set(SOURCE_FILES main.cpp)

add_executable(RaspiHelloWorld ${SOURCE_FILES})

target_include_directories(
        RaspiHelloWorld
        PUBLIC "${PIROOT}/usr/include"
        PUBLIC "${PIROOT}/usr/include/arm-linux-gnueabihf"
)

target_link_libraries (
        RaspiHelloWorld
)

qt5_use_modules(RaspiHelloWorld Widgets)