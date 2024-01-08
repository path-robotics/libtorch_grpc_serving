GPRC_COMPILE_ROOT_PATH=$(pwd)/grpc/
cd $GPRC_COMPILE_ROOT_PATH
mkdir build && cd build
cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_SSL_PROVIDER=package ..
make -j $(nproc)
sudo make install
sudo ldconfig
