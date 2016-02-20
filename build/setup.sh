#!/bin/bash
rm -r CMake* src/ cmake* Makefile FE
cmake ..
make
printf "Trying to run FlogstEngine FE ...\n\n"
./FE
