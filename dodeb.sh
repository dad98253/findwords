#! /bin/sh
#
# =======================================================================
#
# clean out the deb build data and do a fresh build of the deb files
#
# Notes: 
#   This script must be run from this directory!
#   Do NOT make changes to the files in the debian build folder! Make
#   all file changes to the original files that are stored in the current
#   (original starting point) directory tree. The debian build files are
#   whiped clean by this script!
#
# =======================================================================
#

export PROGNAM="permute"
export PVER="0.2"
export BVER="1"
export BASEBDIR="$HOME/src"
export ORIGDIR=$(pwd)
export BARCH="amd64"
export SYSBINDIR="/usr/bin"
export BNAM="$PROGNAM-$PVER"
export BBNAM="${PROGNAM}_$PVER-$BVER"
export BTRIP="${BBNAM}_$BARCH"
export BBDIR="$BASEBDIR/$BNAM"

$SYSBINDIR/echo cretate a fresh dist file
$SYSBINDIR/autoreconf -i -f
./configure
$SYSBINDIR/make dist

$SYSBINDIR/echo go to the build dir
cd $BASEBDIR

$SYSBINDIR/echo clean out old deb and dist files
$SYSBINDIR/rm $BNAM.tar.gz
$SYSBINDIR/rm $BTRIP.build
$SYSBINDIR/rm $BTRIP.changes
$SYSBINDIR/rm $BTRIP.buildinfo
$SYSBINDIR/rm $BTRIP.deb
$SYSBINDIR/rm $BBNAM.dsc
$SYSBINDIR/rm $BBNAM.debian.tar.xz
$SYSBINDIR/rm $BBNAM.diff.gz
$SYSBINDIR/rm $PROGNAM-dbgsym_$PVER-${BVER}_amd64.ddeb
$SYSBINDIR/rm ${PROGNAM}_$PVER.orig.tar.gz

$SYSBINDIR/echo clean out old build dir
$SYSBINDIR/rm -rf $BNAM

$SYSBINDIR/echo copy over new dist file
$SYSBINDIR/cp $ORIGDIR/$BNAM.tar.gz .

$SYSBINDIR/echo unzip the dist
$SYSBINDIR/tar -xvzf $BNAM.tar.gz

$SYSBINDIR/echo go down into the build directory
cd $BNAM

$SYSBINDIR/echo copy over all of the debian files
$SYSBINDIR/cp -r -p $ORIGDIR/debian .

$SYSBINDIR/echo make the deb stuff
$SYSBINDIR/debmake

$SYSBINDIR/echo build the deb stuff
$SYSBINDIR/debuild

$SYSBINDIR/echo all done with dodeb.sh ...
cd $ORIGDIR


