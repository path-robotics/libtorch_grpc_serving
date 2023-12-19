#ifndef WELD_BEAD_MODULE_H_
#define WELD_BEAD_MODULE_H_

#include <torch/script.h> // One-stop header.
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class WeldBeadModule : public torch::jit::script::Module {
 public:
  WeldBeadModule(const std::string& model_path) {
    module = torch::jit::load(model_path);
  }
  
  torch::Tensor classify(torch::Tensor& input_tensor);
 
 private:
  torch::jit::script::Module module;
};

#endif // WELD_BEAD_MODULE_H_
