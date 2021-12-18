# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM ubuntu:latest
ENV DEBIAN_FRONTEND noninteractive
# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install clang

RUN apt install libsdl2-dev libsdl2-2.0-0 -y
RUN apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
RUN apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y
RUN apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y

# These commands copy your files into the specified directory in the image
# and set that as the working location
WORKDIR /app
COPY . .


# This command compiles your app using GCC, adjust for your source code
RUN mkdir bin
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/App.o src/App.cpp
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/Diamond.o src/Diamond.cpp
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/DiamondBoard.o src/DiamondBoard.cpp
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/Block.o src/Block.cpp
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/BoardView.o src/BoardView.cpp
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/BoardController.o src/BoardController.cpp
RUN clang++  `sdl2-config --cflags` -g  -c -o bin/main.o src/main.cpp
RUN clang++ -o match3 bin/App.o bin/Diamond.o bin/DiamondBoard.o bin/Block.o bin/BoardView.o bin/BoardController.o bin/main.o `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm 
RUN export DISPLAY=:0.0
# This command runs your application, comment out this line to compile only
CMD ["./match3"]

LABEL Name=dockerc Version=0.0.1
