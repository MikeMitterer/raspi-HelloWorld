#!/usr/bin/env bash
##################################################################
#
# Mounts bin NFS share from RASPI
#
##################################################################

APPNAME="mounter.sh"

#------------------------------------------------------------------------------
# BASIS

LOGFILE="${APPNAME}_`date +"%Y%m%d"`.log"
ROOTFS="/Volumes/Daten/DevLocal/DevCPP/raspberry/rootfs"

#------------------------------------------------------------------------------
# COLORS
#   Sample: echo -e "I ${RED}love${NC} Stack Overflow\n"
#

BLACK='\033[0;30m'
RED='\033[0;31m'
GREEN='\033[0;32m'
BROWN='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHT_GRAY='\033[0;37m'

DARK_GREY='\033[1;30m'
LIGHT_RED='\033[1;31m'
LIGHT_GREEN='\033[1;32m'
YELLOW='\033[1;33m'
LIGHT_BLUE='\033[1;34m'
LIGHT_PURPLE='\033[1;35m'
LIGHT_CYAN='\033[1;36m'
WHITE='\033[1;37m'

NC='\033[0m' # No Color


#------------------------------------------------------------------------------
# Lock wird gesetzt
#

LOCKDIR="/var/lock"
LOCKFILE="$LOCKDIR/$APPNAME.lock"

[ -f ${LOCKFILE} ] && exit 0

# Trap with number: http://goo.gl/IQmYna
trap 'cleanup' EXIT TERM INT

cleanup () {
    rm -f ${LOCKFILE};
    exit 255;
    }

touch ${LOCKFILE}

#------------------------------------------------------------------------------
# Read settings from settings-file
#
SETTINGS_FILE=$APPNAME.conf
SETTINGS_USER="~/.$SETTINGS_FILE"
SETTINGS_ETC="/etc/$SETTINGS_FILE"

if test -e $SETTINGS_USER
then
    . $SETTINGS_USER
elif test -e $SETTINGS_ETC
then
    . $SETTINGS_ETC
fi

#------------------------------------------------------------------------------
# Functions
#

mountBin() {
    if [ -d bin ];then
	    sudo mount -t nfs -o resvport 192.168.0.90:/home/pi/bin "bin"
    else
	    echo "BIN not found!"
    fi
}

listShares() {
     showmount -e 192.168.0.90
}

unmountBin() {
     sudo umount "bin"
}

#------------------------------------------------------------------------------
# Options
#

usage() {
    echo
    echo -e "${GREEN}Usage:${NC} `basename $0` [ options ]"
    echo -e "\t-l | --list      List RASPI (nfs) shares"
    echo -e "\t-m | --mount     Mount 'bin' to RASPIs bin"
    echo -e "\t-u | --unmount   UnMount bin' from RASPI"
    echo
    }


case "$1" in
    help|-help|--help)
	usage
	;;

    mount|-m|-mount|--mount)
	mountBin
	;;

    unmount|-u|-unmount|--unmount)
	unmountBin
	;;

    list|-l|-list|--list)
	listShares
	;;

    *)
    usage
	;;

esac

#------------------------------------------------------------------------------
# Alles OK...

exit 0
