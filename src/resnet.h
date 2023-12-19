#ifndef WELD_BEAD_MODULE_H_
#define WELD_BEAD_MODULE_H_

#include <torch/script.h> // One-stop header.
#include <torch/torch.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class WeldBeadModule : public torch::jit::script::Module {
 public:
  WeldBeadModule(const std::string& model_path) {

    torch::DeviceType device_type;
    if (torch::cuda::is_available()) {
        device_type = torch::kCUDA;
    } 
    else {
        device_type = torch::kCPU;
    }

    torch::Device device(device_type, 0);
    module = torch::jit::load(model_path);
    module.to(device);
  }
  
  torch::Tensor classify(torch::Tensor& input_tensor);

 private:
  torch::jit::script::Module module;
  
};

#endif // WELD_BEAD_MODULE_H_
