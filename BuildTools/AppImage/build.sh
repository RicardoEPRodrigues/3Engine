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

mkdir -p ${DEST_PATH}
cd ${DEST_PATH}

# Remove previous build
rm -rf ${APPDIR_DEST_PATH}/*

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
/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so \
/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0 \
/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.8.0 \
/usr/lib/x86_64-linux-gnu/libSDL2.so \
/usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so \
/usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0 \
/usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0.2.1 \
/usr/lib/x86_64-linux-gnu/libSDL2_image.so \
/usr/lib/x86_64-linux-gnu/libSDL2_mixer-2.0.so \
/usr/lib/x86_64-linux-gnu/libSDL2_mixer-2.0.so.0 \
/usr/lib/x86_64-linux-gnu/libSDL2_mixer-2.0.so.0.2.0 \
/usr/lib/x86_64-linux-gnu/libSDL2_mixer.so \
/usr/lib/x86_64-linux-gnu/libSDL2_ttf-2.0.so \
/usr/lib/x86_64-linux-gnu/libSDL2_ttf-2.0.so.0 \
/usr/lib/x86_64-linux-gnu/libSDL2_ttf-2.0.so.0.14.0 \
/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so \
/usr/lib/x86_64-linux-gnu/libGLEW.so.2.0 \
/usr/lib/x86_64-linux-gnu/libsndio.so \
/usr/lib/x86_64-linux-gnu/libsndio.so.6.1
"
# Dependencies for Ubuntu 14.04
#DEPS="${DEPS} \
#/usr/lib/x86_64-linux-gnu/libGLX.so.0 \
#/usr/lib/x86_64-linux-gnu/libGLX.so.0.0.0 \
#/usr/lib/x86_64-linux-gnu/libGLX_indirect.so.0 \
#/usr/lib/x86_64-linux-gnu/libpng16.so \
#/usr/lib/x86_64-linux-gnu/libpng16.so.16 \
#/usr/lib/x86_64-linux-gnu/libpng16.so.16.34.0 \
#/usr/lib/x86_64-linux-gnu/libwebp.so.6 \
#/usr/lib/x86_64-linux-gnu/libwebp.so.6.0.2
#/usr/lib/x86_64-linux-gnu/libGLdispatch.so \
#/usr/lib/x86_64-linux-gnu/libGLdispatch.so.0 \
#/usr/lib/x86_64-linux-gnu/libGLdispatch.so.0.0.0 \
#/usr/lib/x86_64-linux-gnu/libstdc++.so.6 \
#/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.25 \
#/usr/lib/x86_64-linux-gnu/libxkbcommon.so \
#/usr/lib/x86_64-linux-gnu/libxkbcommon.so.0 \
#/usr/lib/x86_64-linux-gnu/libxkbcommon.so.0.0.0 \
#/lib/x86_64-linux-gnu/libm.so.6 \
#/lib/x86_64-linux-gnu/libz.so.1 \
#/lib/x86_64-linux-gnu/libz.so.1.2.11 \
#"

cp ${DEPS} ${APPDIR_DEST_PATH}/lib

#CPLP=${SCRIPT_PATH}/cpld.sh
#
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
./appimagetool.AppImage ${APPDIR_NAME} ${APPDIR_NAME%.AppDir}.AppImage
if [ $? -ne 0 ]; then
    echo "Unable to create ${APPDIR_NAME%.AppDir}.AppImage. Exiting..."
    exit 1
fi

echo "Successfully created ${APPDIR_NAME%.AppDir}.AppImage"
