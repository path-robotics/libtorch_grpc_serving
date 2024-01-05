GPRC_COMPILE_ROOT_PATH=$(pwd)/grpc/
cd $GPRC_COMPILE_ROOT_PATH/third_party/zlib
mkdir build && cd build
cmake ..
make -j $(nproc)
sudo make install
