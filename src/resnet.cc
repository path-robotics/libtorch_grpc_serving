#include "resnet.h"

torch::Tensor WeldBeadModule::classify(torch::Tensor& input_tensor) {
  
  std::vector<torch::jit::IValue> inputs;
  inputs.push_back(input_tensor);

  return module.forward(inputs).toTensor();
}
