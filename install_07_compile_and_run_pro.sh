#!/bin/bash
git clone https://github.com/udacity/CppND-Route-Planning-Project.git --recurse-submodules
cd CppND-Route-Planning-Project
mkdir build
cd build
cmake ..
make
#../bin/CppND-Route-Planning-Project -f ../map.osm 
./OSM_A_star_search -f ../map.osm
