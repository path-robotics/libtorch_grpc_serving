mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=./third_party/libtorch ..
make -j $(nproc)
