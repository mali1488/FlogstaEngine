#!/bin/bash
rm -r CMake*
rm -r src/
rm cmake*
rm FE
rm Makefile
cmake ..
make
printf "Trying to run FlogstEngine FE ...\n\n"
./FE
