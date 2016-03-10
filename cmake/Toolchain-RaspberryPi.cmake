include(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(XCOMPILER arm-linux-gnueabihf-)

SET(CMAKE_C_COMPILER ${XCOMPILER}gcc)
SET(CMAKE_CXX_COMPILER ${XCOMPILER}g++)
SET(CMAKE_ASM_COMPILER ${XCOMPILER}as)
SET(CMAKE_AR ${XCOMPILER}ar)
SET(CMAKE_RANLIB ${XCOMPILER}ranlib)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

CMAKE_FORCE_C_COMPILER(${XCOMPILER}gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${XCOMPILER}g++ GNU)

