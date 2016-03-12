brew install Caskroom/cask/gcc-arm-embedded

    ==> Symlinking Binary 'arm-none-eabi-addr2line' to '/usr/local/bin/arm-none-eabi-addr2line'
    ==> Symlinking Binary 'arm-none-eabi-ar' to '/usr/local/bin/arm-none-eabi-ar'
    ==> Symlinking Binary 'arm-none-eabi-as' to '/usr/local/bin/arm-none-eabi-as'
    ==> Symlinking Binary 'arm-none-eabi-c++' to '/usr/local/bin/arm-none-eabi-c++'
    ==> Symlinking Binary 'arm-none-eabi-c++filt' to '/usr/local/bin/arm-none-eabi-c++filt'
    ==> Symlinking Binary 'arm-none-eabi-cpp' to '/usr/local/bin/arm-none-eabi-cpp'
    ==> Symlinking Binary 'arm-none-eabi-elfedit' to '/usr/local/bin/arm-none-eabi-elfedit'
    ==> Symlinking Binary 'arm-none-eabi-g++' to '/usr/local/bin/arm-none-eabi-g++'
    ==> Symlinking Binary 'arm-none-eabi-gcc' to '/usr/local/bin/arm-none-eabi-gcc'
    ==> Symlinking Binary 'arm-none-eabi-gcc-ar' to '/usr/local/bin/arm-none-eabi-gcc-ar'
    ==> Symlinking Binary 'arm-none-eabi-gcc-nm' to '/usr/local/bin/arm-none-eabi-gcc-nm'
    ==> Symlinking Binary 'arm-none-eabi-gcc-ranlib' to '/usr/local/bin/arm-none-eabi-gcc-ranlib'
    ==> Symlinking Binary 'arm-none-eabi-gcov' to '/usr/local/bin/arm-none-eabi-gcov'
    ==> Symlinking Binary 'arm-none-eabi-gcov-tool' to '/usr/local/bin/arm-none-eabi-gcov-tool'
    ==> Symlinking Binary 'arm-none-eabi-gdb' to '/usr/local/bin/arm-none-eabi-gdb'
    ==> Symlinking Binary 'arm-none-eabi-gdb-py' to '/usr/local/bin/arm-none-eabi-gdb-py'
    ==> Symlinking Binary 'arm-none-eabi-gprof' to '/usr/local/bin/arm-none-eabi-gprof'
    ==> Symlinking Binary 'arm-none-eabi-ld' to '/usr/local/bin/arm-none-eabi-ld'
    ==> Symlinking Binary 'arm-none-eabi-ld.bfd' to '/usr/local/bin/arm-none-eabi-ld.bfd'
    ==> Symlinking Binary 'arm-none-eabi-nm' to '/usr/local/bin/arm-none-eabi-nm'
    ==> Symlinking Binary 'arm-none-eabi-objcopy' to '/usr/local/bin/arm-none-eabi-objcopy'
    ==> Symlinking Binary 'arm-none-eabi-objdump' to '/usr/local/bin/arm-none-eabi-objdump'
    ==> Symlinking Binary 'arm-none-eabi-ranlib' to '/usr/local/bin/arm-none-eabi-ranlib'
    ==> Symlinking Binary 'arm-none-eabi-readelf' to '/usr/local/bin/arm-none-eabi-readelf'
    ==> Symlinking Binary 'arm-none-eabi-size' to '/usr/local/bin/arm-none-eabi-size'
    ==> Symlinking Binary 'arm-none-eabi-strings' to '/usr/local/bin/arm-none-eabi-strings'
    ==> Symlinking Binary 'arm-none-eabi-strip' to '/usr/local/bin/arm-none-eabi-strip'


    6d83590c32d1cdbc1da89f7bd4c4302eb1d59e84


cmake CMAKE_BUILD_TYPE=Debug -D CMAKE_TOOLCHAIN_FILE=../cmake/Toolchain-RaspberryPi.cmake ..

brew cask uninstall gcc-arm-embedded


rsync -rl --delete-after --safe-links pi@192.168.1.PI:/{lib,usr} $HOME/raspberrypi/rootfs

rsync -rl --delete-after --safe-links pi@192.168.0.90:/{lib,usr} /Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs
rsync -rlv --delete --safe-links --exclude-from 'exclude-list.txt' pi@192.168.0.90:/{lib,usr} /Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs

/usr/local/linaro/arm-linux-gnueabihf-raspbian/bin



http://www.jaredwolff.com/blog/cross-compiling-on-mac-osx-for-raspberry-pi/

https://github.com/raspberrypi/tools/issues/51

ct-ng armv7-rpi2-linux-gnueabihf


mikemitterer@Mikes-Mac-Pro-2 bin $ ls -la cc
lrwxr-xr-x  1 root  wheel  5  5 Aug  2014 cc -> clang
mikemitterer@Mikes-Mac-Pro-2 bin $ ls -la gcc
-rwxr-xr-x  1 root  wheel  14224  5 Aug  2014 gcc
mikemitterer@Mikes-Mac-Pro-2 bin $ ls -la c++
lrwxr-xr-x  1 root  wheel  7  5 Aug  2014 c++ -> clang++
mikemitterer@Mikes-Mac-Pro-2 bin $ ls -la g++
-rwxr-xr-x  1 root  wheel  14224  5 Aug  2014 g++
mikemitterer@Mikes-Mac-Pro-2 bin $ ls -la clang
-rwxr-xr-x  1 root  wheel  14224  5 Aug  2014 clang
mikemitterer@Mikes-Mac-Pro-2 bin $ mv cc cc.clang
mv: rename cc to cc.clang: Permission denied
mikemitterer@Mikes-Mac-Pro-2 bin $ sudo suz
Password:
mikemitterer@Mikes-Mac-Pro-2 bin $ sudo su
Password:
root@Mikes-Mac-Pro-2 bin $ mv cc cc.clang
root@Mikes-Mac-Pro-2 bin $ mv gcc gcc.clang
root@Mikes-Mac-Pro-2 bin $ mv c++ c++.clang
root@Mikes-Mac-Pro-2 bin $ mv g++ g++.clang


Libs
    .so files are dynamic libraries. The suffix stands for "shared object",
    because all the applications that are linked with the library use the same
    file, rather than making a copy in the resulting executable.

    .a files are static libraries. The suffix stands for "archive",
    because they're actually just an archive (made with the ar command -- a predecessor
    of tar that's now just used for making libraries) of the original .o object files.

    .la files are static libraries used by the GNU "libtools" package.
    You can find more information about them in this question: What is libtool's .la file for?

https://learn.sparkfun.com/tutorials/raspberry-gpio/all

http://pinout.xyz/pinout/wiringpi_gpio_pinout

http://wiringpi.com/the-gpio-utility/

http://raspberrypiguide.de/howtos/raspberry-pi-gpio-how-to/

https://projects.drogon.net/raspberry-pi/wiringpi/the-gpio-utility/

RemoteDebugging
    https://sourceware.org/gdb/wiki/BuildingCrossGDBandGDBserver
                                                                      cd b
1
2
3
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo rpi-update


https://solderspot.wordpress.com/2016/02/04/cross-compiling-for-raspberry-pi-part-ii/
https://aabdelfattah.wordpress.com/2014/03/08/cross-compiling-a-pie-the-raspberry-pi-ultimate-guide/


PKG_CONFIG_PATH=`pwd` arm-linux-gnueabihf-pkg-config --libs --cflags libopencv_highgui

-DCROSS_COMPILER_PATH=(path to compiler folder) cmake option.


https://aplacetogeek.wordpress.com/qt-opencv-v4l-cross-compiling-raspberry-pi-beagle-bone/


https://www.elektronik-kompendium.de/sites/raspberry-pi/2007061.htm
,anonuid=501,anongid=20
(mikemitterer, staff)

exportfs -ra
  service rpcbind restart
  service nfs-kernel-server restart
  service nfs-kernel-server status

showmount -e 192.168.0.90
    sudo mount -t nfs -o resvport 192.168.0.90:/lib lib
    sudo mount -t nfs -o resvport 192.168.0.90:/usr usr

    sudo mount -t nfs -o resvport 192.168.0.90:/home/pi/bin bin

http://www.gtkdb.de/index_36_1976.html

http://krypted.com/mac-os-x/create-groups-using-dscl/
 dscl . create /Groups/nfsshare
 dscl . create /Groups/nfsshare gid 1000

dseditgroup -o edit -a mikemitterer -t user nfsshare


https://www.raspberrypi.org/documentation/remote-access/vnc/