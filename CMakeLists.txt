cmake_minimum_required(VERSION 3.2)

# List of directories to search for CMake modules.
set(CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake
        ${CMAKE_MODULE_PATH})

include(Toolchain-GCC)
include(Config)

project(RaspiHelloWorld)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
        gtest
        URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "--verbose")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
        /usr/local/lib
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Pocco                                                           │
# └──────────────────────────────────────────────────────────────────┘

#set(ENV{Poco_DIR} ${PIROOT}/usr/lib)
#set(Poco_DIR ${PIROOT}/usr/lib)

#set(Poco_DIR /usr/local/Cellar/poco/1.7.1/lib )
find_package(Poco

        )

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

message( WARNING "Poco_LIBRARIES:     " ${Poco_LIBRARIES} )
message( WARNING "Poco_INCLUDE_DIRS:     " ${Poco_INCLUDE_DIRS} )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Tests                                                           │
# └──────────────────────────────────────────────────────────────────┘

add_subdirectory (tests)

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
        PUBLIC "${Poco_INCLUDE_DIRS}"
)

target_link_libraries (
        RaspiHelloWorld

#        ${Poco_Foundation_LIBRARY}
        ${Poco_Foundation_LIBRARY}
        ${Poco_Util_LIBRARY}
)


