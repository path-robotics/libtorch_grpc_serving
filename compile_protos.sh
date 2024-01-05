PROTO_SRC_DIR=./protos
protoc -I $PROTO_SRC_DIR --grpc_out=./protos --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $PROTO_SRC_DIR/weld_bead_model.proto
protoc -I $PROTO_SRC_DIR --cpp_out=./protos $PROTO_SRC_DIR/weld_bead_model.proto
python3 -m grpc_tools.protoc -I$PROTO_SRC_DIR --python_out=./python --grpc_python_out=./python $PROTO_SRC_DIR/weld_bead_model.proto

