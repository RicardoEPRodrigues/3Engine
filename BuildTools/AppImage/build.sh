#!/bin/bash

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then
    echo "Missing Arguments. Usage: ./build.sh <Binaries Path> <AppDir Files Path> <Destination Path>"
    exit 1
fi

SCRIPT_PATH=$(dirname "$0")

BINARIES_PATH=$(readlink -f $1)
APPDIR_PATH=$(readlink -f $2)
DEST_PATH=$(readlink -f $3)
APPDIR_NAME=${APPDIR_PATH##*/}
APPDIR_DEST_PATH=${DEST_PATH}/${APPDIR_NAME}

if [ ! -d ${BINARIES_PATH} ]; then
    echo "Binaries folder doesn't exist. ${BINARIES_PATH} . Exiting..."
    exit 1
fi

if [ ! -d ${APPDIR_PATH} ]; then
    echo "AppDir folder doesn't exist. ${APPDIR_PATH} . Exiting..."
    exit 1
fi

rm -rf ${DEST_PATH}/*
mkdir -p ${DEST_PATH}
cd ${DEST_PATH}

echo "Copying AppDir Folder"
cp -R ${APPDIR_PATH} ${DEST_PATH}
if [ $? -ne 0  ]; then
    echo "Failed Copying AppDir Folder. Exiting..."
    exit 1
fi

echo "Copying Binaries Files into AppDir"
cp -R ${BINARIES_PATH}/. ${APPDIR_DEST_PATH}
if [ $? -ne 0 ]; then
    echo "Failed Copying Binaries Files. Exiting..."
    exit 1
fi


echo "Copy 3Engine library dependencies"
DEPS="\
/usr/lib/x86_64-linux-gnu/libOpenGL.so \
/usr/lib/x86_64-linux-gnu/libOpenGL.so.0 \
/usr/lib/x86_64-linux-gnu/libOpenGL.so.0.0.0 \
/usr/lib/x86_64-linux-gnu/libglut.so \
/usr/lib/x86_64-linux-gnu/libglut.so.3 \
/usr/lib/x86_64-linux-gnu/libglut.so.3.9.0 \
/usr/lib/x86_64-linux-gnu/libGLEW.so \
/usr/lib/x86_64-linux-gnu/libGLEW.so.2.0 \
/usr/lib/x86_64-linux-gnu/libGLEW.so.2.0.0
"
cp ${DEPS} ${APPDIR_DEST_PATH}/lib

#CPLP=${SCRIPT_PATH}/cpld.sh

#echo "Copy 3Engine library dependencies"
#mkdir -p ${APPDIR_DEST_PATH}/lib
#for i in `find ${APPDIR_DEST_PATH}/lib -maxdepth 1 -executable -type f`; do
#    if [[ ${i} = *".so" ]]; then
#        ${CPLP} ${i} ${APPDIR_DEST_PATH}/lib #> /dev/null
#    fi
#done

echo "Moving Executables to AppDir/bin" # and copy library dependencies
mkdir -p ${APPDIR_DEST_PATH}/bin
# Gets all executables and places them on bin folder
for i in `find ${APPDIR_DEST_PATH} -maxdepth 1 -executable -type f`; do
    if [ ${i##*/} != "AppRun" ] && [[ ${i} != *".desktop" ]] && [[ ${i} !=  *".png" ]]; then
#        ${CPLP} ${i} ${APPDIR_DEST_PATH}/lib #> /dev/null
        mv ${i} ${APPDIR_DEST_PATH}/bin
    fi
done

echo "Checking AppImage Tool..."
if [ ! -f appimagetool.AppImage ]; then
    echo "AppImage Tool not found. Downloading..."
    wget -O appimagetool.AppImage "https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage"
    if [ $? -ne 0 ]; then
        echo "Unable to download AppImage Tool. Exiting..."
        exit 1
    fi
    chmod a+x appimagetool.AppImage
else
    echo "AppImage Tool found"
fi

# Define output architecture
export ARCH=x86_64

# Create AppImage with the name of the AppDir Folder
./appimagetool.AppImage ${APPDIR_NAME} ${APPDIR_NAME%.AppDir}.freeGLUT.AppImage
if [ $? -ne 0 ]; then
    echo "Unable to create ${APPDIR_NAME%.AppDir}.AppImage. Exiting..."
    exit 1
fi

echo "Successfully created ${APPDIR_NAME%.AppDir}.AppImage"