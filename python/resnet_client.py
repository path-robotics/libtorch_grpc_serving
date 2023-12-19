import grpc
import numpy as np
import torch
import threading
import time
import example_pb2
import example_pb2_grpc 

host = 'localhost:50051'
model_filepath = "/home/pjochem/Desktop/weld_bead_model_jit.pt"

def do_server_inference(input_vector: np.ndarray) -> np.ndarray:

    with grpc.insecure_channel(host) as channel:

        stub = example_pb2_grpc.WeldBeadModelStub(channel)
        request = example_pb2.InputVector()
        request.data[:] = list(input_vector)
        response = stub.inference(request)

    return np.array(list(response.data))

def do_jit_inference(input_vector: np.ndarray) -> np.ndarray:
    
    model = torch.jit.load(model_filepath).to('cpu')
    model.eval()

    input_tensor = torch.asarray(input_vector)
    input_tensor = input_tensor.to(torch.float32)

    output_torch_tensor = model(input_tensor).cpu().detach()
    return output_torch_tensor.numpy()


def vector_diff(a: np.ndarray, b: np.ndarray) -> bool:
    """..."""

    return np.allclose(a, b, atol=1e-04)


if __name__ == '__main__':

    #input_vector = np.array([0.0] * 210)
    input_vector = np.random.rand(210)
    server_output_vector = do_server_inference(input_vector)
    jit_output_vector = do_jit_inference(input_vector)
    
    threads = []
    num_threads = 700
    for i in range(num_threads):
        threads.append(threading.Thread(target=do_server_inference, args=(input_vector,)))
    
    start_time = time.time()
    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()
    end_time = time.time()

    elapsed_time = end_time - start_time

    print(f"Elapsed Time: {elapsed_time}")
    print(f"Are the two output vectors equal: {vector_diff(server_output_vector, jit_output_vector)}")
 
