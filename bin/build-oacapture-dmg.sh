#!/bin/bash
#
# build-oacapture-dmg.sh -- Build a DMG install file on OSX from built binaries
#
# Copyright 2013,2014,2015,2016 James Fidell (james@openastroproject.org)
#
# License:
#
# This file is part of the Open Astro Project.
#
# The Open Astro Project is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The Open Astro Project is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with the Open Astro Project.  If not, see
# <http://www.gnu.org/licenses/>.
#

ROOT=./app
APPDIR=$ROOT/oaCapture.app
rm -fr $ROOT
mkdir $ROOT
mkdir $APPDIR

mkdir $APPDIR/Contents

mkdir $APPDIR/Contents/MacOS
mkdir $APPDIR/Contents/Resources
mkdir $APPDIR/Contents/Frameworks

mkdir $APPDIR/Contents/Resources/firmware
mkdir $APPDIR/Contents/Resources/firmware/qhy

cp osx/oacapture.plist $APPDIR/Contents/Info.plist
cp osx/oaCapture.icns $APPDIR/Contents/Resources

cp oacapture/oacapture $APPDIR/Contents/MacOS/oaCapture
strip $APPDIR/Contents/MacOS/oaCapture
cp ext/libusb/examples/fxload $APPDIR/Contents/MacOS
strip $APPDIR/Contents/MacOS/fxload


cp lib/firmware/qhy/QHY{5,5II,5LOADER,6}.HEX \
    $APPDIR/Contents/Resources/firmware/qhy

/opt/local/bin/macdeployqt $APPDIR

for lib in toupcam mallincam altaircam
do
  libfile=ext/lib$lib/mac64/lib$lib.dylib
  if [ -f $libfile ]
  then
    cp $libfile $APPDIR/Contents/MacOS
  fi
done

# These are for compatibility with older releases of OSX

install_name_tool -change /System/Library/Frameworks/CoreText.framework/Versions/A/CoreText  /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/CoreText.framework/Versions/A/CoreText $APPDIR/Contents/Frameworks/QtGui.framework/Versions/4/QtGui

install_name_tool -change /System/Library/Frameworks/CoreGraphics.framework/Versions/A/CoreGraphics /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/CoreGraphics.framework/Versions/A/CoreGraphics $APPDIR/Contents/Frameworks/QtGui.framework/Versions/4/QtGui

install_name_tool -change /System/Library/Frameworks/ImageIO.framework/Versions/A/ImageIO /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/ImageIO.framework/Versions/A/ImageIO $APPDIR/Contents/Frameworks/QtGui.framework/Versions/4/QtGui

install_name_tool -change /System/Library/Frameworks/CFNetwork.framework/Versions/A/CFNetwork /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/CFNetwork.framework/CFNetwork $APPDIR/Contents/Frameworks/QtNetwork.framework/Versions/4/QtNetwork

cd $ROOT
rm -f ../oaCapture-1.0.0.dmg
hdiutil create -format UDBZ -quiet -srcfolder oaCapture.app ../oaCapture-1.0.0.dmg
