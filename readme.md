#To rebuild from scratch
cd ~/huevadas/projects/math && rm -rf build && mkdir build && cd build && cmake .. && make ; cd ..

#To build
make

#To test
make test