cmake_minimum_required(VERSION 2.8)

# List of directories to search for CMake modules.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(Toolchain-RaspberryPi)
include(Config)

project(RaspiHelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --verbose")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    ${PIROOT}/lib ${PIROOT}/lib/arm-linux-gnueabihf
    ${PIROOT}/usr/lib ${PIROOT}/usr/lib/arm-linux-gnueabihf
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Boost                                                           │
# └──────────────────────────────────────────────────────────────────┘
# http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)

#set(ENV{Boost_DIR} "${PIROOT}/usr/include/boost")
set(BOOST_ROOT ${PIROOT}/usr)
#set(BOOST_INCLUDEDIR "${PIROOT}/usr/include")
#set(BOOST_LIBRARYDIR "${PIROOT}/usr/lib/arm-linux-gnueabihf")

set(Boost_NO_SYSTEM_PATHS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Boost
        COMPONENTS program_options date_time
        REQUIRED)
message( WARNING "Boost_INCLUDE_DIRS:     " ${Boost_INCLUDE_DIRS} )
message( WARNING "Boost_LIBRARIES:     " ${Boost_LIBRARIES} )


# Sample - findet alle SOs
# file(GLOB_RECURSE ALLLIBS
#         "${PIROOT}/lib/arm-linux-gnueabihf/*.so"
#         "${PIROOT}/usr/lib/arm-linux-gnueabihf/*.so"
# )


set(SOURCE_FILES main.cpp)

add_executable(RaspiHelloWorld
        main.cpp
        )

target_include_directories(
        RaspiHelloWorld
        PUBLIC "${PIROOT}/usr/include"
        PUBLIC "${PIROOT}/usr/include/arm-linux-gnueabihf"
        PUBLIC "${Boost_INCLUDE_DIRS}"
)

target_link_libraries (
        RaspiHelloWorld
        ${Boost_LIBRARIES}
)


