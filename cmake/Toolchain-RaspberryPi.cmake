include(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

set( CMAKE_SYSTEM_PROCESSOR arm )

SET(PIROOT /Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs)

#set(CMAKE_CXX_FLAGS           ""                    CACHE STRING "c++ flags")
#set(CMAKE_C_FLAGS             ""                    CACHE STRING "c flags")
#set(CMAKE_SHARED_LINKER_FLAGS ""                    CACHE STRING "shared linker flags")
#set(CMAKE_MODULE_LINKER_FLAGS ""                    CACHE STRING "module linker flags")
#set(CMAKE_EXE_LINKER_FLAGS    "-Wl,-z,nocopyreloc"  CACHE STRING "executable linker flags")
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthumb -fdata-sections -Wa, -fsigned-char")
#set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -mthumb -fdata-sections -Wa, -fsigned-char")

#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now ${CMAKE_SHARED_LINKER_FLAGS}")
#set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now ${CMAKE_MODULE_LINKER_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS    "-Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now ${CMAKE_EXE_LINKER_FLAGS}")

#set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/opt/vc/lib")
set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/lib/arm-linux-gnueabihf")
set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/usr/lib/arm-linux-gnueabihf")
set(FLAGS "${FLAGS} -Wl,-rpath-link,${PIROOT}/usr/local/lib")

#SET(FLAGS "-Wl,-rpath-link,${PIROOT}/opt/vc/lib -Wl,-rpath-link,${PIROOT}/lib/arm-linux-gnueabihf -Wl,-rpath-link,${PIROOT}/usr/lib/arm-linux-gnueabihf -Wl,-rpath-link,${PIROOT}/usr/local/lib")

# specify the cross compiler
SET(XCOMPILER arm-linux-gnueabihf-)

SET(CMAKE_C_COMPILER ${XCOMPILER}gcc)
SET(CMAKE_CXX_COMPILER ${XCOMPILER}g++)
SET(CMAKE_ASM_COMPILER ${XCOMPILER}as)
SET(CMAKE_AR ${XCOMPILER}ar)
SET(CMAKE_RANLIB ${XCOMPILER}ranlib)
#SET(CMAKE_RANLIB ${XCOMPILER}ranlib)
#PKG_CONFIG_EXECUTABLE=arm-linux-gnueabihf-pkg-config.

UNSET(CMAKE_C_FLAGS CACHE)
UNSET(CMAKE_CXX_FLAGS CACHE)

SET(CMAKE_CXX_FLAGS ${FLAGS} CACHE STRING "" FORCE)
SET(CMAKE_C_FLAGS ${FLAGS} CACHE STRING "" FORCE)

SET(CMAKE_SYSROOT ${PIROOT})
SET(CMAKE_FIND_ROOT_PATH ${PIROOT})


# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

CMAKE_FORCE_C_COMPILER(${XCOMPILER}gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${XCOMPILER}g++ GNU)


