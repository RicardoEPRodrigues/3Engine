#!/bin/bash

set -e
set -x

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DEPENDENCIES_DIR="${DIR}/dependencies"

# Installing Dependencies
if hash apt 2>/dev/null; then
  if ! dpkg --get-selections | grep g++; then
    sudo apt-get install -y g++
  fi
  if ! dpkg --get-selections | grep libxmu-dev; then
    sudo apt-get install -y libxmu-dev
  fi
  if ! dpkg --get-selections | grep libxi-dev; then
    sudo apt-get install -y libxi-dev
  fi
  if ! dpkg --get-selections | grep cmake; then
    sudo apt-get install -y cmake
  fi
  if ! dpkg --get-selections | grep libgl1-mesa-dev; then
    sudo apt-get install -y libgl1-mesa-dev
  fi
  if ! dpkg --get-selections | grep libjpeg-dev; then
    sudo apt-get install -y libjpeg-dev
  fi
  if ! dpkg --get-selections | grep libjpeg-dev; then
    sudo apt-get install -y libtiff-dev
  fi
  if ! dpkg --get-selections | grep libjpeg-dev; then
    sudo apt-get install -y libwebp-dev
  fi
  if ! dpkg --get-selections | grep libfreetype6-dev; then
    sudo apt-get install -y libfreetype6-dev
  fi
fi


mkdir -p ${DEPENDENCIES_DIR}
cd /tmp

wget https://www.libsdl.org/release/SDL2-2.0.9.tar.gz -O SDL2-2.0.9.tar.gz
tar -xzvf SDL2-2.0.9.tar.gz
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.4.tar.gz -O SDL2_image-2.0.4.tar.gz
tar -xzvf SDL2_image-2.0.4.tar.gz
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz -O SDL2_ttf-2.0.15.tar.gz
tar -xzvf SDL2_ttf-2.0.15.tar.gz
wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz -O SDL2_mixer-2.0.4.tar.gz
tar -xzvf SDL2_mixer-2.0.4.tar.gz

(cd SDL2-2.0.9        && ./configure --prefix="${DEPENDENCIES_DIR}/SDL2"                                              && make clean && make -j4 && make install && cd ..)
(cd SDL2_image-2.0.4  && ./configure --prefix="${DEPENDENCIES_DIR}/SDL2" --with-sdl-prefix="${DEPENDENCIES_DIR}/SDL2" && make clean && make -j4 && make install && cd ..)
(cd SDL2_ttf-2.0.15   && ./configure --prefix="${DEPENDENCIES_DIR}/SDL2" --with-sdl-prefix="${DEPENDENCIES_DIR}/SDL2" && make clean && make -j4 && make install && cd ..)
(cd SDL2_mixer-2.0.4  && ./configure --prefix="${DEPENDENCIES_DIR}/SDL2" --with-sdl-prefix="${DEPENDENCIES_DIR}/SDL2" && make clean && make -j4 && make install && cd ..)

wget https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.tgz -O glew-2.1.0.tgz
tar -xzvf glew-2.1.0.tgz

(cd glew-2.1.0        && make clean && make && GLEW_NO_GLU=1 GLEW_DEST="${DEPENDENCIES_DIR}/GLEW" make install && cd ..)