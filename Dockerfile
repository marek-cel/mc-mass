FROM ubuntu:24.04

RUN apt update
RUN apt install -y \
    build-essential \
    cmake \
    googletest \
    lcov \
    libgmock-dev \
    libgtest-dev \
    libopenscenegraph-dev \
    libqt5opengl5-dev \
    libqt5svg5-dev \
    libqt5x11extras5-dev \
    libxml2-dev \
    python3-all \
    qtbase5-dev \
    qtbase5-dev-tools

