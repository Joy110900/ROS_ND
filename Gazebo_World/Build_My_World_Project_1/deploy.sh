#!/bin/bash

mkdir build
echo Created build directory
cd build
cmake ../
sleep 2
make
export GAZEBO_PLUGIN_PATH=$PWD
cd ../world
gazebo my_world
