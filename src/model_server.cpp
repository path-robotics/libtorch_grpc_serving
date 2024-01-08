#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <grpcpp/grpcpp.h>
#include <string>
#include "weld_bead_model.grpc.pb.h"
#include "weld_bead_model.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using WeldBeadModel::InferenceService;
using WeldBeadModel::InputVector;
using WeldBeadModel::OutputVector;

/* Is a Torchscript module thread safe?
 * Yes, https://discuss.pytorch.org/t/is-inference-thread-safe/88583
 */

WeldBeadModule weld_bead_module("/home/pjochem/Desktop/jit_model_v1_from_shared_drive.pt");

class WeldBeadModelServiceImpl : public InferenceService::Service {
  Status inference (ServerContext* context, const InputVector* input, OutputVector* output) override {
 
    try {
    	// Use the neural network.
    	weld_bead_module.inference(input, output);
    } 
    
    catch (const std::exception& ex) {
	    std::cout << ex.what() << std::endl;

      // How do I return an error message?
      return Status::OK;
    }    
    
    return Status::OK;
    }
};

void RunServer(std::string server_address) {

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
  std::cout << "Server listening on " << server_address << std::endl << std::flush;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}


int main(int argc, const char* argv[]) {

  using namespace std;
  vector<string> addresses = {"0.0.0.0:50051"};
  vector<thread*> threads;
  for (auto& address: addresses) {

    thread* next_thread = new thread(RunServer, address);
    threads.push_back(next_thread);
  }

  for (auto& thread: threads) {
    thread->join();
  }

  return 0;
}
