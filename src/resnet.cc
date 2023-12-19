#include "resnet.h"

torch::Device device(torch::kCPU);

torch::Tensor WeldBeadModule::classify(torch::Tensor& input_tensor) {
  
    torch::DeviceType device_type;
    if (torch::cuda::is_available()) {
        device_type = torch::kCUDA;
    } 
    else {
        device_type = torch::kCPU;
    }

    torch::Device device(device_type, 0);

  std::vector<torch::jit::IValue> inputs;
  input_tensor = input_tensor.to(device);
  inputs.emplace_back(input_tensor);

  return module.forward(inputs).toTensor();
}
