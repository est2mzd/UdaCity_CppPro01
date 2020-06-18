#!/bin/bash
sudo apt-get purge cmake
tar -xzvf cmake-3.14.3.tar.gz
cd cmake-3.14.3
./bootstrap
make
sudo make install
