#!/bin/bash

INCLUDES="-I. -Isource/renders -Isource/orders -Isource"
OPENCV_FLAGS=$(pkg-config --cflags --libs opencv4)
GL_FLAGS="-lglfw -lGL -lGLEW"

g++ -o 'bin/main.o' -c 'main.cpp' $INCLUDES $OPENCV_FLAGS
g++ -o 'bin/sprite.o' -c 'source/sprite.cpp' $OPENCV_FLAGS
g++ -o 'bin/canvas.o' -c 'source/canvas.cpp' $OPENCV_FLAGS
g++ -o 'bin/pixelCanvas.o' -c 'source/pixelCanvas.cpp' $OPENCV_FLAGS
g++ -o 'run' 'bin/main.o' 'bin/sprite.o' 'bin/canvas.o' 'bin/pixelCanvas.o' $OPENCV_FLAGS $GL_FLAGS
