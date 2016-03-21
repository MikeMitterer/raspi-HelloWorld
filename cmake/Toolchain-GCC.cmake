include(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Darwin)
SET(CMAKE_SYSTEM_VERSION 1)

#set(CMAKE_SYSTEM_PROCESSOR arm )

# War mal notwendig - funkt aber nur
# Im CMakeList.txt under project
# set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

# specify the cross compiler
set(CROSS_COMPILER_PATH "/usr/local/Cellar/gcc/5.3.0")
set(CROSS_COMPILER_BIN "${CROSS_COMPILER_PATH}/bin")
#SET(CROSS_COMPILER arm-linux-gnueabihf-)

##set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/opt/vc/lib")
#set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/lib/arm-linux-gnueabihf")
#set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/usr/lib/arm-linux-gnueabihf")
#set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/usr/local/lib")
#set(RPATH_FLAGS ${FLAGS})

SET(CMAKE_C_COMPILER "${CROSS_COMPILER_BIN}/gcc-5")
SET(CMAKE_CXX_COMPILER "${CROSS_COMPILER_BIN}/g++-5")
#SET(CMAKE_ASM_COMPILER as)
SET(CMAKE_AR "${CROSS_COMPILER_BIN}/gcc-ar-5")
SET(CMAKE_RANLIB "${CROSS_COMPILER_BIN}/gcc-ranlib-5")
#SET(CMAKE_RANLIB ${XCOMPILER}ranlib)
#PKG_CONFIG_EXECUTABLE=arm-linux-gnueabihf-pkg-config.

#UNSET(CMAKE_C_FLAGS CACHE)
#UNSET(CMAKE_CXX_FLAGS CACHE)

#SET(CMAKE_CXX_FLAGS ${RPATH_FLAGS} CACHE STRING "c++ flags" FORCE)
#SET(CMAKE_C_FLAGS ${RPATH_FLAGS} CACHE STRING "c flags" FORCE)

#SET(CMAKE_SYSROOT ${PIROOT})
#SET(CMAKE_FIND_ROOT_PATH ${PIROOT})

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

CMAKE_FORCE_C_COMPILER(gcc-5 GNU)
CMAKE_FORCE_CXX_COMPILER(g++-5 GNU)

#message( STATUS "PIROOT:                  " ${PIROOT} )
#message( STATUS "CMAKE_FRAMEWORK_PATH:    " ${CROSS_COMPILER_PATH} )
#message( WARNING "CMAKE_FRAMEWORK_PATH:     " ${CMAKE_FRAMEWORK_PATH} )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Project                                                         │
# └──────────────────────────────────────────────────────────────────┘

#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
#    ${PIROOT}/lib ${PIROOT}/lib/arm-linux-gnueabihf
#    ${PIROOT}/usr/lib ${PIROOT}/usr/lib/arm-linux-gnueabihf
#)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Pocco                                                           │
# └──────────────────────────────────────────────────────────────────┘

#set(Poco_DIR ${PIROOT}/usr/lib)
