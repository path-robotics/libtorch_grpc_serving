add_library(adaptive_welding_models weld_bead_model.hpp weld_bead_model.cpp)
target_link_libraries(adaptive_welding_models ${TORCH_LIBRARIES})

add_executable(model_server model_server.cpp ${PROTO_GENERATED_FILES_DIR}/weld_bead_model.pb.cc ${PROTO_GENERATED_FILES_DIR}/weld_bead_model.grpc.pb.cc)
target_link_libraries(model_server
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF}
    adaptive_welding_models)
