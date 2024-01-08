cmake_minimum_required(VERSION 3.10)

project(custom_ops
    VERSION 1.0
    LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
set(PROTO_GENERATED_FILES_DIR "${PROJECT_SOURCE_DIR}/protos")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-DRESNETSAVEPATH="${PROJECT_SOURCE_DIR}/traced_resnet_model.pt")

# set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

list(APPEND CMAKE_PREFIX_PATH "/home/pjochem/Desktop/libtorch_grpc_serving/third_party/libtorch/share/cmake/Torch")
set(CMAKE_CUDA_COMPILER "/usr/local/cuda/bin/nvcc")
find_package(Torch REQUIRED)
set(CMAKE_CUDA_COMPILER "/usr/local/cuda/bin/nvcc")
message(STATUS "Torch libraries: ${TORCH_LIBRARIES}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

include_directories("${PROTO_GENERATED_FILES_DIR}")

add_subdirectory(src)
