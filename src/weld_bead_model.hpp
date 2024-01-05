#ifndef WELD_BEAD_MODULE_H_
#define WELD_BEAD_MODULE_H_

#include <torch/script.h>
#include <torch/torch.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "weld_bead_model.hpp"
#include "weld_bead_model.grpc.pb.h"



class WeldBeadModule : public torch::jit::script::Module {
 
 public:
  WeldBeadModule(const std::string& model_path);
  void inference(const WeldBeadModel::InputVector* input, WeldBeadModel::OutputVector* output);

 private:
  torch::jit::script::Module module;
};

#endif // WELD_BEAD_MODULE_H_
