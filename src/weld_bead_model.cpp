#include "weld_bead_model.hpp"

torch::Device device(torch::kCPU);

WeldBeadModule::WeldBeadModule(const std::string& model_path) {

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

void WeldBeadModule::inference(const WeldBeadModel::InputVector* input, WeldBeadModel::OutputVector* output) {
  
     // Create the input tensor.
    torch::Tensor input_tensor = torch::zeros({210}, torch::dtype(torch::kFloat32));
    for (int i = 0; i < (input->data()).size(); ++i) {
        input_tensor[i] = input->data(i);
    }

    // Choose the device.
    torch::DeviceType device_type = (torch::cuda::is_available()) ? torch::kCUDA : torch::kCPU;
    torch::Device device(device_type, 0);

    // Move the inputs to the device.
    std::vector<torch::jit::IValue> inputs;
    input_tensor = input_tensor.to(device);
    inputs.emplace_back(input_tensor);

    // Do forward propagation.
    torch::Tensor output_tensor = module.forward(inputs).toTensor();

    // Write the result to the protocol buffer type.
    for (int i = 0; i < 206; i++) {
        output->add_data(output_tensor[i].item<double>());
    }
}
