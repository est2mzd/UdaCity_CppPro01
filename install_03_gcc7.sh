#!/bin/bash
sudo rm /usr/bin/g++
sudo ln -s /usr/bin/g++-7 /usr/bin/g++
g++ --version
