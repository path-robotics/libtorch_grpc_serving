GPRC_COMPILE_ROOT_PATH=$(pwd)/grpc/
cd $GPRC_COMPILE_ROOT_PATH/third_party/protobuf/cmake
mkdir build && cd build
cmake -Dprotobuf_BUILD_TESTS=OFF ..
make -j $(nproc)
sudo make install
