#!/bin/bash
rm -r CMake*
cmake ..
make
make install
printf "Trying to run FlogstEngine FE ...\n"
./FE
