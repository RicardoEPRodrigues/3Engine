#!/bin/sh

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then
    echo "Missing Arguments. Usage: ./build.sh <Binaries Path> <AppDir Files Path> <Destination Path>"
    exit 1
fi

binariesPath=$(readlink -f $1)
appDirPath=$(readlink -f $2)
destPath=$(readlink -f $3)
appDirName=${appDirPath##*/}
destAppDirPath=${destPath}/${appDirName}

if [ ! -d ${binariesPath} ]; then
    echo "Binaries folder doesn't exist. ${binariesPath} . Exiting..."
    exit 1
fi

if [ ! -d ${appDirPath} ]; then
    echo "AppDir folder doesn't exist. ${appDirPath} . Exiting..."
    exit 1
fi


mkdir -p ${destPath}
cd ${destPath}

echo "Copying AppDir Folder"
cp -R ${appDirPath} .
if [ $? -ne 0  ]; then
    echo "Failed Copying AppDir Folder. Exiting..."
    exit 1
fi

echo "Copying Binaries Files into AppDir"
cp -R ${binariesPath}/. ${destAppDirPath}
if [ $? -ne 0 ]; then
    echo "Failed Copying Binaries Files. Exiting..."
    exit 1
fi

echo "Moving Executables to AppDir/bin"
mkdir -p ${destAppDirPath}/bin
# Gets all executables and places them on bin folder
for i in `find ${destAppDirPath} -maxdepth 1 -executable -type f`; do
    if [ ${i##*/} != "AppRun" ]; then
        mv ${i} ${destAppDirPath}/bin
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
./appimagetool.AppImage ${appDirName} ${appDirName%.AppDir}.AppImage
if [ $? -ne 0 ]; then
    echo "Unable to create ${appDirName%.AppDir}.AppImage. Exiting..."
    exit 1
fi

echo "Successfully created ${appDirName%.AppDir}.AppImage"