#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <grpcpp/grpcpp.h>

#include "example.grpc.pb.h"
#include "resnet.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using AdaptiveModels::InputVector;
using AdaptiveModels::OutputVector;
using AdaptiveModels::WeldBeadModel;

WeldBeadModule weld_bead_module("/home/pjochem/Desktop/weld_bead_model_jit.pt");
std::string server_address("0.0.0.0:50051");

class WeldBeadModelServiceImpl : public WeldBeadModel::Service {
  Status inference (ServerContext* context, const InputVector* input, OutputVector* result) override {
 
    try {
	    
      // Create the input tensor.
    	torch::Tensor input_tensor = torch::zeros({210}, torch::dtype(torch::kFloat32));
    	for (int i = 0; i < (input->data()).size(); ++i) {
     		input_tensor[i] = input->data(i);
    	}

    	// Use the neural network.
    	torch::Tensor output_tensor = weld_bead_module.classify(input_tensor);
	
	    // Convert the output tensor to the protocol buffer type.
      for (int i = 0; i < 206; i++) {
        result->add_data(output_tensor[i].item<double>());
      }
    } 
    
    catch (const std::exception& ex) {
	    std::cout << ex.what() << std::endl;
    }    
    
    return Status::OK;
    }
};

void RunServer() {

  WeldBeadModelServiceImpl service;

  ServerBuilder builder;

  int max_num_threads = 100;
  grpc::ResourceQuota resource_quota;
  resource_quota.SetMaxThreads(max_num_threads);
  builder.SetResourceQuota(resource_quota);

  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}


int main(int argc, const char* argv[]) {
  RunServer();
  return 0;
}
